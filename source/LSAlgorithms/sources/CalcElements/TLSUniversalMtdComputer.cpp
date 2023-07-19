#include "TLSUniversalMtdComputer.h"

#include <vector>
#include <iostream>

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
	// test if we do not have a 'nullpointer' in a case that the matrices are not initialized
	if (!(im->getFirstDgnMtrx()) || !(im->getCnstrFirstDgnMtrx()) || !(rm->getSolutionVectByConst()))
	{
		logCritical() << "Some of the design matrices are not initialized!";
		return false;
	}

	const TSparseMatrix &A = *im->getFirstDgnMtrx();
	const TVector &W = im->getMisclosureVctr(); // W : Misclosures vector ("fermetures")
	const TSparseMatrix &A2 = *im->getCnstrFirstDgnMtrx(); // A2 : First design matrix part related to constraints only
	const TVector &W2 = im->getCnstrMisclosureVctr(); // W2 : Misclosures vector part related to constraints only


	//masked input data
	//TSparseMatrix AMasked = im->maskEqnRows(&A);
	TSparseMatrix AMasked = im->maskRows(&A, im->maskData.EIndices);
	//std::cout << (AMasked - AMasked2).toDense().norm() << std::endl;
	//TVector WMasked = im->getEqnMask() * W;
	TVector WMasked = im->maskRows(W, im->maskData.EIndices);


	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();
	int nbMasked = im->maskData.EIndices.size();
	int nbEqReduced = nbEq - nbMasked;


	// set invN1
	TSparseMatrix invN1(nbEqReduced, nbEqReduced);
	if (im->getSecondDgnBlockDiagStatus())
	{
		if (!(im->getWeightMtrx()) || !(im->getSecondDgnBlockDiagInvMtrx()))
		{
			throw std::runtime_error("Some of the design matrices are not initialized!");
		}
		const TSparseMatrix &Pv = *im->getWeightMtrx();
		//TSparseMatrix PvMasked = im->maskObsColsAndRows(&Pv);
		TSparseMatrix PvRowMasked = im->maskRows(&Pv, im->maskData.OIndices);
		TSparseMatrix PvMasked = im->maskColumns(&PvRowMasked, im->maskData.OIndices);
		//std::cout << (PvMasked - PvMasked2).toDense().norm() << std::endl;
		const TSparseMatrix &invB = *im->getSecondDgnBlockDiagInvMtrx();
		//TSparseMatrix invBMasked = im->maskColsAndRows(&invB);
		//TSparseMatrix invBMasked = (im->getObsMask()).transpose() * ( invB )*( im->getEqnMask()).transpose();
		TSparseMatrix invBRowMasked = im->maskRows(&invB, im->maskData.EIndices);
		TSparseMatrix invBMasked = im->maskColumns(&invBRowMasked, im->maskData.OIndices);
		//std::cout << (invBMasked - invBMasked2).toDense().norm() << std::endl;
		invN1 = invBMasked.transpose() * PvMasked * invBMasked;
	}
	else
	{ // if B is not block diagonal, invN1 needs to be computed via an explicit inversion
	  // B*invPv*BT is symmetric and positive definite so LDLT can be used
		if (!(im->getWeightInvMtrx()) || !(im->getSecondDgnMtrx()))
		{
			throw std::runtime_error("Some of the design matrices are not initialized!");
		}
		const TSparseMatrix &B = *im->getSecondDgnMtrx();
		const TSparseMatrix &InvPv = *im->getWeightInvMtrx();
		TSparseMatrix BMasked = im->getEqnMask() * B * im->getObsMask();
		TSparseMatrix InvPvMasked = im->maskObsColsAndRows(&InvPv);
		if (!TSparseUtils::inverse(BMasked * InvPvMasked * BMasked.transpose(), invN1, true))
		{
			logCritical() << "Matrix B*inv(Pv)*transpose(B) could not be inverted!";
			return false;
		}
		// copy invN1 to resultmatrices only if B is not block diagonal, otherwise it is not needed in the calcRes method
		rm->setInvN1Matrix(invN1);
	}

	// Calculate Normal matrix N2 = At * inv( B * inv(P) * Bt ) * A , matrix dimensions (u,u)
	// and re-sets this new matrix to the main TLSResultsMatrices object.
	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = AMasked.transpose() * invN1 * AMasked;

	// construct NBig = (N2, A2t
	//                   A2, 0  )
	TSparseMatrix NBig(nbUnk + nbCnstr, nbUnk + nbCnstr);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(N2.nonZeros() + 2 * A2.nonZeros());

	// Fill in the N2 part
	for (int k = 0; k < N2.outerSize(); ++k)
	{
		for (TSparseMatrix::InnerIterator it(N2, k); it; ++it)
			coeffs.push_back(TTriplet(it.row(), it.col(), it.value()));
	}

	// Fill the A2 and A2T
	for (int k = 0; k < A2.outerSize(); ++k)
	{
		for (TSparseMatrix::InnerIterator it(A2, k); it; ++it)
		{
			coeffs.push_back(TTriplet(it.row() + N2.rows(), it.col(), it.value())); // A2
			coeffs.push_back(TTriplet(it.col(), it.row() + N2.cols(), it.value())); // A2T
		}
	}
	NBig.setFromTriplets(coeffs.begin(), coeffs.end());

	// Extended vector: appends W2 (constraints misclosures) to the calculated At*inv(N1)*W  vector
	TVector VBig(nbUnk + nbCnstr);
	VBig << AMasked.transpose() * invN1 * WMasked, W2;

	// Calculates solution NBig * X = -VBig and keeps only the part corresponding to adjusted parameters
	TVector solutionExt(nbUnk + nbCnstr);

	// use Cholesky decomposition if nbCnstr=0, otherwise SparseLU as positive definiteness of NBig may be violated
	if (!TSparseUtils::solveUnique(NBig, -VBig, solutionExt, (nbCnstr == 0), (nbCnstr == 0), useStrictThreshold))
	{
		logCritical() << "No solution could be found when solving equation system: Nbig * dX = -VBig (extended matrices with conditions)";
		return false;
	}

	TVector solution(nbUnk);
	// we do not need the Lagrange multipliers
	solution = solutionExt.head(nbUnk);

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(NBig);
	rm->setSolutionVect(solution);

	return true;
}

