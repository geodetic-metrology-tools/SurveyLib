/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_SCALAR_PARA
#define SU_SCALAR_PARA

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <list>
#include <string>

#include "TSpatialPoint.h"
#include "TSpatialPosition.h"
#include "TFreeVector.h"
#include <UEOIndices.h>
#include "TALSCalcParameter.h"

class TLSCalcScalarParam : public TALSCalcParameter
{
public:
	/*!@name Constructors / destructor */
	//@{
		/*! Default constructor */
		TLSCalcScalarParam();
		/*! Constructor
		/param stores provisional value for the scale */
      TLSCalcScalarParam(TReal pos, ELSStatus status, std::string name);
		/*! Copy constructor */
		TLSCalcScalarParam(const TLSCalcScalarParam& source);
		/*! Destructor */
		virtual ~TLSCalcScalarParam();
	//@}


	/*!@name Access methods */
	//@{
		/*! Returns the provisional value of the scale */
		TReal getProvisionalValue() const;
		/*! Returns the correction value */
      TReal getCorrection() const;
		/*! Returns the estimated value for the scale */
      TReal getEstimatedValue() const;
		/*! Returns the estimated precision for the scale */
      TReal getEstimatedPrecision() const;
		/*! Returns the covariance element for the scale */
      TReal getEstimatedCovariance() const;
		/*! Returns the status of the scale for calculation */
		TALSCalcParameter::ELSStatus getStatus() const;
		/*!Returns the status (Cala, Vxy....)*/
		TSpatialStatus::ESpatialStatus getGlobalStatus() const;
		void resetValues();
	//@}

	/*!@name Settings */
	//@{
		/*! Sets the provisional value of the scale */
      void setProvisionalValue(TReal pv);
		/*! Sets the estimated value of the scale */
      void setEstimatedValue(TReal ev);
		/*! Sets the correction value */
      void setCorrection(TReal corr);
		/*! Sets the estimated precision after calculation */
      void setEstimatedPrecision(TReal ep);
		/*! Sets the covariance after calculation */
      void setEstimatedCovariance(TReal cov);
		/*! Sets the status of the scale */
		void setStatus(ELSStatus stat);
		
		/*! Sets the position vector parameter's unknown index */
		
		UEOIndices setUIndex(UEOIndices ui);
		MatrixIndex getScalarIndex();

		/*! re-initialises the parameters alterred during or after
			a least squares calculation */
		void	reInitialise();
	//@}

	
protected:

	/*! Sets the estimated value (provisional + correction) */
	void	setEstimatedValue();


private:

	/*! Copy assignment operator */
	TLSCalcScalarParam&	operator=(const TLSCalcScalarParam& right);

	TReal	fProvisionalValue; /*!< scale's provisional value */
   TReal	fCorrection; /*!< scale's correction after calculation  */
   TReal	fEstimatedValue; /*!< scale's estimated value after calculation */
   TReal	fEstimatedPrecision; /*!< scale's estimated precision after calculation */
   TReal	fCovariance;
	
	TALSCalcParameter::ELSStatus		fStatus; /*!< scale parameter's status for calculation */
	MatrixIndex			fScalarIndices[1]; /*!< scalar parameter's unknown indices for calculation */
};

/*!@name Constants definition */
//@{
/*! List of ls calc position vector observations  */
typedef std::list< TLSCalcScalarParam > LSScalarContainer;
/*! Iterator of the list of ls calc position vector observations */
typedef LSScalarContainer::iterator LSScalarIter;
/*! Constant iterator of the list of ls calc position vector observations */
typedef LSScalarContainer::const_iterator	LSScalarConstIter;
//@}


#endif //SU_POS_VECTOR_PARA
