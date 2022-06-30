//  TTrf2TrfTransformation.cpp
//
/** A Helmert transformation between two terrestrial reference frames.

	The two reference frames should be terrestrial reference frames


	Patterns:


	Copyright 2021 CERN BE/GM. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations

#include  "TTrf2TrfTransformation.h"
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
#include  "THelmertRefFrameTransform.h"
#include  "TAReferenceFrame.h"
#include  <math.h>
////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////////////////
TTrf2TrfTransformation::TTrf2TrfTransformation()
	: fFrom(0), fTo(0), fTransform(0)
{	// default constructor
}


TTrf2TrfTransformation::TTrf2TrfTransformation(TTerrestrialReferenceFrame* from,
											   TTerrestrialReferenceFrame* to,
											   THelmertTransformation* transform)
: fFrom(from), fTo(to), fTransform(0)
{	// constructor taking pointers to the source and destination reference frames
}

TTrf2TrfTransformation::TTrf2TrfTransformation(TTerrestrialReferenceFrame* from,
												TTerrestrialReferenceFrame* to,
												const TMatrix* coeffTransfoITRF,
												const TMatrix* coeffTransfoETRF )
: fFrom(from), fTo(to), fTransform(0)
{
	fcoeff_toPastITRF.setDimensions(coeffTransfoITRF->numRows(), coeffTransfoITRF->numCols());
	fcoeff_toPastITRF = *coeffTransfoITRF;
	fcoeff_ITRFtoETRF.setDimensions(coeffTransfoETRF->numRows(), coeffTransfoETRF->numCols());
	fcoeff_ITRFtoETRF = *coeffTransfoETRF;
}

TTrf2TrfTransformation::TTrf2TrfTransformation(TTerrestrialReferenceFrame* from,
											   TTerrestrialReferenceFrame* to,
											   const TScaleFactor& enlarg, const TRotation& rot, const TTranslation& transl)
: fFrom(from), fTo(to), fTransform(0)
{
	setTransform(enlarg, rot, transl);
}


TTrf2TrfTransformation::TTrf2TrfTransformation(const  TTrf2TrfTransformation& original)
	: fFrom(0), fTo(0), fTransform(0)
{// copy constructor
	*this = original;
}

TTrf2TrfTransformation::~TTrf2TrfTransformation()
{//destructor
}

//////////////////////////////////////////////////////////////////////
//MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////

void TTrf2TrfTransformation::calcDeltaEpoch()
{
	
	this->setDeltaEpoch (this->fFrom->getEpoch() - this->fTo->getEpoch());

}


TTrf2TrfTransformation& TTrf2TrfTransformation::operator=(const TTrf2TrfTransformation& right)
{	// Copy Assignment operator
	if (this != &right)
	{
		setSourceFrame(right.getSourceFrame());
		setDestinationFrame(right.getDestinationFrame());
	}
	return *this;
}

TTrf2TrfTransformation* TTrf2TrfTransformation::clone() const
{// Return a pointer to a clone of this reference frame
	TTrf2TrfTransformation* result = new TTrf2TrfTransformation();
	result->setSourceFrame(this->getSourceFrame());
	result->setDestinationFrame(this->getDestinationFrame());
	result->setTransform(this->getTransform()->clone());
	return result;
}


TTrf2TrfTransformation* TTrf2TrfTransformation::inverse() const
{// Return a pointer to the inverse of this transformtion

	TTrf2TrfTransformation* inver = this->clone();
	inver->invert();
	return inver;
}


void  TTrf2TrfTransformation::invert()
{
	TTerrestrialReferenceFrame* tmp = getSourceFrame();
	this->setSourceFrame(getDestinationFrame());
	this->setDestinationFrame(tmp);
	this->getTransform()->invert();
	return;
}

TFreeVector TTrf2TrfTransformation::positionToFree(TPositionVector &pv) const
{// Convert a position vector in free vector (required for working with velocities)
	TFreeVector fv;
	fv.setX(pv.getX());
	fv.setY(pv.getY());
	fv.setZ(pv.getZ());
	return fv;
}

bool TTrf2TrfTransformation::isInitialised() const
{
	bool init = false;
	if (fFrom != 0 && fTo != 0 &&
		fFrom->getEpoch() != NO_VALf && fTo->getEpoch() != NO_VALf &&
		fFrom->getSolution() != "noSolution" && fTo->getSolution() != "noSolution")
	{
		init = true;
	}
	return init;
}


bool  TTrf2TrfTransformation::transform(TPositionVector& pv) const
{// transform a position vector
	bool result = false;

	if (isInitialised())
	{
		int solInput = 0, solOutput = 0;
		TLength tX_m(0), tY_m(0), tZ_m(0), vX_m_yr(0), vY_m_yr(0), vZ_m_yr(0); // translation (meters and meters per year)
		TScaleFactor d(0), d_yr(0); // scale factor
		TAngle rX_rad(0), rY_rad(0), rZ_rad(0), rX_rad_yr(0), rY_rad_yr(0), rZ_rad_yr(0); // rotation (radians and radians/year)

		if (fFrom->getSolution().find("ITRF") != std::string::npos)
		{
			if (fFrom->getSolution() != "ITRF 2014")
				solInput = findITRFSolution(fFrom);
		}
		else
		{
			if (fFrom->getSolution() != "ETRF 2008")
				solInput = findETRFSolution(fFrom);
		}
		if (fTo->getSolution().find("ITRF") != std::string::npos)
		{
			if (fTo->getSolution() != "ITRF 2014")
				solOutput = findITRFSolution(fTo);
		}
		else
		{
			if (fTo->getSolution() != "ETRF 2008")
				solOutput = findETRFSolution(fTo);
		}

		// Transformation between 2 ITRF
		if (fFrom->getSolution().find("ITRF") != std::string::npos && fTo->getSolution().find("ITRF") != std::string::npos)
		{
			// Transformation ITRFxx -> ITRF yy @input epoch
			// Velocity and rates

			// No matter the reference frame, coordinates of pv are a sufficient approximation
			TFreeVector velITRF_yy = itrf2014velocity(pv);
			if (fFrom->getSolution() != "ITRF 2014")
			{ // Transformation of velocity vector from ITRF2014 to input reference frame
				velITRF_yy = itrf2014velocityToOtherITRF(fcoeff_toPastITRF, pv, velITRF_yy, fFrom);
			}
			if (fFrom->getSolution() != fTo->getSolution())
			{
				THelmertTransformation itrf2itrfTransfoRate = itrf2itrfRate(fcoeff_toPastITRF, fFrom, fTo);
				velITRF_yy = transformITRFVelocity(pv, velITRF_yy, itrf2itrfTransfoRate);

				// Position
				result = itrf2itrf(fcoeff_toPastITRF, pv, fFrom, fTo);
			}

			// Transfo to ITRFyy @ output epoch
			TReal deltaEpoch = fTo->getEpoch() - fFrom->getEpoch();
			pv = applyPlateVelocity(pv, velITRF_yy, deltaEpoch);
		}

		// Transformation between ITRF and ETRF
		else if (fFrom->getSolution().find("ITRF") != std::string::npos && fTo->getSolution().find("ETRF") != std::string::npos)
		{
			// Find equivalent ITRF
			fTo->setSolution(fTo->getSolution().replace(0, 4, "ITRF"));

			// Transfo ITRFxx -> ITRFyy @ input epoch
			// Velocity and rates
			TFreeVector velITRF_yy = itrf2014velocity(pv);

			if (fFrom->getSolution() != "ITRF 2014")
			{ // Transformation of velocity vector from ITRF2014 to input reference frame
				velITRF_yy = itrf2014velocityToOtherITRF(fcoeff_toPastITRF, pv, velITRF_yy, fFrom);
			}

			if (fFrom->getSolution() != fTo->getSolution())
			{
				// Velocity and rates
				THelmertTransformation itrf2itrfTransfoRate = itrf2itrfRate(fcoeff_toPastITRF, fFrom, fTo);
				velITRF_yy = transformITRFVelocity(pv, velITRF_yy, itrf2itrfTransfoRate);

				// Position
				result = itrf2itrf(fcoeff_toPastITRF, pv, fFrom, fTo);
			}

			// Transfo ITRFyy -> ETRFyy @ input epoch
			fTo->setSolution(fTo->getSolution().replace(0, 4, "ETRF"));

			THelmertTransformation itrf2etrfTransfoRate = itrf2etrfRate(fcoeff_ITRFtoETRF, fTo, 0);
			TFreeVector velETRF_yy = transformETRFVelocity(pv, velITRF_yy, itrf2etrfTransfoRate);
			result = itrf2etrf(fcoeff_ITRFtoETRF, pv, fFrom, fTo, 0);

			// Transfo to ETRFyy @ output epoch
			TReal deltaEpoch = fTo->getEpoch() - fFrom->getEpoch();
			pv = applyPlateVelocity(pv, velETRF_yy, deltaEpoch);
		}

		// Transformation between ETRF and ITRF
		else if (fFrom->getSolution().find("ETRF") != std::string::npos && fTo->getSolution().find("ITRF") != std::string::npos)
		{
			// Transfo ETRFxx -> ITRFxx @ input epoch
			result = itrf2etrf(fcoeff_ITRFtoETRF, pv, fTo, fFrom, 1);

			// Transfo ITRFxx -> ITRFyy @ input epoch
			// Find equivalent ITRF and convert
			fFrom->setSolution(fFrom->getSolution().replace(0, 4, "ITRF"));

			if (fFrom->getSolution() != fTo->getSolution())
			{
				result = itrf2itrf(fcoeff_toPastITRF, pv, fFrom, fTo);
			}

			// Transfo to ITRFFyy @ output epoch
			TFreeVector velITRF_yy = itrf2014velocity(pv);
			if (fTo->getSolution() != "ITRF 2014")
			{ // Transformation of velocity vector from ITRF2014 to input reference frame
				velITRF_yy = itrf2014velocityToOtherITRF(fcoeff_toPastITRF, pv, velITRF_yy, fTo);
			}
			TReal deltaEpoch = fTo->getEpoch() - fFrom->getEpoch();
			pv = applyPlateVelocity(pv, velITRF_yy, deltaEpoch);

			// Reset starting solution
			fFrom->setSolution(fFrom->getSolution().replace(0, 4, "ETRF"));
		}

		// Transformation between ETRF and ETRF
		else if (fFrom->getSolution().find("ETRF") != std::string::npos && fTo->getSolution().find("ETRF") != std::string::npos)
		{
			TFreeVector velETRF_yy;
			if (fFrom->getSolution() != fTo->getSolution())
			{
				// Transfo ETRFxx -> ITRFxx @ input epoch
				result = itrf2etrf(fcoeff_ITRFtoETRF, pv, fTo, fFrom, 1);

				// Transfo ITRFxx -> ITRFyy @ input epoch
				// Find equivalent ITRF and convert
				fFrom->setSolution(fFrom->getSolution().replace(0, 4, "ITRF"));
				fTo->setSolution(fTo->getSolution().replace(0, 4, "ITRF"));
				result = itrf2itrf(fcoeff_toPastITRF, pv, fFrom, fTo);

				// Velocity and rates (ITRF)
				TFreeVector velITRF_yy = itrf2014velocity(pv);
				if (fTo->getSolution() != "ITRF 2014")
				{ // Transformation of velocity vector from ITRF2014 to output reference frame
					velITRF_yy = itrf2014velocityToOtherITRF(fcoeff_toPastITRF, pv, velITRF_yy, fTo);
				}

				// Transfo ITRFyy -> ETRFyy @ input epoch
				fTo->setSolution(fTo->getSolution().replace(0, 4, "ETRF"));
				THelmertTransformation itrf2etrfTransfoRate = itrf2etrfRate(fcoeff_ITRFtoETRF, fTo, 0);
				velETRF_yy = transformETRFVelocity(pv, velITRF_yy, itrf2etrfTransfoRate);
				result = itrf2etrf(fcoeff_ITRFtoETRF, pv, fFrom, fTo, 0);
			}
			else
			{
				// Find equivalent ITRF and convert velocity
				fTo->setSolution(fTo->getSolution().replace(0, 4, "ITRF"));

				TFreeVector velITRF_yy = itrf2014velocity(pv);
				if (fTo->getSolution() != "ITRF 2014")
				{ // Transformation of velocity vector from ITRF2014 to output reference frame
					velITRF_yy = itrf2014velocityToOtherITRF(fcoeff_toPastITRF, pv, velITRF_yy, fTo);
				}

				// Transfo vel ITRFyy -> vel ETRFyy
				fTo->setSolution(fTo->getSolution().replace(0, 4, "ETRF"));
				THelmertTransformation itrf2etrfTransfoRate = itrf2etrfRate(fcoeff_ITRFtoETRF, fTo, 0);
				velETRF_yy = transformETRFVelocity(pv, velITRF_yy, itrf2etrfTransfoRate);
			}

			// Transfo to ETRFyy @ output epoch
			TReal deltaEpoch = fTo->getEpoch() - fFrom->getEpoch();
			pv = applyPlateVelocity(pv, velETRF_yy, deltaEpoch);

			// Reset starting solution
			fFrom->setSolution(fFrom->getSolution().replace(0, 4, "ETRF"));
			
		}
	}
	return result;
}

int TTrf2TrfTransformation::findITRFSolution(TTerrestrialReferenceFrame* refFrame) const
{
	int i = -1;
	if (refFrame->getSolution() == "ITRF 2008")
		i = 0;
	else if (refFrame->getSolution() == "ITRF 2005")
		i = 1;
	else if (refFrame->getSolution() == "ITRF 2000")
		i = 2;
	else if (refFrame->getSolution() == "ITRF 97")
		i = 3;
	else if (refFrame->getSolution() == "ITRF 96")
		i = 4;
	else if (refFrame->getSolution() == "ITRF 94")
		i = 5;
	else if (refFrame->getSolution() == "ITRF 93")
		i = 6;
	else if (refFrame->getSolution() == "ITRF 92")
		i = 7;
	else if (refFrame->getSolution() == "ITRF 91")
		i = 8;
	else if (refFrame->getSolution() == "ITRF 90")
		i = 9;
	else if (refFrame->getSolution() == "ITRF 89")
		i = 10;
	else if (refFrame->getSolution() == "ITRF 88")
		i = 11;

	return i;
}

int TTrf2TrfTransformation::findETRFSolution(TTerrestrialReferenceFrame* refFrame) const
{

	int i = -1;
	if (refFrame->getSolution() == "ETRF 2014")
		i = 0;
	else if (refFrame->getSolution() == "ETRF 2005")
		i = 1;
	else if (refFrame->getSolution() == "ETRF 2000")
		i = 2;
	else if (refFrame->getSolution() == "ETRF 97")
		i = 3;
	else if (refFrame->getSolution() == "ETRF 96")
		i = 4;
	else if (refFrame->getSolution() == "ETRF 94")
		i = 5;
	else if (refFrame->getSolution() == "ETRF 93")
		i = 6;
	else if (refFrame->getSolution() == "ETRF 92")
		i = 7;
	else if (refFrame->getSolution() == "ETRF 91")
		i = 8;
	else if (refFrame->getSolution() == "ETRF 90")
		i = 9;
	else if (refFrame->getSolution() == "ETRF 89")
		i = 10;

	return i;
}




/*
bool  TTrf2TrfTransformation::transform(TFreeVector& fv) const
{// transform a free vector
	bool result = false;

	if (isInitialised())
		result = fTransform->transform(fv);

	return result;
}


bool  TTrf2TrfTransformation::transform(TRotationMatrix& rmx) const
{// transform a Rotation Matrix
	bool result = false;

	if (isInitialised())
		result = fTransform->transform(rmx);

	return result;
}

*/
void TTrf2TrfTransformation::setTransform(THelmertTransformation* helmert)
{// set the transformation
	if (fTransform != 0)
		delete fTransform;

	fTransform = helmert;
}