bool TLSUniversalMtdComputer::calcResidusAndVarCovMatrix(TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = im->getNbrUnknowns();
	int nbObs = im->getNbrObservations();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	if (!(im->getFirstDgnMtrx()) || !(im->getSecondDgnMtrx()) || !(im->getWeightInvMtrx()) || !(rm->getSolutionVectByConst()) || !(rm->getResidualsVectByConst())
		|| !(rm->getResCovarMtrxByConst()))
		throw std::runtime_error("Some of the design matrices are not initialized!");

	const TSparseMatrix &A = *im->getFirstDgnMtrx();
	const TSparseMatrix &B = *im->getSecondDgnMtrx();
	const TSparseMatrix &InvPv = *im->getWeightInvMtrx();

	TSparseMatrix S(nbObs, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		if (!(im->getSecondDgnBlockDiagInvMtrx()))
		{
			throw std::runtime_error("The matrix invB is not initialized!");
		}
		// if B is block-diagonal, the S formula simplifies to -invB
		S = -(*im->getSecondDgnBlockDiagInvMtrx());
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
	const TSparseMatrix &Pv = *im->getWeightMtrx();
	const TVector &W = im->getMisclosureVctr();
	const TSparseMatrix &A2 = *im->getCnstrFirstDgnMtrx();
	const TVector &solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix &NBig = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	//--------------- Residuals ---------------//
	// Calculate intermediate matrix
	// S = - inv(P) * Bt *inv( B * inv(P) * Bt )
	// Residuals vector V
	TVector V(nbObs);
	V = S * (A * solution + W);

	//--------------- Sigma 0 a posteriri ---------------//
	int nbObsReduced = nbObs - im->maskData.OIndices.size();
	int nbUnkReduced = nbUnk- im->maskData.UIndices.size();
	//TSparseMatrix PvMasked = im->maskObsColsAndRows(&Pv);
	TSparseMatrix PvRowMasked = im->maskRows(&Pv, im->maskData.OIndices);
	TSparseMatrix PvMasked = im->maskColumns(&PvRowMasked, im->maskData.OIndices);
	TVector VMasked(nbObsReduced);
	//VMasked = im->getEqnMask() * V;
	VMasked = im->maskRows(V, im->maskData.OIndices);
	sigmaZero2Aposteriori = VMasked.transpose() * PvMasked * VMasked;
	if (nbObsReduced + nbCnstr != nbUnkReduced)
		sigmaZero2Aposteriori /= (nbObsReduced - nbUnkReduced + nbCnstr); // NB Redundancy: Takes into account the number of constraints!
	else
		fError += "Number of equations equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObsReduced, nbUnkReduced);
	rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	// ----------Covariance Matrices-----------//
	// only taking into account the unmasked parameters (the active ones), the other entries are 0
	TSparseMatrix Qxx_big(nbUnkReduced + nbCnstr, nbUnkReduced + nbCnstr);
	TSparseMatrix Qxx(nbUnk, nbUnk);
	TDenseMatrix QxxDense(nbUnk, nbUnk);
	QxxDense.setZero();

	// use Cholesky decomposition if nbCnstr=0, otherwise use LU as positive definiteness may be violated
	if (!TSparseUtils::inverse(NBig, Qxx_big, (nbCnstr == 0), (nbCnstr == 0)))
	{
		logCritical() << "The normal matrix NBig could not be inverted!";
		return false;
	}
	std::vector<int> activeUnkn = im->getActiveUnkIndices();
	QxxDense(activeUnkn, activeUnkn) = Qxx_big.topLeftCorner(nbUnkReduced, nbUnkReduced).toDense();

	//Qxx = Qxx_big.topLeftCorner(nbUnk, nbUnk);
	Qxx = QxxDense.sparseView();
	//--------------- Residual covariance matrix: ---------------//
	TSparseMatrix Qvv(nbObs, nbObs);
	if (im->getSecondDgnBlockDiagStatus())
	{ // formula with simplifications if B is invertible Qvv = inv(P) - invB*A*Qxx*At*invBT
		TDenseMatrix QxxATinvBT(nbUnk, nbObs);
		TSparseMatrix invBA(nbObs, nbUnk);
		if (!(im->getSecondDgnBlockDiagInvMtrx()))
		{
			throw std::runtime_error("The matrix invB is not initialized!");
		}
		const TSparseMatrix &invB = *im->getSecondDgnBlockDiagInvMtrx();
		invBA = invB * A;
		QxxATinvBT = Qxx * invBA.transpose();
		Qvv = InvPv - invBA * QxxATinvBT;
	}
	else
	{
		// general formula
		Qvv = -S * B * InvPv - S * A * Qxx * A.transpose() * S.transpose();
	}
	// Copies the matrices into the members of the TResultsMatrices object
	rm->setUnkCovarMtrx(Qxx);
	rm->setResCovarMtrx(Qvv);
	rm->setResidualsVect(V);
	return true;
}

