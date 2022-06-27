//  TADataSet.h
/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
//
/*! An abstract data set for computation programs with input files.  
  
    Patterns:
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_DATASET
#define SU_DATASET


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
#include	"TFileParameters.h"
#include	"TDataParameters.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup projectFrameWork

  @{*/


//Class definition
class  TADataSet //: public TObject  
{
public:

	/*!@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TADataSet();

		/*!
		\brief Constructor

		\param fp : TFileParameters
		\param dp : TDataParameters*/
		TADataSet(const  TFileParameters& fp, const TDataParameters& dp);

		/*!
		\brief Constructor

		\param dp : TDataParameters*/
		TADataSet(const TDataParameters& dp);

		/// Copy Constructor 
		TADataSet( const TADataSet& );

		/// Destructor
		virtual  ~TADataSet();
	//@}


	/*!@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TADataSet& operator=( const TADataSet& );

		/// indicates if file parameters have been set
		bool  fileKnown() const;

		/// clear the file parameters
		//void  fileDeleted();

		/// returns a copy of the file parameters
		TFileParameters  getFileParams() const;

		/// set the file parameters
		void  setFileParams(const TFileParameters&);

		/// returns a copy of the data parameters
		TDataParameters  getDataParams() const;

		/// set copy ofthe data parameters
		void  setDataParams(const TDataParameters&);

		/*!
		\brief check if the Data Set is Saved

		\return true if it's saved*/
		bool isSaved();

		/*!
		\brief put the saved status to the value of b

		\return b*/
		void saved();
	//@}


	/*!@name Wrapper TDataParameters Functions */
	//@{
		bool	isDataParamsDefined() const;

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
		
		/// set coordinate precision
		void	setCoordPrecision(const TPointFormat::ECoordPrecision precision);

		/// set the point name's width
		void	setPointNameWidth(const int);

		/// set the origin of the local system used
		bool	setLocalSystemOrigin(std::shared_ptr <TLocalSystemOrigin>);

		/// set the epoch of the coordinates
		void	setCoordEpoch(const TReal epoch);

		/// set the solution of the coordinates
		void	setSolution(const std::string solution);

		/// get the reference system identifier
		TAReferenceFrame*	getRefFrame();

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

		/// get a pointer to the origin of the local system used
        TLocalSystemOrigin* getLocalSystemOrigin() const;

		/// get the epoch of the coordinates
		TReal getCoordEpoch() const;

		/// get the solution of the coordinates
		std::string getSolution() const;


	//@}
	
		
	/*!@name Wrapper TFileParameters Functions */
	//@{
		/// set the full filename, both path and name
		bool  setFileName( const std::string& );
		/// set the file type
		bool  setTypeFormat( const std::string& );
		/// clear the file parameters and set the default values 
		void  defaultValues();

		/// get the full filename, both path and name
		std::string  getFileName()  const;
		/// get the name of the file
		std::string  getName()  const;
		/// get the path for the file
		std::string  getPath()  const;
		/// get the file type
		TFileParameters::EFileType  getType()  const;
		/// get the text stream's format
		TFileParameters::ETextFormat  getFormat() const;
		/// indicates if the file name, type and format have been set
		bool  isFileParamsDefined()  const;
	//@}

	/*!@output stream format access methods*/
	//@{
	
		/// set results file format
		virtual void setResultsFileFormat(TAStreamFormatter::ETextFormat resFileFrmt);

		/// get results file format
		virtual TAStreamFormatter::ETextFormat getResultsFileFormat();

		/// set punch file format
		virtual void setPunchFileFormat(TAStreamFormatter::ETextFormat puncFileFrmt);

		/// get punch file format
		virtual TAStreamFormatter::ETextFormat getPunchFileFormat();

		/// set punch seperator
		virtual void setPunchSeparator(std::string);

		/// set results seperator
		virtual void setResultsSeparator(std::string);

		/// get results seperator
		virtual std::string getResultsSeparator();

		/// get punch seperator
		virtual std::string getPunchSeparator();

		/// get the format for the spacing between the data
		bool isSpaceBetweenData();
		
		/// set no space between the data
		void setNoSpaceBetweenData();

		/// set a space between the data
		void setSpaceBetweenData();

		/// set the format of the file
		void setFormatType(std::string fmtType);

		/// get the format of the file
		std::string getFormatType();
	//@}



private:

	/*!name Private Attributes*/
	//@{
		bool						fLineSpacing;

		///TFileParameters
		TFileParameters				fFileParams;

		///TDataParameters
		TDataParameters				fDataParams;

		///saved status : bool
		bool						fSaved;

		std::string						fFormatType;

		TAStreamFormatter::ETextFormat fPunchFileFormat;

		TAStreamFormatter::ETextFormat fResultsFileFormat;

		std::string fPunchSeparator;

		std::string fResultsSeparator;
	//@}

	//ClassDef(TADataSet, 1)
};

/*@}*/

#endif // SU_DATASET
