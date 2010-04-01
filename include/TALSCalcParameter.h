// TALSCalcParameter.h

/*!
	Definition of an abstract class for ls calc parameters:
	- defines the parameters status with enumerator ELSStatus and structure LSParaStatus
	- defines the name used as identifier for parameters

	Copyright 2003 CERN EST/SU. All rights reserved
*/

#ifndef SU_ABS_PARA
#define SU_ABS_PARA

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>
using namespace std;

//! Abstract class for ls calc parameters 
class TALSCalcParameter {

public:
	
	/*! constant definition */
	enum	ELSStatus {kFixed, kVariable, kNull}; 
	
	/*!@name Constructor / destructor */
	//@{
	/*! Constructor
	\param name parameter's identifier */
	explicit TALSCalcParameter(string name);
	/*! Destructor */
	virtual ~TALSCalcParameter();
	//@}
	/*! Private copy constructor */
	TALSCalcParameter(const TALSCalcParameter& source);

	/*! Overloaded equality operator */
	virtual bool  operator==(const TALSCalcParameter& right) const;

	/*! Returns the parameter's identifier as a string */
	virtual string getName() const;
	/*! Sets the parameter's identifier as a string */
	virtual void setName(string name);


private:
	/*! Private default constructor */
	TALSCalcParameter();
	
	/*! Copy assignment operator */
	TALSCalcParameter&	operator=(const TALSCalcParameter& right);


	string fName;	/*!< string identifying the parameter */

};

//! structure for 3 enumerator values 
/*! used for TLSCalcPosVectorParam and TLSCalcOrientationParam */
struct LSParaStatus {
	TALSCalcParameter::ELSStatus first;
	TALSCalcParameter::ELSStatus second;
	TALSCalcParameter::ELSStatus third;
};
	
#endif //SU_ABS_PARA