void TTrf2TrfTransformation::setTransform(const TScaleFactor& scale, const TRotation& rot, const TTranslation& transl)
{
	if (fTransform != 0)
		delete fTransform;

	fTransform = new THelmertTransformation(scale, rot, transl);
	return;
}

TFreeVector TTrf2TrfTransformation::itrf2014velocity(TPositionVector& pv) const {

	TFreeVector pvFree = positionToFree(pv);

	//Zuheir Altamimi, Laurent Métivier, Paul Rebischung, Hélène Rouby, Xavier Collilieux, ITRF2014 plate motion model, Geophysical Journal International, Volume 209, Issue 3, June 2017, Pages 1906–1912, https://doi.org/10.1093/gji/ggx136
	//CERN is located on the eurasian (EURA) plate

	TAngle fOmegaX, fOmegaY, fOmegaZ;
	fOmegaX.setRadiansValue(-0.085 * pow(10, -3) / 3600 * DEG2RAD);    //Uncertainty : +/-0.004 mas/yr
	fOmegaY.setRadiansValue(-0.531 * pow(10, -3) / 3600.0 * DEG2RAD);  //Uncertainty : +/-0.004 mas/yr
	fOmegaZ.setRadiansValue(0.770 * pow(10, -3) / 3600.0 * DEG2RAD);   //Uncertainty : +/-0.004 mas/yr

	TRotationMatrix velocityMat(TRotationMatrix::kRxyz, fOmegaX, fOmegaY, fOmegaZ);
	velocityMat.setC(0, 0, 0);
	velocityMat.setC(1, 1, 0);
	velocityMat.setC(2, 2, 0);

	TFreeVector velocityVec = velocityMat * pvFree * (-1); //Need to multiply by -1 to get the velocity going to the future

	
	return velocityVec;

}

