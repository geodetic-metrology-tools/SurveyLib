// TLSCalcPosVectorParam.h


#ifndef SU_POS_VECTOR_PARA
#define SU_POS_VECTOR_PARA

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <list>
#include <string>
#include <array>
//using namespace std;

#include "TRefSystemFactory.h"
#include "TSpatialPoint.h"
#include "TSpatialPosition.h"
#include "TFreeVector.h"
#include "UEOIndices.h"
#include "TALSCalcParameter.h"
#include "TConstants.h"

class TLSCalcPosVectorParam : public TALSCalcParameter
{
public:
	/*!@name Constructors / destructor */
	//@{
		/*! Default constructor */
		TLSCalcPosVectorParam();

		/*! Constructor
		\param spobs provisional value for the spatial point */
		TLSCalcPosVectorParam(TPositionVector pos,struct LSParaStatus status,string name);

		/*! Copy constructor */
		TLSCalcPosVectorParam(const TLSCalcPosVectorParam& source);

		/*! Destructor */
		virtual ~TLSCalcPosVectorParam();
	//@}

	/*!@name public member functions */
	//@{
		using TALSCalcParameter::operator ==;
		
		/*! Copy assignment operator */
		TLSCalcPosVectorParam&	operator=(const TLSCalcPosVectorParam& right);

		//! equivalence operator
		bool	operator==(const TLSCalcPosVectorParam& ) const;

	//@}
			

	/*!@name Access methods : Facade*/
	//@{
		/*! Returns the provisional value of the position vector */
		TPositionVector	getProvisionalValue() const {return fProvisionalValue;}

		/*! Returns the correction value */
		TFreeVector		getCorrection() const {	return fCorrection;}

		/*! Returns the estimated value for the position */
		TPositionVector	getEstimatedValue() const {	return fEstimatedValue;}

		/*! Returns the estimated value for the position */
		const TPositionVector*	getEstimatedValuePointer() const {	return &fEstimatedValue;}

		/*! Returns the estimated precision for the position */
		TFreeVector		getEstimatedPrecision() const {	return fEstimatedPrecision;}

		/*! Returns the covariance element for the position */
		TFreeVector		getEstimatedCovariance() const {return fCovariance;}

		/*! Returns the status of the X-position for calculation */
		TALSCalcParameter::ELSStatus	getXStatus() const {return fStatus.first;}

		/*! Returns the status of the Y-position for calculation */
		TALSCalcParameter::ELSStatus	getYStatus() const {return fStatus.second;}

		/*! Returns the status of the Z-position for calculation */
		TALSCalcParameter::ELSStatus	getZStatus() const {return fStatus.third;}

		/*! Returns the unknown index of the X-position  */
		MatrixIndex			getXIndex() const {	return fPosVectorIndices[0];}

		/*! Returns the unknown index of the Y-position  */
		MatrixIndex			getYIndex() const {return fPosVectorIndices[1];}

		/*! Returns the unknown index of the Z-position  */
		MatrixIndex			getZIndex() const {	return fPosVectorIndices[2];}

		/*!Return the estimated X sigma*/
		TReal				getXSigma() const {return fEstimatedPrecision.getX().getValue();}

		/*!Return the estimated Y sigma*/
		TReal				getYSigma() const {return fEstimatedPrecision.getY().getValue();}

		/*!Return the estimated Z sigma*/
		TReal				getZSigma() const {return fEstimatedPrecision.getZ().getValue();}

		/*!Return the estimated XY covariance*/
		TReal				getXYCovar() const {return fCovariance.getX().getValue();}

		/*!Return the estimated YZ covariance*/
		TReal				getYZCovar() const {return fCovariance.getY().getValue();}

		/*!Return the estimated XZ covariance*/
		TReal				getXZCovar() const {return fCovariance.getZ().getValue();}

		/*!Return the estimated X variance (mm2)*/
		TReal				getXVar() const {return  (powq(getXSigma()*M2MM, 2) );}

		/*!Return the estimated Y variance (mm2)*/
		TDouble				getYVar() const {return  (powq(getYSigma()*M2MM, 2) );}

		/*!Return the estimated Z variance (mm2)*/
		TDouble				getZVar() const {return  (powq(getZSigma()*M2MM, 2) );}

		TReal				getErrorEllMajorAxis() const;

		TReal				getErrorEllMinorAxis() const;

		TAngle				getErrorEllGis() const;

