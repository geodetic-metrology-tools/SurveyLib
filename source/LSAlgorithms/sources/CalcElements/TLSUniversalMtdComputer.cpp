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
	if (!(im->getGlobalFirstDgnMtrx()) || !(im->getCnstrFirstDgnMtrx()) || !(rm->getSolutionVectByConst()))
	{
		logCritical() << "Some of the design matrices are not initialized!";
		return false;
	}

	const TSparseMatrix& A = *im->getGlobalFirstDgnMtrx();
	const TVector W = im->getGlobalMisclosureVctr(); // W : Misclosures vector ("fermetures")
	const TSparseMatrix &A2 = *im->getCnstrFirstDgnMtrx(); // A2 : First design matrix part related to constraints only
	const TVector &W2 = im->getCnstrMisclosureVctr(); // W2 : Misclosures vector part related to constraints only

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();
	int nbWeights = im->getNbrWeights();

	// set invN1
	TSparseMatrix invN1(nbEq + nbWeights, nbEq + nbWeights);
	if (im->getSecondDgnBlockDiagStatus())
	{
		if (!(im->getGlobalWeightMtrx()) || !(im->getGlobalSecondDgnBlockDiagInvMtrx()))
		{
			throw std::runtime_error("Some of the design matrices are not initialized!");
		}
		const TSparseMatrix &P= *im->getGlobalWeightMtrx();
		const TSparseMatrix &invB= *im->getGlobalSecondDgnBlockDiagInvMtrx();
		invN1 = invB.transpose() * P* invB;
	}
	else
	{ // if B is not block diagonal, invN1 needs to be computed via an explicit inversion
	  // B*invPv*BT is symmetric and positive definite so LDLT can be used
		if (!(im->getGlobalWeightInvMtrx()) || !(im->getGlobalSecondDgnMtrx()))
		{
			throw std::runtime_error("Some of the design matrices are not initialized!");
		}
		const TSparseMatrix &B= *im->getGlobalSecondDgnMtrx();
		const TSparseMatrix &InvP= *im->getGlobalWeightInvMtrx();
		if (!TSparseUtils::inverse(B* InvP* B.transpose(), invN1, true))
		{
			logCritical() << "Matrix B*inv(Pv)*transpose(B) could not be inverted!";
			return false;
		}
		// copy invN1 to resultmatrices only if B is not block diagonal, otherwise it is not needed in the calcRes method
		rm->setInvN1Matrix(invN1);
	}

