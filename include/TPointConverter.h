////////////////////////////////////////////////////////////////////
// TPointConverter
/*!
Write point for an output LGC file
and sends the appropriate messages

Patterns:

 
Copyright 2003 CERN EST/SU. All rights reserved.
*/
/////////////////////////////////////////////////////////////////////

#ifndef SU_TPTCONVERTER
#define SU_TPTCONVERTER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

////////////////////////////////////////////////////////////////
// Forward declarations

#include "TAConverter.h"
#include "TRefSystemFactory.h"

// typedefs
////////////////////////////////////////////////////////////////

/*!\ingroup ????

@{*/

//Class definition
class  TPointConverter : public TAConverter  
{
public:

	/*!@name Constructors and Destructors*/
		//@{
			//!constructor
			TPointConverter(TAStreamFormatter* stream,
							const TRefSystemFactory::ERefFrame	fRefFrame);

			//!Destructor
			virtual  ~TPointConverter();
		//@}

		//! copy assignment operator
		TPointConverter& operator=(const TPointConverter& source);



	/*!@name Public member functions*/
		//@{

			void	writeName(LSPosVecConstIter pt, int width);

			void	writeName(string ptName, int width);

			void	writeXYZandH(const LSPosVecConstIter pt);

			void	writeXYZandH(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const string separator,
									LSPosVecConstIter pt);


			void	writeXYZorH(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const string separator,
									LSPosVecConstIter pt);

			void	writeXYH(	const int width,
								const int precision,
								const TLength::EUnits unit,
								const string separator,
								LSPosVecConstIter pt);

			void	writeXYZ(	const int width,
								const int precision,
								const TLength::EUnits unit,
								const string separator,
								LSPosVecConstIter pt);

			void	writeXYZ(	const int width,
								const int precision,
								const TLength::EUnits unit,
								const string separator,
								const TPositionVector pt);

			void	write3Coordinates(	const int width,
										const int precision,
										const TLength::EUnits unit,
										const string separator,
										const TPositionVector pt);


			void	writeN( const int width,
							const int precision,
							const TLength::EUnits unit,
							LSPosVecConstIter pt);


			void	writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
											const int width,
											const int precision,
											const TLength::EUnits unit,
											const string separator,
											const TLength Xparam,
											const TLength Yparam,
											const TLength Zparam,
											const string Dparam);

	
			void	writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
											const int width,
											const int precision,
											const string separator,
											const TDouble Xparam,
											const TDouble Yparam,
											const TDouble Zparam,
											const string Dparam);

			bool	isInLocalSystem() const {return	fLocalSys;}

		//@}


private:

			//!constructor
			TPointConverter();


private:


		bool							fLocalSys;

		TRefSystemFactory::ERefFrame	fRefFrame;
};

/*@}*/

#endif // SU_TPTCONVERTER