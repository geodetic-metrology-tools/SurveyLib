// TLSCalcPosVectorParam.cpp
#include <stdio.h>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>


#include "lsalgo/TLSCalcPosVectorParam.h"
#include "TAGeoidModel.h"
#include "TAReferenceFrame.h"

//////////////////////////////////////////////////////////////////////
// CONSTRUCTORS / DESTRUCTOR
//////////////////////////////////////////////////////////////////////
TLSCalcPosVectorParam::TLSCalcPosVectorParam():
TALSCalcParameter(""),
fProvisionalValue(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fCorrection(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fEstimatedValue(fProvisionalValue),
fEstimatedPrecision(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fCovariance(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian)
{// Default constructor
	for (int i=0;i<3;i++)
		fPosVectorIndices[i] = 0;
	fStatus.first = TALSCalcParameter::kVariable;
	fStatus.second = TALSCalcParameter::kVariable;
	fStatus.third = TALSCalcParameter::kVariable;
}


TLSCalcPosVectorParam::TLSCalcPosVectorParam(TPositionVector pos,struct LSParaStatus status,
											 string name ):
TALSCalcParameter(name),
fProvisionalValue(pos),
fStatus(status),
fCorrection(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fEstimatedValue(fProvisionalValue),
fEstimatedPrecision(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fCovariance(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian)
{// Constructor taking provisional value and parameter status as argument
	for (int i=0;i<3;i++)
		fPosVectorIndices[i] = 0;
}




TLSCalcPosVectorParam::TLSCalcPosVectorParam(const TLSCalcPosVectorParam& source):
TALSCalcParameter(source.getName()),
fProvisionalValue(source.fProvisionalValue),
fCorrection(source.fCorrection),
fEstimatedValue(source.fEstimatedValue),
fEstimatedPrecision(source.fEstimatedPrecision),
fCovariance(source.fCovariance)
{// Copy constructor 
	fStatus = source.fStatus; 
	for (int i=0;i<3;i++)
		fPosVectorIndices[i] = source.fPosVectorIndices[i]; 
}



TLSCalcPosVectorParam::~TLSCalcPosVectorParam() 
{// Destructor
}


// Copy assignement operator
TLSCalcPosVectorParam& TLSCalcPosVectorParam::operator =(const TLSCalcPosVectorParam& right) 
{
	if (this != &right)
	{
		this->setName( right.getName() );
		fProvisionalValue = right.fProvisionalValue; 
		fCorrection = right.fCorrection; 
		fEstimatedValue = right.fEstimatedValue; 
		fEstimatedPrecision = right.fEstimatedPrecision;
		fCovariance = right.fCovariance;
		fStatus = right.fStatus;
		for (int i=0;i<3;i++)
			fPosVectorIndices[i] = right.fPosVectorIndices[i]; 
	}

	return *this;
}


// equivalence operator
bool	TLSCalcPosVectorParam::operator==(const TLSCalcPosVectorParam& right) const
{
	bool equal = false;

	if( this->getName() == right.getName()
		&& fProvisionalValue == right.fProvisionalValue 
		&& fCorrection == right.fCorrection 
		&& fEstimatedValue == right.fEstimatedValue
		&& fEstimatedPrecision == right.fEstimatedPrecision
		&& fCovariance == right.fCovariance
		&& fStatus.first == right.fStatus.first
		&& fStatus.second == right.fStatus.second
		&& fStatus.third == right.fStatus.third
		&& fPosVectorIndices[0] == right.fPosVectorIndices[0]
		&& fPosVectorIndices[1] == right.fPosVectorIndices[1]
		&& fPosVectorIndices[2] == right.fPosVectorIndices[2]
		) 
	{
		equal = true;
	}

	return equal;
}


// re-initialises the parameters alterred during or after a least squares calculation
void	TLSCalcPosVectorParam::reInitialise()
{
	TFreeVector zeroVec(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian);
	fCorrection = zeroVec;
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = zeroVec;
	fCovariance = zeroVec;

	return;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////
TSpatialStatus::ESpatialStatus	TLSCalcPosVectorParam::getGlobalStatus() const
{/*!Retutns the status (Cala, Vxy....)*/
	TSpatialStatus::ESpatialStatus status = TSpatialStatus::kUnknown;

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVx;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVy;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVz;}

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVxy;}

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVxz;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVyz;}

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVxyz;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kCala;}
	
	return status;
}


string		TLSCalcPosVectorParam::getPosVecStatus() const
{
	string res = "unknown";
	TSpatialStatus::ESpatialStatus status = this->getGlobalStatus();
	
	switch(status)
	{
		case TSpatialStatus::kUnknown :
			res = "unknown";
			break;

		case TSpatialStatus::kVx :
			res = "VX";
			break;

		case TSpatialStatus::kVy :
			res = "VY";
			break;

		case TSpatialStatus::kVz :
			res = "VZ";
			break;

		case TSpatialStatus::kVxy :
			res = "VXY";
			break;

		case TSpatialStatus::kVxz :
			res = "VXZ";
			break;

		case TSpatialStatus::kVyz :
			res = "VYZ";
			break;

		case TSpatialStatus::kVxyz :
			res = "VXYZ";
			break;

		case TSpatialStatus::kCala :
			res = "CALA";
			break;

		case TSpatialStatus::kPosNull :
			res = "UNDEFINED";
			break;
	}



	return res;
}



///////////////////////////////////////////////////////////////////////////
// PUBLIC & PROTECTED SETTINGS METHODS
///////////////////////////////////////////////////////////////////////////
void	TLSCalcPosVectorParam::setCorrection(TFreeVector corr)
{// Sets the correction value 
	fCorrection = corr;
	setEstimatedValue();
}


// Sets the estimated value (last estimated + correction) 
void	TLSCalcPosVectorParam::setEstimatedValue() 
{
	fEstimatedValue += fCorrection;
}



UEOIndices		TLSCalcPosVectorParam::setUIndex(UEOIndices ui) 
{// Sets the position vector parameter's unknown index 

	if (fStatus.first == TALSCalcParameter::kVariable)
		fPosVectorIndices[0] = ui.UIndex ++;

	if (fStatus.second == TALSCalcParameter::kVariable)
		fPosVectorIndices[1] = ui.UIndex ++;

	if (fStatus.third == TALSCalcParameter::kVariable)
		fPosVectorIndices[2] = ui.UIndex ++;
	
	return ui;
}




TLength		TLSCalcPosVectorParam::getHEstValue(const TRefSystemFactory::ERefFrame	refFrame) const
{
	TLength h;
	TAReferenceFrame* refH = (TRefSystemFactory::getRefSystemFactory()->getRefFrame(refFrame));
	TAReferenceFrame* ccs = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS);
	if(refH != ccs)
	{
		string name = refH->getName();
		TSpatialPosition pos (ccs);
		pos.setCoordinates(getEstimatedValue());
		pos.transform(refH);
		h = pos.getCoordinates(TCoordSysFactory::k2DPlusH).getH();
	}
	return h;
}

TLength		TLSCalcPosVectorParam::getHProvValue(const TRefSystemFactory::ERefFrame	refFrame) const
{
	TLength h;
	TAReferenceFrame* refH = (TRefSystemFactory::getRefSystemFactory()->getRefFrame(refFrame));
	TAReferenceFrame* ccs = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS);
	if(refH != ccs)
	{
		string name = refH->getName();
		TSpatialPosition pos (ccs);
		pos.setCoordinates(getProvisionalValue());
		pos.transform(refH);
		h = pos.getCoordinates(TCoordSysFactory::k2DPlusH).getH();
	}
	return h;
}





