// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLSUniversalMtdComputer.h"

#include <vector>

#include <Eigen/Dense>
#include <Logger.hpp>

#include "TLSInputMatrices.h"
#include "TLSResultsMatrices.h"
#include "TSparseMatrix.h"

TLSUniversalMtdComputer::TLSUniversalMtdComputer() : count(1)
{ // default constructor
}

TLSUniversalMtdComputer::~TLSUniversalMtdComputer()
{ // destructor
}

bool TLSUniversalMtdComputer::computeResults(TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	bool result = true;
	if (rm->getSolutionVectByConst()->size() != 0)
	{
		result = computeResultsMatrices(im, rm);
	}
	else
	{
		logWarning() << "Number of unknowns = 0.";
	}
	return result;
}

bool TLSUniversalMtdComputer::computeResultsMatrices(TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	if (!(rm->getSolutionVectByConst()) || !(im->isInitialized))
	{
		logCritical() << "Some of the design matrices are not initialized!";
		return false;
	}

	const TSparseMatrix &A = im->getFirstDgnMtrx();
	const TVector &W = im->getMisclosureVctr(); // W : Misclosures vector ("fermetures")
	const TSparseMatrix &A2 = im->getCnstrFirstDgnMtrx(); // A2 : First design matrix part related to constraints only
	const TVector &W2 = im->getCnstrMisclosureVctr(); // W2 : Misclosures vector part related to constraints only

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();

	// set invN1
	TSparseMatrix invN1(nbEq, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		const TSparseMatrix &Pv = im->getWeightMtrx();
		const TSparseMatrix &invB = im->getSecondDgnBlockDiagInvMtrx();
		invN1 = invB.transpose() * Pv * invB;
	}
	else
	{ // if B is not block diagonal, invN1 needs to be computed via an explicit inversion
	  // B*invPv*BT is symmetric and positive definite so LDLT can be used
		const TSparseMatrix &B = im->getSecondDgnMtrx();
		const TSparseMatrix &InvPv = im->getWeightInvMtrx();
		if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1, true))
		{
			logCritical() << "Matrix B*inv(Pv)*transpose(B) could not be inverted!";
			return false;
		}
		// copy invN1 to resultmatrices only if B is not block diagonal, otherwise it is not needed in the calcRes method
		rm->setInvN1Matrix(invN1);
	}

	// Calculate Normal matrix N2 = At * inv( B * inv(P) * Bt ) * A , matrix dimensions (u,u)
	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = A.transpose() * invN1 * A;

	// Regularize N2 diagonal
	double regTerm = 1e-6;
	for (int k = 0; k < N2.outerSize(); ++k)
	{
		for (TSparseMatrix::InnerIterator it(N2, k); it; ++it)
		{
			if (it.row() == it.col())
				it.valueRef() += regTerm;
		}
	}

	// For constrained problems, augment N2 to ensure SPD even for rank-deficient networks.
	// A2^T*A2 lifts zero eigenvalues in the datum-deficient directions.
	// The constrained solution and covariance are unaffected (A2^T*A2 is constant on the constraint manifold).
	if (nbCnstr > 0)
		N2 += A2.transpose() * A2;

	// Factorize N2 via LDLT (both constrained and unconstrained)
	storedLDLT = std::make_unique<Eigen::SimplicialLDLT<TSparseMatrix>>();
	TSparseMatrix N2scaled = TSparseUtils::createSymmetricScaling(N2, storedScaling);
	storedLDLT->compute(N2scaled);
	if (storedLDLT->info() != Eigen::Success)
	{
		logCritical() << "LDLT factorization of N2 failed!";
		storedLDLT.reset();
		return false;
	}
	storedNbUnk = nbUnk;

	// Helper: solve N2 * x = rhs using the scaled LDLT factorization
	auto solveN2 = [&](const TVector &rhs) -> TVector
	{
		TVector rhsScaled = storedScaling.asDiagonal() * rhs;
		TVector yScaled = storedLDLT->solve(rhsScaled);
		return storedScaling.asDiagonal() * yScaled;
	};

	TVector n = A.transpose() * invN1 * W;
	TVector x0 = solveN2(-n); // unconstrained solution

	if (nbCnstr == 0)
	{
		rm->setNormalMatrix(N2);
		rm->setSolutionVect(x0);
	}
	else
	{
		// Schur complement: solve N2 * X = A2^T (one column per constraint)
		Eigen::MatrixXd A2dense(A2);
		storedX.resize(nbUnk, nbCnstr);
		for (int c = 0; c < nbCnstr; ++c)
			storedX.col(c) = solveN2(A2dense.row(c).transpose());

		// Schur complement: Sc = A2 * X (small nbCnstr x nbCnstr dense matrix)
		Eigen::MatrixXd Sc = A2dense * storedX;
		// Lagrange multipliers: lambda = Sc^{-1} * (A2 * x0 + W2)
		storedScInv = Sc.inverse();
		TVector lambda = storedScInv * (A2dense * x0 + W2);
		// Corrected solution
		TVector solution = x0 - storedX * lambda;

		rm->setNormalMatrix(N2);
		rm->setSolutionVect(solution);
	}

	return true;
}