//	 std::cout << "A=" << std::endl << (*im->getGlobalFirstDgnMtrx()).toDense() << std::endl;
//	 std::cout << "B=" << std::endl << (*im->getGlobalSecondDgnMtrx()).toDense() << std::endl;
//	 std::cout << "Binv=" << std::endl << (*im->getGlobalSecondDgnBlockDiagInvMtrx()).toDense() << std::endl;
//	 std::cout << "P=" << std::endl << (*im->getGlobalWeightMtrx()).toDense() << std::endl;
//	 std::cout << "Pinv=" << std::endl << (*im->getGlobalWeightInvMtrx()).toDense() << std::endl;
//	 std::cout << "Misclosure=" << std::endl << im->getGlobalMisclosureVctr() << std::endl;


	// Calculate Normal matrix N2 = At * inv( B * inv(P) * Bt ) * A , matrix dimensions (u,u)
	// and re-sets this new matrix to the main TLSResultsMatrices object.
	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = A.transpose() * invN1 * A;

	// std::cout << A.toDense() << std::endl;
	// std::cout << (*im->getGlobalWeightMtrx()).toDense() << std::endl;
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
	VBig << A.transpose() * invN1 * W, W2;

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
	// std::cout << "solution= " << solution << std::endl;

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(NBig);
	rm->setSolutionVect(solution);

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
	int nbWeights= im->getNbrWeights();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	if (!(im->getGlobalFirstDgnMtrx()) || !(im->getGlobalSecondDgnMtrx()) || !(im->getGlobalWeightInvMtrx()) || !(rm->getSolutionVectByConst()) || !(rm->getResidualsVectByConst())
		|| !(rm->getResCovarMtrxByConst()))
		throw std::runtime_error("Some of the design matrices are not initialized!");

	const TSparseMatrix& A = *im->getGlobalFirstDgnMtrx();
	const TSparseMatrix& B = *im->getGlobalSecondDgnMtrx();
	const TSparseMatrix& InvP = *im->getGlobalWeightInvMtrx();

	TSparseMatrix S(nbObs + nbWeights, nbEq + nbWeights);
	if (im->getSecondDgnBlockDiagStatus())
	{
		if (!(im->getGlobalSecondDgnBlockDiagInvMtrx()))
		{
			throw std::runtime_error("The matrix invB is not initialized!");
		}
		// if B is block-diagonal, the S formula simplifies to -invB
		S = -(*im->getGlobalSecondDgnBlockDiagInvMtrx());
	}
	else
	{
		if (!(rm->getInvN1MatrixByConst()))
		{
			throw std::runtime_error("The matrix invN1 is not initialized!");
		}
		const TSparseMatrix &invN1 = *rm->getInvN1MatrixByConst(); // NB: invN1 will NOT be recalculated here (just taken from previous results!)
		S = -InvP * B.transpose() * invN1;
	}
	const TSparseMatrix &P = *im->getGlobalWeightMtrx();
	const TVector W = im->getGlobalMisclosureVctr();
	const TSparseMatrix &A2 = *im->getCnstrFirstDgnMtrx();
	const TVector &solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix &NBig = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	//--------------- Residuals ---------------//
	// Calculate intermediate matrix
	// S = - inv(P) * Bt *inv( B * inv(P) * Bt )
	// Residuals vector V
	TVector V(nbObs+nbWeights);
	V = S * (A * solution + W);
	TVector Vobs(nbObs);
	Vobs = V.topRows(nbObs);
	TVector Vweights(nbWeights);
	Vweights = V.topRows(nbWeights);

	//--------------- Sigma 0 a posteriri ---------------//
	sigmaZero2Aposteriori = Vobs.transpose() * im->getObsWeightMtrx() * Vobs;
	if (nbEq + nbCnstr + nbWeights != nbUnk)
	{
		sigmaZero2Aposteriori /= (nbEq - nbUnk + nbCnstr + nbWeights); // NB Redundancy: Takes into account the number of constraints!
	}
	else
		fError += "Number of equations + constraints equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk);
	rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	// ----------Covariance Matrices-----------//

	TSparseMatrix Qxx_big(nbUnk + nbCnstr, nbUnk + nbCnstr);
	TSparseMatrix Qxx(nbUnk, nbUnk);

	// use Cholesky decomposition if nbCnstr=0, otherwise use LU as positive definiteness may be violated
	if (!TSparseUtils::inverse(NBig, Qxx_big, (nbCnstr == 0), (nbCnstr == 0)))
	{
		logCritical() << "The normal matrix NBig could not be inverted!";
		return false;
	}
	Qxx = Qxx_big.topLeftCorner(nbUnk, nbUnk);
	// std::cout << "Qxx=" << Qxx << std::endl;
	//--------------- Residual covariance matrix: ---------------//
	TSparseMatrix Qvv(nbObs + nbWeights, nbObs + nbWeights);
	if (im->getSecondDgnBlockDiagStatus())
	{ // formula with simplifications if B is invertible Qvv = inv(P) - invB*A*Qxx*At*invBT
		TDenseMatrix QxxATinvBT(nbUnk, nbObs + nbWeights);
		TSparseMatrix invBA(nbObs + nbWeights, nbUnk);
		if (!(im->getGlobalSecondDgnBlockDiagInvMtrx()))
		{
			throw std::runtime_error("The matrix invB is not initialized!");
		}
		const TSparseMatrix &invB = *im->getGlobalSecondDgnBlockDiagInvMtrx();
		invBA = invB * A;
		QxxATinvBT = Qxx * invBA.transpose();
		Qvv = InvP - invBA * QxxATinvBT;
	}
	else
	{
		// general formula
		Qvv = -S * B * InvP - S * A * Qxx * A.transpose() * S.transpose();
	}
	// Copies the matrices into the members of the TResultsMatrices object
	TSparseMatrix QvvObs(nbObs, nbObs);
	QvvObs = Qvv.topLeftCorner(nbObs, nbObs);
	rm->setUnkCovarMtrx(Qxx);
	rm->setResCovarMtrx(QvvObs);
	rm->setResidualsVect(Vobs);
	return true;
}