TFreeVector TTrf2TrfTransformation::itrf2014velocityToOtherITRF(TMatrix coeff_toPastITRF, TPositionVector& pv, TFreeVector& velITRF2014, TTerrestrialReferenceFrame* itrfIn) const {

	TFreeVector pv_Free;
	pv_Free.setX(pv.getX());

	std::string name = "itrf14";
	TReal epoch = fFrom->getEpoch();
	std::string solution = "ITRF 2014";
	TTerrestrialReferenceFrame* itrf2014 = new TTerrestrialReferenceFrame(name, TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), epoch, solution);
	THelmertTransformation itrf2itrfTransfoRate = itrf2itrfRate(coeff_toPastITRF, itrf2014, itrfIn);
	TFreeVector velITRF_yy = transformITRFVelocity(pv, velITRF2014, itrf2itrfTransfoRate);

	return velITRF_yy;

}

TFreeVector TTrf2TrfTransformation::transformITRFVelocity(TPositionVector &pv, TFreeVector &velITRF_yy, THelmertTransformation &itrf2itrfTransfoRate) const
{
	TFreeVector pvFree = positionToFree(pv);
	velITRF_yy = velITRF_yy + itrf2itrfTransfoRate.getTranslation().getVector()
							+ pvFree * itrf2itrfTransfoRate.getScaleFactor().getScaleFactor()
							+ itrf2itrfTransfoRate.getRotation().getRotationMatrix() * pvFree;
	return velITRF_yy;
}