TLength		TLSCalcPosVectorParam::getNEstValue(const TRefSystemFactory::EGeoid	geo) const
{


	//Toujours en CCS pendant le calcul TAReferenceFrame* pointRefFrame = getStreamFormatter()->getReferenceFrame();
	TAReferenceFrame* ccs = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS);
	TAGeoidModel* geoid = TRefSystemFactory::getRefSystemFactory()->getGeoid(geo);

	TSpatialPosition pos (ccs);
	pos.setCoordinates(getEstimatedValue());
	TLength N = geoid->getN(pos);

	return N;
}


TLength		TLSCalcPosVectorParam::getErrorEllMajorAxis() const
{
	TReal vxy = getXYCovar().getMMetresValue();
	TReal sx2 = powq(getXSigma().getMMetresValue(), 2) ;
	TReal sy2 = powq(getYSigma().getMMetresValue(), 2) ;
	TReal gdAxe = (LITERAL(1.0)/sqrtq(LITERAL(2.0))) * sqrtq( sx2 + sy2 + sqrtq( powq((sy2 - sx2), 2) + (LITERAL(4.0) * vxy * vxy) ) );
	
	TLength res;
	res.setMMetresValue(gdAxe);
	return res;
}

	
TLength		TLSCalcPosVectorParam::getErrorEllMinorAxis() const
{
	TReal vxy = getXYCovar().getMMetresValue();
	TReal sx2 = powq(getXSigma().getMMetresValue(), 2) ;
	TReal sy2 = powq(getYSigma().getMMetresValue(), 2) ;
	TReal ptAxe = (LITERAL(1.0)/sqrtq(LITERAL(2.0))) * sqrtq( sx2 + sy2 - sqrtq( powq((sy2 - sx2), 2) + (LITERAL(4.0) * vxy *vxy) ) );
	
	TLength res;
	res.setMMetresValue(ptAxe);
	return res;
}

	
TAngle		TLSCalcPosVectorParam::getErrorEllGis() const
{
	TReal vxy = getXYCovar().getMMetresValue();
	TReal sx2 = powq(getXSigma().getMMetresValue(), 2) ;
	TReal sy2 = powq(getYSigma().getMMetresValue(), 2) ;
	TAngle gis (( LITERAL(0.5)) * TAngle::aTan2(2*vxy , (sy2 - sx2) ) );
	
	TReal testAffichage = gis.getGonsValue();
	TAngle deuxCentGrad;
	deuxCentGrad.setGonsValue(200);
	if(testAffichage > 200)
	{
		gis = gis - deuxCentGrad;
	}

	return gis;
}


