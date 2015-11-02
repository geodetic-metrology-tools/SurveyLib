#ifndef SU_TPTCONVERTER
#define SU_TPTCONVERTER

#include "TAConverter.h"
#include "TRefSystemFactory.h"

/*!\ingroup Converters
 \brief Enables to write points in many different ways.
@{*/

//Class definition
class  TPointConverter : public TAConverter  
{
public:

	/*!@name Constructors and Destructors*/
		//@{
			//!constructor
			TPointConverter(TAStreamFormatter* stream, const TRefSystemFactory::ERefFrame	fRefFrame);

			//!Destructor
			virtual  ~TPointConverter();
		//@}

		//! copy assignment operator
		TPointConverter& operator=(const TPointConverter& source);



	/*!@name Public member functions*/
		//@{
			void	writeName(string ptName, int width);

			void	writeXYZandH(const TPositionVector& pt);

			void	writeXYZandH(const TPositionVector& pt, TReal heightH);


			void	writeXYH(	const int width,
								const int precision,
								const TLength::EUnits unit,
								const string separator,
								const TReal Xparam,
                        		const TReal Yparam,
                        		const TReal Hparam);

			void	writeXYZ(	const int width,
								const int precision,
								const TLength::EUnits unit,
								const string separator,
								const TPositionVector pt);

			void	write3Coordinates(	const int width,
										const int precision,
										const string separator,
										const TPositionVector pt);


			void	writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
											const int width,
											const int precision,
											const TLength::EUnits unit,
											const string separator,
											const TLength Xparam,
											const TLength Yparam,
											const TLength Zparam,
											const string Dparam,
											bool isCovar = false);


			void	writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
											const int width,
											const int precision,
											const string separator,
                                 const TReal Xparam,
                                 const TReal Yparam,
                                 const TReal Zparam,
											const string Dparam,
											bool isCovar = false);

			void	TPointConverter::writeN( const int width,
								 const int precision,
								 TReal N);

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