TFreeVector TTrf2TrfTransformation::transformETRFVelocity(TPositionVector &pv, TFreeVector &velITRF_yy, THelmertTransformation &itrf2etrfTransfoRate) const
{
	TFreeVector pvFree = positionToFree(pv);
	TFreeVector velETRF_yy = velITRF_yy + itrf2etrfTransfoRate.getTranslation().getVector()
										+ itrf2etrfTransfoRate.getRotation().getRotationMatrix() * pvFree;
	return velETRF_yy;
}

TPositionVector TTrf2TrfTransformation::applyPlateVelocity(TPositionVector& pv, TFreeVector& velocityVec,  TReal deltaEpoch) const {
	TPositionVector pv_transla = pv + velocityVec * deltaEpoch;
	return pv_transla;
}

bool TTrf2TrfTransformation::itrf2itrf(TMatrix coeff_toPastITRF, TPositionVector & pv, TTerrestrialReferenceFrame * itrfIn, TTerrestrialReferenceFrame * itrfOut) const {

	bool result = false;
	int solInput = 0, solOutput = 0;
	TLength tX_m(0), tY_m(0), tZ_m(0), tXv_m_yr(0), tYv_m_yr(0), tZv_m_yr(0); //translation (meters and meters per year)
	TScaleFactor d(0), dv_yr(0); //scale factor
	TAngle rX_rad(0), rY_rad(0), rZ_rad(0), rXv_rad_yr(0), rYv_rad_yr(0), rZv_rad_yr(0); //rotation (radians and radians/year)
	TReal startEpoch = NO_VALf;


	if (itrfIn->getSolution() != "ITRF 2014")
		solInput = findITRFSolution(itrfIn);

	if (itrfOut->getSolution() != "ITRF 2014")
		solOutput = findITRFSolution(itrfOut);

	if (itrfIn->getSolution() != "ITRF 2014" && itrfOut->getSolution() != "ITRF 2014")
	{
		//Get transformation parameters in the matrix
		//Translation, rotations and scale factor and rates
		tX_m.setMetresValue((coeff_toPastITRF(solOutput, 0) - coeff_toPastITRF(solInput, 0)) * MM2M);
		tY_m.setMetresValue((coeff_toPastITRF(solOutput, 1) - coeff_toPastITRF(solInput, 1)) * MM2M);
		tZ_m.setMetresValue((coeff_toPastITRF(solOutput, 2) - coeff_toPastITRF(solInput, 2)) * MM2M);
		d.setScaleFactor((coeff_toPastITRF(solOutput, 3) - coeff_toPastITRF(solInput, 3)) * pow(10, -9));
		rX_rad.setRadiansValue((coeff_toPastITRF(solOutput, 4) - coeff_toPastITRF(solInput, 4)) * pow(10, -3) / 3600 * DEG2RAD);
		rY_rad.setRadiansValue((coeff_toPastITRF(solOutput, 5) - coeff_toPastITRF(solInput, 5)) * pow(10, -3) / 3600 * DEG2RAD);
		rZ_rad.setRadiansValue((coeff_toPastITRF(solOutput, 6) - coeff_toPastITRF(solInput, 6)) * pow(10, -3) / 3600 * DEG2RAD);
		tXv_m_yr.setMetresValue((coeff_toPastITRF(solOutput, 8) - coeff_toPastITRF(solInput, 8)) * MM2M);
		tYv_m_yr.setMetresValue((coeff_toPastITRF(solOutput, 9) - coeff_toPastITRF(solInput, 9)) * MM2M);
		tZv_m_yr.setMetresValue((coeff_toPastITRF(solOutput, 10) - coeff_toPastITRF(solInput, 10)) * MM2M);
		dv_yr.setScaleFactor((coeff_toPastITRF(solOutput, 11) - coeff_toPastITRF(solInput, 11)) * pow(10, -9));
		rXv_rad_yr.setRadiansValue((coeff_toPastITRF(solOutput, 12) - coeff_toPastITRF(solInput, 12)) * pow(10, -3) / 3600 * DEG2RAD);
		rYv_rad_yr.setRadiansValue((coeff_toPastITRF(solOutput, 13) - coeff_toPastITRF(solInput, 13)) * pow(10, -3) / 3600 * DEG2RAD);
		rZv_rad_yr.setRadiansValue((coeff_toPastITRF(solOutput, 14) - coeff_toPastITRF(solInput, 14)) * pow(10, -3) / 3600 * DEG2RAD);
		startEpoch = itrfIn->getEpoch();

	}
	else if (itrfIn->getSolution() == "ITRF 2014")
	{
		tX_m.setMetresValue(coeff_toPastITRF(solOutput, 0) * MM2M);
		tY_m.setMetresValue(coeff_toPastITRF(solOutput, 1) * MM2M);
		tZ_m.setMetresValue(coeff_toPastITRF(solOutput, 2) * MM2M);
		d.setScaleFactor(coeff_toPastITRF(solOutput, 3) * pow(10, -9));
		rX_rad.setRadiansValue(coeff_toPastITRF(solOutput, 4) * pow(10, -3) / 3600 * DEG2RAD);
		rY_rad.setRadiansValue(coeff_toPastITRF(solOutput, 5) * pow(10, -3) / 3600 * DEG2RAD);
		rZ_rad.setRadiansValue(coeff_toPastITRF(solOutput, 6) * pow(10, -3) / 3600 * DEG2RAD);
		tXv_m_yr.setMetresValue(coeff_toPastITRF(solOutput, 8) * MM2M);
		tYv_m_yr.setMetresValue(coeff_toPastITRF(solOutput, 9) * MM2M);
		tZv_m_yr.setMetresValue(coeff_toPastITRF(solOutput, 10) * MM2M);
		dv_yr.setScaleFactor(coeff_toPastITRF(solOutput, 11) * pow(10, -9));
		rXv_rad_yr.setRadiansValue(coeff_toPastITRF(solOutput, 12) * pow(10, -3) / 3600 * DEG2RAD);
		rYv_rad_yr.setRadiansValue(coeff_toPastITRF(solOutput, 13) * pow(10, -3) / 3600 * DEG2RAD);
		rZv_rad_yr.setRadiansValue(coeff_toPastITRF(solOutput, 14) * pow(10, -3) / 3600 * DEG2RAD);
		startEpoch = itrfIn->getEpoch();

	}
	else if (itrfOut->getSolution() == "ITRF 2014") 
	{
		tX_m.setMetresValue(-coeff_toPastITRF(solInput, 0) * MM2M);
		tY_m.setMetresValue(-coeff_toPastITRF(solInput, 1) * MM2M);
		tZ_m.setMetresValue(-coeff_toPastITRF(solInput, 2) * MM2M);
		d.setScaleFactor(-coeff_toPastITRF(solInput, 3) * pow(10, -9));
		rX_rad.setRadiansValue(-coeff_toPastITRF(solInput, 4) * pow(10, -3) / 3600 * DEG2RAD);
		rY_rad.setRadiansValue(-coeff_toPastITRF(solInput, 5) * pow(10, -3) / 3600 * DEG2RAD);
		rZ_rad.setRadiansValue(-coeff_toPastITRF(solInput, 6) * pow(10, -3) / 3600 * DEG2RAD);
		tXv_m_yr.setMetresValue(-coeff_toPastITRF(solInput, 8) * MM2M);
		tYv_m_yr.setMetresValue(-coeff_toPastITRF(solInput, 9) * MM2M);
		tZv_m_yr.setMetresValue(-coeff_toPastITRF(solInput, 10) * MM2M);
		dv_yr.setScaleFactor(-coeff_toPastITRF(solInput, 11) * pow(10, -9));
		rXv_rad_yr.setRadiansValue(-coeff_toPastITRF(solInput, 12) * pow(10, -3) / 3600 * DEG2RAD);
		rYv_rad_yr.setRadiansValue(-coeff_toPastITRF(solInput, 13) * pow(10, -3) / 3600 * DEG2RAD);
		rZv_rad_yr.setRadiansValue(-coeff_toPastITRF(solInput, 14) * pow(10, -3) / 3600 * DEG2RAD);
	}

	//Transformation parameters at start epoch (Altamimi, Z. (2018) EUREF Technical Note 1: Relationship and Transformation between the Internationaland the European Terrestrial Reference Systems, equation 5)
	tX_m.setMetresValue(tX_m.getMetresValue() + tXv_m_yr.getMetresValue() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));
	tY_m.setMetresValue(tY_m.getMetresValue() + tYv_m_yr.getMetresValue() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));
	tZ_m.setMetresValue(tZ_m.getMetresValue() + tZv_m_yr.getMetresValue() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));
	d.setScaleFactor(d.getScaleFactor() + dv_yr.getScaleFactor() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));
	rX_rad.setRadiansValue(rX_rad.getRadiansValue() + rXv_rad_yr.getRadiansValue() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));
	rY_rad.setRadiansValue(rY_rad.getRadiansValue() + rYv_rad_yr.getRadiansValue() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));
	rZ_rad.setRadiansValue(rZ_rad.getRadiansValue() + rZv_rad_yr.getRadiansValue() * (itrfIn->getEpoch() - coeff_toPastITRF(solOutput, 7)));

	TTranslation currentTransla(tX_m, tY_m, tZ_m);
	TRotationMatrix currentRotaMat (TRotationMatrix::kRxyz, -rX_rad, -rY_rad, -rZ_rad);
	currentRotaMat.setC(0, 0, 0);
	currentRotaMat.setC(1, 1, 0);
	currentRotaMat.setC(2, 2, 0);
	TRotation currentRota(currentRotaMat);
	THelmertTransformation itrf2itrfTransfo(d, currentRota, currentTransla);

	TFreeVector pvFree = positionToFree(pv);
	pv = pv + currentTransla.getVector() + pvFree * d.getScaleFactor() + currentRota.getRotationMatrix() * pvFree;

	return result = true;

}

