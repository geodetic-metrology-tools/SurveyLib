// TDataParameters.h
//
/*! The parameters of a dataset. Identifies the :

  		reference frame, 
			- ref frame origin,
			- ref frame orientation
  		coordinate system,
  		coordinate angle units,
		coordinate length units

    as necessary of the reference system
*/
// Patterns:
//
// 
// Copyright 2000-2002 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_DATA_PARAMETERS
#define SU_DATA_PARAMETERS


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
class		TAReferenceFrame;
#include	"TAReferenceFrame.h"
#include	"TAngle.h"
#include	"TLength.h"
#include	"TPointFormat.h"
#include	"TObservationFormat.h"
#include	"TAStreamFormatter.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////


	
//Class definition
class  TDataParameters //: public TObject 

{
public:
	
	/*//!@name Constants
	//@{
		/*! Enumerator for Reference Frames */
		enum  ERefFrame {kUndefined, kMLA2000Machine, kMLA1985Machine, kCCS,  kCernX0Y0He, kCernXYHg00Machine, 
			kCernXYHg85, kCernXYHg85Machine, kCERNXYHsSphereSPS, kLocalRefFrame, kCernLGatP0, kCGRF,
			kWGS84, kROMA40, kITRF97};

		enum  ECoordUnit {kNotDefined, kMetric, kGons, kDMS};

	//@}*/


	/*!@name Constructors and Destructors */
	//@{
		//! default constructor
		TDataParameters();

		//! copy constructor
		TDataParameters(const TDataParameters&);

		//! destructor
		virtual  ~TDataParameters();

	//@}
	/*!@name member functions */
	//@{
		//! copy assignment operator
		TDataParameters& operator=(const TDataParameters& );

		//! equivalence operator
		bool	operator==(const TDataParameters& );

		bool	defined() const;

		bool	isOriginExpected() const;

		//! set the reference system identifier
		bool	setRefFrame(TDataParameters::ERefFrame);

		//!set the coordinate system
		bool	setCoordSys(const TCoordSysFactory::ECoordSys&);

		//!set angle umits
		bool	setAngUnits(const TAngle::EUnits&);

		//!setlength units
		bool	setLenUnits(const TLength::EUnits&);
	
		//! set the coordinate units
		bool	setUnits( const TDataParameters::ECoordUnit& );

		//! set the angle precision
		void	setAnglePrecision(const TObservationFormat::EAnglePrecision precision );
		
		//! set the length precision 
		void	setLengthPrecision(const TObservationFormat::ELengthPrecision precision );
		
		//!set coordinate precision
		void	setCoordPrecision(const TPointFormat::ECoordPrecision precision);

		//! set angle, length and coordinate precisions, based on the integer arguement
		void	setPrecision(int precision);


		//!set the point name's width
		void	setPointNameWidth(const int);

		bool	setLocalSystemOrigin(const struct LocalSystemOrigin);
	

		//! get the reference system identifier
		TAReferenceFrame*	getRefFrame();

		//! get the reference system identifier
		TDataParameters::ERefFrame	getRefFrameEnumerator() const;

		//! get the coordinate system for the RefSystem data
		TCoordSysFactory::ECoordSys		getCoordinateSystem()  const;
		
		//! get the angle units
		TAngle::EUnits		getAngleUnits() const;
	
		//! get the length units
		TLength::EUnits		getLengthUnits() const;
	
		//! get the angle precision
		TObservationFormat::EAnglePrecision		getAnglePrecision() const;

		//! get the length precision 
		TObservationFormat::ELengthPrecision	getLengthPrecision() const;

		//! get the coord precision 
		TPointFormat::ECoordPrecision			getCoordPrecision() const;

		//! get the point name's width 
		int										getPointNameWidth() const;

		struct LocalSystemOrigin				getLocalSystemOrigin() const;
			
	//@}
	/*!@output stream format access methods*/
	//@{
/*
		virtual void setResultsFileFormat(TAStreamFormatter::ETextFormat resFileFrmt);


		virtual TAStreamFormatter::ETextFormat getResultsFileFormat();


		virtual void setPunchFileFormat(TAStreamFormatter::ETextFormat puncFileFrmt);


		virtual TAStreamFormatter::ETextFormat getPunchFileFormat();


		virtual void setPunchSeparator(string);


		virtual void setResultsSeparator(string);


		virtual string getResultsSeparator();


		virtual string getPunchSeparator();
		*/
	//@}

private:

	TAReferenceFrame*							fRefFrame;
	TDataParameters::ERefFrame					fRefFrameEnum;
	TDataParameters::ECoordUnit					fCoordUnit;
	struct LocalSystemOrigin	fLSO;
	TCoordSysFactory::ECoordSys					fCoordSys;

	TAngle::EUnits								fAngleUnits;
	TLength::EUnits								fLengthUnits;

	TObservationFormat::EAnglePrecision			fAnglePrecision;
	TObservationFormat::ELengthPrecision		fLengthPrecision;
	TPointFormat::ECoordPrecision				fCoordPrecision;

	int											fPointNameWidth;

	TAStreamFormatter::ETextFormat punchFileFormat;
	TAStreamFormatter::ETextFormat resultsFileFormat;
	string punchSeparator;
	string resultsSeparator;
	//ClassDef(TDataParameters, 1)
};


#endif // SU_DATA_PARAMETERS
