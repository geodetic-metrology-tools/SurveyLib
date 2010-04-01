/*!  TMeasListenerWrapper
/
/    A Wrapper around a TVMeasurementListener.
/    The wrapper enables a pointer to a measurement listener to be stored
/    in an STL container.
/
/  
/    Patterns:
/    Wrapper around TVMeasurementListener.
/   
/    Copyright 2002 CERN EST/SU. All rights reserved.
/
//////////////////////////////////////////////////////////////////////*/



#ifndef SU_MEAS_LISTENER_WRAPPER
#define SU_MEAS_LISTENER_WRAPPER


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (disable:4786)


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <string>
//using namespace std;
//
class  TVMeasurementListener;
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TMeasListenerWrapper //: public TObject  
{

public:
	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor
		TMeasListenerWrapper();

		/// Constructor taking a pointer to a reference frame
		TMeasListenerWrapper( TVMeasurementListener* );

		/// Copy Constructor 
		TMeasListenerWrapper( const TMeasListenerWrapper& );

		/// Destructor
		virtual  ~TMeasListenerWrapper();
	//@}


	/**@name Member Functions */
	//@{
		/// Return the name of the reference frame
		string  getName() const;

		/// Copy Assignment Operator 
		TMeasListenerWrapper& operator=( const TMeasListenerWrapper& );

		/// Equivalence Operator
		bool operator==( const TMeasListenerWrapper& right ) const;

		/// Less Than Comparison Operator
		bool operator<( const TMeasListenerWrapper& right ) const;

		/// Return a pointer to the measurement listener
		TVMeasurementListener*  getListener() const;

		/// Set the pointer to a measurement listener
		void setListener( TVMeasurementListener* listener );


		/// Set the Ref Frame idetifier
		void setIdentifier( int i );


	//@}


protected:


private:
	TVMeasurementListener*  fListener;

	//ClassDef(TMeasListenerWrapper, 1)
};



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_MEAS_LISTENER_WRAPPER