THelmertTransformation TTrf2TrfTransformation::itrf2itrfRate(TMatrix coeff_toPastITRF, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* itrfOut) const {
	int solInput = 0, solOutput = 0;
	TLength tXv_m_yr(0), tYv_m_yr(0), tZv_m_yr(0); //translation rate meters per year
	TScaleFactor d(0), dv_yr(0); //scale factor rate
	TAngle rXv_rad_yr(0), rYv_rad_yr(0), rZv_rad_yr(0); //rotation rate radians/year

	if (itrfIn->getSolution() != "ITRF 2014")
		solInput = findITRFSolution(itrfIn);

	if (itrfOut->getSolution() != "ITRF 2014")
		solOutput = findITRFSolution(itrfOut);

	if (itrfIn->getSolution() != "ITRF 2014" && itrfOut->getSolution() != "ITRF 2014")
	{
		tXv_m_yr.setMetresValue((coeff_toPastITRF(solOutput, 8) - coeff_toPastITRF(solInput, 8)) * MM2M);
		tYv_m_yr.setMetresValue((coeff_toPastITRF(solOutput, 9) - coeff_toPastITRF(solInput, 9)) * MM2M);
		tZv_m_yr.setMetresValue((coeff_toPastITRF(solOutput, 10) - coeff_toPastITRF(solInput, 10)) * MM2M);
		dv_yr.setScaleFactor((coeff_toPastITRF(solOutput, 11) - coeff_toPastITRF(solInput, 11)) * pow(10, -9));
		rXv_rad_yr.setRadiansValue((coeff_toPastITRF(solOutput, 12) - coeff_toPastITRF(solInput, 12)) * pow(10, -3) / 3600 * DEG2RAD);
		rYv_rad_yr.setRadiansValue((coeff_toPastITRF(solOutput, 13) - coeff_toPastITRF(solInput, 13)) * pow(10, -3) / 3600 * DEG2RAD);
		rZv_rad_yr.setRadiansValue((coeff_toPastITRF(solOutput, 14) - coeff_toPastITRF(solInput, 14)) * pow(10, -3) / 3600 * DEG2RAD);
	}
	else if (itrfIn->getSolution() == "ITRF 2014") 
	{
		tXv_m_yr.setMetresValue(coeff_toPastITRF(solOutput, 8) * MM2M);
		tYv_m_yr.setMetresValue(coeff_toPastITRF(solOutput, 9) * MM2M);
		tZv_m_yr.setMetresValue(coeff_toPastITRF(solOutput, 10) * MM2M);
		dv_yr.setScaleFactor(coeff_toPastITRF(solOutput, 11) * pow(10, -9));
		rXv_rad_yr.setRadiansValue(coeff_toPastITRF(solOutput, 12) * pow(10, -3) / 3600 * DEG2RAD);
		rYv_rad_yr.setRadiansValue(coeff_toPastITRF(solOutput, 13) * pow(10, -3) / 3600 * DEG2RAD);
		rZv_rad_yr.setRadiansValue(coeff_toPastITRF(solOutput, 14) * pow(10, -3) / 3600 * DEG2RAD);
	}
	else if (itrfOut->getSolution() == "ITRF 2014")
	{
		tXv_m_yr.setMetresValue(-coeff_toPastITRF(solInput, 8) * MM2M);
		tYv_m_yr.setMetresValue(-coeff_toPastITRF(solInput, 9) * MM2M);
		tZv_m_yr.setMetresValue(-coeff_toPastITRF(solInput, 10) * MM2M);
		dv_yr.setScaleFactor(-coeff_toPastITRF(solInput, 11) * pow(10, -9));
		rXv_rad_yr.setRadiansValue(-coeff_toPastITRF(solInput, 12) * pow(10, -3) / 3600 * DEG2RAD);
		rYv_rad_yr.setRadiansValue(-coeff_toPastITRF(solInput, 13) * pow(10, -3) / 3600 * DEG2RAD);
		rZv_rad_yr.setRadiansValue(-coeff_toPastITRF(solInput, 14) * pow(10, -3) / 3600 * DEG2RAD);
	}

	TTranslation translaRate(tXv_m_yr, tYv_m_yr, tZv_m_yr);
	TRotationMatrix currentRotaRateMat(TRotationMatrix::kRxyz, -rXv_rad_yr, -rYv_rad_yr, -rZv_rad_yr);
	currentRotaRateMat.setC(0, 0, 0);
	currentRotaRateMat.setC(1, 1, 0);
	currentRotaRateMat.setC(2, 2, 0);
	TRotation rotaRate(currentRotaRateMat);
	THelmertTransformation rateTransfo(dv_yr, rotaRate, translaRate);


	return rateTransfo;
}

