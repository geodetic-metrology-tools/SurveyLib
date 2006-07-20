// TAFreeVector.h
//
/** 3D Vector used as a free vector only affected by rotations and scaling*/
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_FREE_VECTOR
#define SU_A_FREE_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations

#include  <iostream>
using namespace std;
//
//#include  "TLength.h"
//#include  "**classname**.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TAFreeVector //: public TObject  
{
public:
	//constants
	enum EVectorStatus {kNull, kKnown};

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TAFreeVector();
	
		/// Destructor
		virtual  ~TAFreeVector();
	//@}


	/**@name Member Functions */
	//@{
		
		/// set the component on X Axis
		virtual void setXYZComponents( const double& x, const double& y, const double& z)=0;

		/// set the component on X Axis
		virtual void setXComponent( const double&)=0;

		/// set the component on Y Axis
		virtual void setYComponent( const double&)=0;

		/// set the componant on Z Axis
		virtual void setZComponent( const double&)=0;

		/// get the component on X Axis
		virtual double getXComponent()const=0;

		/// get the component on Y Axis
		virtual double getYComponent()const=0;

		/// set the component on Z Axis
		virtual double getZComponent()const=0;

		/// set status
		void setStatus(EVectorStatus);

		/// get Status
		bool isNull() const;


	//@}


private:
	/**@name Member Attributes */
		//@{
				EVectorStatus fStatus;

		//@}

	//ClassDef(TAFreeVector, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_A_FREE_VECTOR