bool TLSUniversalMtdComputer::calcResidusAndVarCovMatrix(const TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = im->getNbrUnknowns();
	int nbObs = im->getNbrObservations();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	if (!(rm->getSolutionVectByConst()) || !(rm->getResidualsVectByConst()) || !(rm->getZReliabilityVectByConst()) || !(rm->getResCovarDiagByConst()))
		throw std::runtime_error("Some of the result matrices are not initialized!");

	const TSparseMatrix &A = im->getFirstDgnMtrx();
	const TSparseMatrix &B = im->getSecondDgnMtrx();
	const TSparseMatrix &InvPv = im->getWeightInvMtrx();

	TSparseMatrix S(nbObs, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		// if B is block-diagonal, the S formula simplifies to -invB
		S = -(im->getSecondDgnBlockDiagInvMtrx());
	}
	else
	{
		if (!(rm->getInvN1MatrixByConst()))
		{
			throw std::runtime_error("The matrix invN1 is not initialized!");
		}
		const TSparseMatrix &invN1 = *rm->getInvN1MatrixByConst(); // NB: invN1 will NOT be recalculated here (just taken from previous results!)
		S = -InvPv * B.transpose() * invN1;
	}
	const TSparseMatrix &Pv = im->getWeightMtrx();
	const TVector &W = im->getMisclosureVctr();
	const TVector &solution = *rm->getSolutionVectByConst();

	//--------------- Residuals ---------------//
	TVector V(nbObs);
	V = S * (A * solution + W);

	//--------------- Sigma 0 a posteriri ---------------//
	sigmaZero2Aposteriori = V.transpose() * Pv * V;
	if (nbEq + nbCnstr != nbUnk)
		sigmaZero2Aposteriori /= (nbEq - nbUnk + nbCnstr);
	else
		fError += "Number of equations + constraints equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk, nbCnstr);
	rm->setSigmaZeroLimits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	// ----------Covariance Matrices-----------//
	bool PvIsDiag = (Pv.nonZeros() == Pv.rows());
	TSparseMatrix Qxx(nbUnk, nbUnk);
	TVector QvvDiag(nbObs);
	TVector ZReliability(nbObs);

	if (!storedLDLT)
	{
		// Zero unknowns or factorization was never performed — set trivial empty results
		rm->setResCovarDiag(QvvDiag);
		rm->setZReliabilityVect(ZReliability);
		rm->setUnkCovarMtrx(Qxx);
		rm->setResidualsVect(V);
		return true;
	}

	if (PvIsDiag)
	{
		TSparseMatrix M = S * A;
		TSparseMatrix augPattern = TSparseUtils::symbolicMtM(M);
		TSparseMatrix Qfree = TSparseUtils::takahashiSelectedInverse(*storedLDLT, storedScaling, &augPattern);
		storedLDLT.reset();

		TVector diagMQxxMT;
		if (nbCnstr == 0)
		{
			Qxx = Qfree;
			diagMQxxMT = TSparseUtils::diagMQMt(M, Qxx);
		}
		else
		{
			// Rank-c correction: Qxx = Q_free - X * Sc^{-1} * X^T
			// As a sparse matrix, apply correction to all elements in Q_free's pattern
			Eigen::MatrixXd XScInv = storedX * storedScInv; // (nbUnk x nbCnstr)
			Qxx = Qfree;
			for (int col = 0; col < Qxx.outerSize(); ++col)
				for (TSparseMatrix::InnerIterator it(Qxx, col); it; ++it)
					it.valueRef() -= XScInv.row(it.row()).dot(storedX.row(it.col()));

			// diag(M*Qxx*M^T) = diag(M*Qfree*M^T) - diag((M*X)*Sc^{-1}*(M*X)^T)
			TVector diagMQfreeMT = TSparseUtils::diagMQMt(M, Qfree);
			Eigen::MatrixXd MX = Eigen::MatrixXd(M) * storedX; // (nbObs x nbCnstr)
			Eigen::MatrixXd MXScInv = MX * storedScInv;
			// diag of MXScInv * MX^T = row-wise dot products
			TVector diagCorrection(nbObs);
			for (int i = 0; i < nbObs; ++i)
				diagCorrection[i] = MXScInv.row(i).dot(MX.row(i));
			diagMQxxMT = diagMQfreeMT - diagCorrection;
		}

		if (im->getSecondDgnBlockDiagStatus())
			QvvDiag = InvPv.diagonal() - diagMQxxMT;
		else
		{
			TSparseMatrix SBInvPv = S * B * InvPv;
			QvvDiag = SBInvPv.diagonal() - diagMQxxMT;
		}
		ZReliability = QvvDiag.cwiseProduct(Pv.diagonal());
	}
	else
	{
		TSparseMatrix Qfree = TSparseUtils::takahashiSelectedInverse(*storedLDLT, storedScaling);
		storedLDLT.reset();

		if (nbCnstr == 0)
			Qxx = Qfree;
		else
		{
			Eigen::MatrixXd XScInv = storedX * storedScInv;
			Qxx = Qfree;
			for (int col = 0; col < Qxx.outerSize(); ++col)
				for (TSparseMatrix::InnerIterator it(Qxx, col); it; ++it)
					it.valueRef() -= XScInv.row(it.row()).dot(storedX.row(it.col()));
		}

		if (im->getSecondDgnBlockDiagStatus())
		{
			TSparseMatrix Qvv = -S * B * InvPv - S * A * Qxx * A.transpose() * S.transpose();
			QvvDiag = Qvv.diagonal();
			TSparseMatrix QvvPv = Qvv * Pv;
			ZReliability = QvvPv.diagonal();
		}
	}

	// Copies the data into the members of the TResultsMatrices object
	rm->setResCovarDiag(QvvDiag);
	rm->setZReliabilityVect(ZReliability);
	rm->setUnkCovarMtrx(Qxx);
	rm->setResidualsVect(V);
	return true;
}