TLSCalcPosVectorParam::ErrorEllipsoid TLSCalcPosVectorParam::getErrorEllipsoid() const {
	Eigen::Matrix3d m;

	m << pow2(getXSigma().getMMetresValue()),     getXYCovar().getMMetresValue(),     getXZCovar().getMMetresValue(),
             getXYCovar().getMMetresValue(),  pow2(getYSigma().getMMetresValue()),    getYZCovar().getMMetresValue(),
		     getXZCovar().getMMetresValue(),      getYZCovar().getMMetresValue(), pow2(getZSigma().getMMetresValue());

	Eigen::EigenSolver<Eigen::Matrix3d> ev(m);
	
	const auto& evals(ev.eigenvalues());
	const auto& evecs(ev.eigenvectors());
	
	/* The length of the semimajor axes of the 95% confidence ellipsoid are
	   Fv * [eigenvalue_0, eigenvalue_1, eigenvalue_2] with Fv being the 95% 
	   percentile of the Fisher distribution for three degrees of freedom (approx. 7.80).
	   We are interested in the one-sigma-level, so our multiplier actualy is 1.0.

	   We need the eigenvectors as well since they are the direction sof the ellipsoid's axes.
	   
	   Source:
	   Parameter Estimation and Inverse Problems
	   Richard C. Aster, Brian Borchers, Clifford H. Thurber
	   Academic Press, 2013 - 360 pages
	   (on page 36)
	*/

	ErrorEllipsoid ell = {
		// Indexing is (row, column): Each column corresponds to one eigenvector
		{evecs(0,0).real(), evecs(1,0).real(), evecs(2,0).real()},
		{evecs(0,1).real(), evecs(1,1).real(), evecs(2,1).real()},
		{evecs(0,2).real(), evecs(1,2).real(), evecs(2,2).real()},
		sqrtq(evals(0).real()),
		sqrtq(evals(1).real()),
		sqrtq(evals(2).real()),
	};

	return ell;
}




