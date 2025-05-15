/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿#ifndef SU_ABS_PARA
#define SU_ABS_PARA

/*!
Definition of an abstract class for ls calc parameters:
- defines the parameters status with enumerator ELSStatus and structure LSParaStatus
- defines the name used as identifier for parameters
*/
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string>

//! Abstract class for ls calc parameters 
class TALSCalcParameter {

public:
	
	/*! constant definition */
	enum	ELSStatus {kFixed, kVariable, kNull}; 
	
	/*!@name Constructor / destructor */
	//@{
	/*! Constructor
	\param name parameter's identifier */
    explicit TALSCalcParameter(const std::string & name);
	/*! Destructor */
	virtual ~TALSCalcParameter();
	//@}
	/*! Private copy constructor */
	TALSCalcParameter(const TALSCalcParameter& source);

	/*! Overloaded equality operator */
	virtual bool  operator==(const TALSCalcParameter& right) const;

	/*! Returns the parameter's identifier as a string */
	std::string getName() const;

	void setName(const std::string & n) { fName = n; }


private:
	/*! Private default constructor */
	TALSCalcParameter();
	
	/*! Copy assignment operator */
	TALSCalcParameter&	operator=(const TALSCalcParameter& right);


	std::string fName;	/*!< string identifying the parameter */

};

//! structure for 3 enumerator values 
/*! used for TLSCalcPosVectorParam and TLSCalcOrientationParam */
struct LSParaStatus {
	TALSCalcParameter::ELSStatus first;
	TALSCalcParameter::ELSStatus second;
	TALSCalcParameter::ELSStatus third;

	LSParaStatus(TALSCalcParameter::ELSStatus defStatus = TALSCalcParameter::kNull) :
		first(defStatus),
		second(defStatus),
		third(defStatus) {}

	void setAll(TALSCalcParameter::ELSStatus status) {
		first = second = third = status;
	}
};
	
#endif //SU_ABS_PARA