bool TTrf2TrfTransformation::itrf2etrf(TMatrix coeffITRFyy_toETRFyy, TPositionVector& pv, TTerrestrialReferenceFrame* itrf, TTerrestrialReferenceFrame* etrf, bool inverse) const
{
	// inverse is false if we want to transformfrom itrf to etrf and true if we want to transform from etrf to itrf
	bool result = false;
	int solInput = 0, solEtrf = 0;
	TLength tX_m(0), tY_m(0), tZ_m(0), tXv_m_yr(0), tYv_m_yr(0), tZv_m_yr(0); //translation (meters and meters per year)
	TScaleFactor d(0), dv_yr(0); //scale factor
	TAngle rX_rad(0), rY_rad(0), rZ_rad(0), rXv_rad_yr(0), rYv_rad_yr(0), rZv_rad_yr(0); //rotation (radians and radians/year)
	TReal startEpoch = NO_VALf;

	solEtrf = findETRFSolution(etrf);

	tX_m.setMetresValue(coeffITRFyy_toETRFyy(solEtrf, 0) * MM2M);
	tY_m.setMetresValue(coeffITRFyy_toETRFyy(solEtrf, 1) * MM2M);
	tZ_m.setMetresValue(coeffITRFyy_toETRFyy(solEtrf, 2) * MM2M);
	d.setScaleFactor(coeffITRFyy_toETRFyy(solEtrf, 3) * pow(10, -9));
	rX_rad.setRadiansValue(coeffITRFyy_toETRFyy(solEtrf, 4) * pow(10, -3) / 3600 * DEG2RAD);
	rY_rad.setRadiansValue(coeffITRFyy_toETRFyy(solEtrf, 5) * pow(10, -3) / 3600 * DEG2RAD);
	rZ_rad.setRadiansValue(coeffITRFyy_toETRFyy(solEtrf, 6) * pow(10, -3) / 3600 * DEG2RAD);
	tXv_m_yr.setMetresValue(coeffITRFyy_toETRFyy(solEtrf, 8) * MM2M);
	tYv_m_yr.setMetresValue(coeffITRFyy_toETRFyy(solEtrf, 9) * MM2M);
	tZv_m_yr.setMetresValue(coeffITRFyy_toETRFyy(solEtrf, 10) * MM2M);
	dv_yr.setScaleFactor(coeffITRFyy_toETRFyy(solEtrf, 11) * pow(10, -9));
	rXv_rad_yr.setRadiansValue(coeffITRFyy_toETRFyy(solEtrf, 12) * pow(10, -3) / 3600 * DEG2RAD);
	rYv_rad_yr.setRadiansValue(coeffITRFyy_toETRFyy(solEtrf, 13) * pow(10, -3) / 3600 * DEG2RAD);
	rZv_rad_yr.setRadiansValue(coeffITRFyy_toETRFyy(solEtrf, 14) * pow(10, -3) / 3600 * DEG2RAD);

	//Transformation parameters at start epoch (Altamimi, Z. (2018) EUREF Technical Note 1: Relationship and Transformation between the Internationaland the European Terrestrial Reference Systems, equation 5)
	if (!inverse)
	{
		startEpoch = itrf->getEpoch();
	}
	else
	{
		startEpoch = etrf->getEpoch();
	}
	tX_m.setMetresValue(tX_m.getMetresValue() + tXv_m_yr.getMetresValue() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));
	tY_m.setMetresValue(tY_m.getMetresValue() + tYv_m_yr.getMetresValue() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));
	tZ_m.setMetresValue(tZ_m.getMetresValue() + tZv_m_yr.getMetresValue() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));
	d.setScaleFactor(d.getScaleFactor() + dv_yr.getScaleFactor() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));
	rX_rad.setRadiansValue(rX_rad.getRadiansValue() + rXv_rad_yr.getRadiansValue() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));
	rY_rad.setRadiansValue(rY_rad.getRadiansValue() + rYv_rad_yr.getRadiansValue() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));
	rZ_rad.setRadiansValue(rZ_rad.getRadiansValue() + rZv_rad_yr.getRadiansValue() * (startEpoch - coeffITRFyy_toETRFyy(solEtrf, 7)));


	TTranslation currentTransla(tX_m, tY_m, tZ_m);
	TRotationMatrix currentRotaMat(TRotationMatrix::kRxyz, -rX_rad, -rY_rad, -rZ_rad);
	currentRotaMat.setC(0, 0, 0);
	currentRotaMat.setC(1, 1, 0);
	currentRotaMat.setC(2, 2, 0);
	TRotation currentRota(currentRotaMat);
	TRotationMatrix currentRotaRateMat(TRotationMatrix::kRxyz, -rXv_rad_yr, -rYv_rad_yr, -rZv_rad_yr);
	currentRotaRateMat.setC(0, 0, 0);
	currentRotaRateMat.setC(1, 1, 0);
	currentRotaRateMat.setC(2, 2, 0);
	TRotation currentRotaRate(currentRotaRateMat);
	THelmertTransformation itrf2etrfTransfo(d, currentRota, currentTransla);

	TFreeVector pvFree = positionToFree(pv);

	if (!inverse)
	{
		pv = pv + currentTransla.getVector() + pvFree * d.getScaleFactor() + currentRotaRate.getRotationMatrix() * pvFree * (startEpoch - 1989.0);
	}
	else
	{
		pv = pv - currentTransla.getVector() - pvFree * d.getScaleFactor() - currentRotaRate.getRotationMatrix() * pvFree * (startEpoch - 1989.0);
	}
	
	return result = true;

}

