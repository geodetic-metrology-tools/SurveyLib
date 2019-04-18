// TDataParameters.h
//
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
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
//////////////////////////////////////////////////////////////////////



#ifndef SU_DATA_PARAMETERS
#define SU_DATA_PARAMETERS


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <string>
#include <memory>

#include "TAReferenceFrame.h"
#include "TAngle.h"
#include "TLength.h"
#include "TPointFormat.h"
#include "TObservationFormat.h"
#include "TAStreamFormatter.h"
#include <TRefSystemFactory.h> 

class		TAReferenceFrame;
	
//Class definition
class  TDataParameters //: public TObject 

{
public:
	
	/*///@name Constants
	//@{*/
		
		enum  ECoordUnit {kNotDefined, kMetric, kGons, kDMS};

	//@}


	/*!@name Constructors and Destructors */
	//@{
		/// default constructor
		TDataParameters();

		/// copy constructor
		TDataParameters(const TDataParameters&);

		/// destructor
		virtual  ~TDataParameters();

	//@}
	/*!@name member functions */
	//@{
		/// copy assignment operator
		TDataParameters& operator=(TDataParameters); // Pass-by-value, simpler and better in C++0x
        
        void swap(TDataParameters & other) noexcept;

		/// equivalence operator
		bool	operator==(const TDataParameters& );

		/// Returns "true" if the parameters are defined
		bool	defined() const;

		bool	isOriginExpected() const;

		/// set the reference system identifier
		bool	setRefFrame(TRefSystemFactory::ERefFrame);

		///set the coordinate system
		bool	setCoordSys(const TCoordSysFactory::ECoordSys&);

		///set angle umits
		bool	setAngUnits(const TAngle::EUnits&);

		///setlength units
		bool	setLenUnits(const TLength::EUnits&);
	
		/// set the coordinate units
		bool	setUnits( const TDataParameters::ECoordUnit& );

		/// set the angle precision
		void	setAnglePrecision(const TObservationFormat::EAnglePrecision precision );
		
		/// set the length precision 
		void	setLengthPrecision(const TObservationFormat::ELengthPrecision precision );
		
		///set coordinate precision
		void	setCoordPrecision(const TPointFormat::ECoordPrecision precision);

		/// set angle, length and coordinate precisions, based on the integer arguement
		void	setPrecision(int precision);


		///set the point name's width
		void	setPointNameWidth(const int);

        bool	setLocalSystemOrigin(const TLocalSystemOrigin &);
        bool    setLocalSystemOrigin(std::shared_ptr<TLocalSystemOrigin> lso);
		void	setOriginFile(const std::string &);


		/// get the reference system identifier
		TAReferenceFrame*	getRefFrame() const;

		/// get the reference system identifier
		TRefSystemFactory::ERefFrame	getRefFrameEnumerator() const;

		/// get the coordinate system for the RefSystem data
		TCoordSysFactory::ECoordSys		getCoordinateSystem()  const;
		
		/// get the angle units
		TAngle::EUnits		getAngleUnits() const;
	
		/// get the length units
		TLength::EUnits		getLengthUnits() const;
	
		/// get the angle precision
		TObservationFormat::EAnglePrecision		getAnglePrecision() const;

		/// get the length precision 
		TObservationFormat::ELengthPrecision	getLengthPrecision() const;

		/// get the coord precision 
		TPointFormat::ECoordPrecision			getCoordPrecision() const;

		/// get the point name's width 
		int										getPointNameWidth() const;

		TLocalSystemOrigin* getLocalSystemOrigin() const;
		const std::string& getOriginFile() const;
			

		std::string getRFName() const;
	//@}

private:

	mutable TAReferenceFrame*					fRefFrame;
    TRefSystemFactory::ERefFrame			    fRefFrameEnum;
	ECoordUnit									fCoordUnit;
    TLocalSystemOrigin*             			fLSO;
	std::string										fOriginFile;
	TCoordSysFactory::ECoordSys					fCoordSys;

	TAngle::EUnits								fAngleUnits;
	TLength::EUnits								fLengthUnits;

	TObservationFormat::EAnglePrecision			fAnglePrecision;
	TObservationFormat::ELengthPrecision		fLengthPrecision;
	TPointFormat::ECoordPrecision				fCoordPrecision;

	int											fPointNameWidth;

	TAStreamFormatter::ETextFormat punchFileFormat;
	TAStreamFormatter::ETextFormat resultsFileFormat;
	std::string punchSeparator;
	std::string resultsSeparator;

};

namespace std {
    template<>
    inline void swap(TDataParameters & lhs, TDataParameters & rhs) noexcept
    {
        lhs.swap(rhs);
    }
}


#endif // SU_DATA_PARAMETERS