		// returns the three axes of the error ellipsoid
		struct ErrorEllipsoid {
			TReal vx[3]; // Direction (unit)vector of the x-semiaxis
			TReal vy[3]; // Direction (unit)vector of the y-semiaxis
			TReal vz[3]; // Direction (unit)vector of the z-semiaxis
			TReal lx; // Length of the x-semiaxis
			TReal ly; // Length of the y-semiaxis
			TReal lz; // Length of the z-semiaxis
		};
		ErrorEllipsoid getErrorEllipsoid() const;

		/*!Return the estimated X coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getXEstValue() const {return getEstimatedValue().getX();}

		/*!Return the estimated Y coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getYEstValue() const {return getEstimatedValue().getY();}

		/*!Return the estimated Z coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getZEstValue() const {return getEstimatedValue().getZ();}

		/*!Return the estimated X coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getDXValue() const {return (getEstimatedValue().getX()-getProvisionalValue().getX());}

		/*!Return the estimated Y coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getDYValue() const {return (getEstimatedValue().getY()-getProvisionalValue().getY());}

		/*!Return the estimated Z coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getDZValue() const {return (getEstimatedValue().getZ()-getProvisionalValue().getZ());}

		/*!Compute and return the estimated H coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getHEstValue(const TRefSystemFactory::ERefFrame	refFrame) const;

		/*!Compute and return the estimated H coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getHProvValue(const TRefSystemFactory::ERefFrame	refFrame) const;

		/*!Compute and return the estimated H coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getDHValue(const TRefSystemFactory::ERefFrame	refFrame) const {return getHEstValue(refFrame) - getHProvValue(refFrame);}


		/*!Compute and return the estimated N */
		TScalar				getNEstValue(const TRefSystemFactory::EGeoid	geo) const;

		/*!Return the provisional X coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getXProvValue() const {return getProvisionalValue().getX();}

		/*!Return the provisional Y coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getYProvValue() const {return getProvisionalValue().getY();}

		/*!Return the provisional Z coordinate of TLSCalcPosVectorParam (this object is always in CCS)*/
		TScalar				getZProvValue() const {return getProvisionalValue().getZ();}

//		int					getId() const {return getName().getId();}

		/*!Returns the status (Cala, Vxy....)*/
		TSpatialStatus::ESpatialStatus	getGlobalStatus() const;

		string				getPosVecStatus() const;
	//@}

	/*!@name Settings */
	//@{
		/*! Sets the provisional value of the position vector */
		void	setProvisionalValue(TPositionVector pv) {fProvisionalValue = pv; return;}

		/*! Sets the estimated value of the position vector */
		void	setEstimatedValueVector(TPositionVector pv) {fEstimatedValue = pv; return;}

		/*! Sets the correction value */
		void	setCorrection(TFreeVector corr);

		/*! Sets the estimated precision after calculation */
		void	setEstimatedPrecision(TFreeVector ep) {fEstimatedPrecision = ep; return;}

		/*! Sets the covariance after calculation */
		void	setEstimatedCovariance(TFreeVector cov) {fCovariance = cov; return; }

		/*! Sets the status of the vector */
		void	setStatus(struct LSParaStatus stat) {fStatus = stat; return;}

		/*! Sets the position vector parameter's unknown index */
		UEOIndices		setUIndex(UEOIndices ui);

		/*! re-initialises the parameters alterred during or after
			a least squares calculation */
		void	reInitialise();


	//@}

	
protected:

	/*! Sets the estimated value (last estimated + correction) */
	void	setEstimatedValue();


private:

	TPositionVector			fProvisionalValue; /*!< position's provisional value */
	TFreeVector				fCorrection; /*!< position's correction after calculation  */
	TPositionVector			fEstimatedValue; /*!< position's estimated value after calculation */
	TFreeVector				fEstimatedPrecision; /*!< position's estimated precision after calculation */
	TFreeVector				fCovariance; 

	struct LSParaStatus		fStatus; /*!< position parameter's status for calculation */
	MatrixIndex				fPosVectorIndices[3]; /*!< position parameter's unknown indices for calculation */
};

/*!@name Constants definition */
//@{
/*! List of ls calc position vector observations  */
typedef list< TLSCalcPosVectorParam >		LSPosVecContainer;
/*! Iterator of the list of ls calc position vector observations */
typedef LSPosVecContainer::iterator			LSPosVecIter;
/*! Constant iterator of the list of ls calc position vector observations */
typedef LSPosVecContainer::const_iterator	LSPosVecConstIter;
//@}


#endif //SU_POS_VECTOR_PARA