THelmertTransformation TTrf2TrfTransformation::itrf2etrfRate(TMatrix coeffITRFyy_toETRFyy, TTerrestrialReferenceFrame* etrf, bool inverse) const {

	int solInput = 0, solOutput = 0;
	TLength  tXv_m_yr(0), tYv_m_yr(0), tZv_m_yr(0); //translation rate (meters per year)
	TScaleFactor d(0), dv_yr(0); //scale factor rate
	TAngle rX_rad(0), rY_rad(0), rZ_rad(0), rXv_rad_yr(0), rYv_rad_yr(0), rZv_rad_yr(0); //rotation rate (radians/year)

	solOutput = findETRFSolution(etrf);

	tXv_m_yr.setMetresValue(coeffITRFyy_toETRFyy(solOutput, 8) * MM2M);
	tYv_m_yr.setMetresValue(coeffITRFyy_toETRFyy(solOutput, 9) * MM2M);
	tZv_m_yr.setMetresValue(coeffITRFyy_toETRFyy(solOutput, 10) * MM2M);
	dv_yr.setScaleFactor(coeffITRFyy_toETRFyy(solOutput, 11) * pow(10, -9));
	rXv_rad_yr.setRadiansValue(coeffITRFyy_toETRFyy(solOutput, 12) * pow(10, -3) / 3600 * DEG2RAD);
	rYv_rad_yr.setRadiansValue(coeffITRFyy_toETRFyy(solOutput, 13) * pow(10, -3) / 3600 * DEG2RAD);
	rZv_rad_yr.setRadiansValue(coeffITRFyy_toETRFyy(solOutput, 14) * pow(10, -3) / 3600 * DEG2RAD);

	TTranslation translaRate(tXv_m_yr, tYv_m_yr, tZv_m_yr);
	TRotationMatrix currentRotaRateMat(TRotationMatrix::kRxyz, -rXv_rad_yr, -rYv_rad_yr, -rZv_rad_yr);
	currentRotaRateMat.setC(0, 0, 0);
	currentRotaRateMat.setC(1, 1, 0);
	currentRotaRateMat.setC(2, 2, 0);
	TRotation rotaRate(currentRotaRateMat);

	THelmertTransformation rateTransfo(dv_yr, rotaRate, translaRate);
		
	if (inverse) rateTransfo.inverse();
	
	return rateTransfo;
}

//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
