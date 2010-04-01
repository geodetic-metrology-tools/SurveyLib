// TAQtStreamFormatter.h: 
//
// Abstract Base Class for a QTextStream Formatter.
// Enables the output of all the standard survey objects.
//
//
// Patterns:
// Maintains a reference to a QTextStream following 
// the decorator pattern.
// 
//
// Copyright 1999,2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#ifndef SU_A_TEXT_STREAM_FORMATTER
#define SU_A_TEXT_STREAM_FORMATTER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning(disable:4786)


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <string>
using namespace std;
//
class  TAngleFilter;
class  TLengthFilter;
class  TSpatialPointName;
class  TSpatialPoint;
class  TSpatialPositionFilter;
class  TAQtStreamFormatter;
#include  "TAngle.h"
#include  "TLength.h"
#include  "TSpatialPosition.h"
#include  "TVReferenceFrame.h"
#include  "QTextStream.h"
#include "TPointFormat.h"
#include "TObservationFormat.h"
// typedefs
typedef TAQtStreamFormatter & (*TSFFUNC)(TAQtStreamFormatter &);// manipulator function
////////////////////////////////////////////////////////////////



//Class definition
class TAQtStreamFormatter : public QTextStream //, public TObject  
{
public:

	/**@name Constants */
	//@{
		enum  ETextFormat { kNull, kFreeFormat };

	//@}


	// constructors and destructors
	//TAQtStreamFormatter();
	TAQtStreamFormatter( QTextStream * );
	virtual ~TAQtStreamFormatter() = 0;

	//member functions
    virtual  TAngle::EUnits  setAngleUnits( TAngle::EUnits );
    virtual  TLength::EUnits  setLengthUnits( TLength::EUnits );
    virtual  TSpatialPosition::ECoordToken  setCoordToken( TSpatialPosition::ECoordToken );
	virtual  TSpatialPosition::ECoordinateSystem  setCoordSys( TSpatialPosition::ECoordinateSystem );
	virtual  TVReferenceFrame*  setReferenceFrame( TVReferenceFrame * );

    virtual  TAngle::EUnits  getAngleUnits() const;
    virtual  TLength::EUnits  getLengthUnits() const;
    virtual  TSpatialPosition::ECoordToken  getCoordToken() const;
	virtual  TSpatialPosition::ECoordinateSystem  getCoordSys() const;
	virtual  TVReferenceFrame*  getReferenceFrame() const;

	virtual void				setPointFormat(TPointFormat ptFormat);
	virtual void				setObsFormat(TObservationFormat ptFormat);

	virtual const TPointFormat*			getPointFormat() const;
	virtual const TObservationFormat*	getObsFormat() const;

	virtual QString					separator() const = 0;


	virtual  TAQtStreamFormatter  &operator>>( TAngle & ) = 0;
	virtual  TAQtStreamFormatter  &operator>>( TLength & ) = 0;
	virtual  TAQtStreamFormatter  &operator>>( TSpatialPointName & ) = 0;
	virtual  TAQtStreamFormatter  &operator>>( TSpatialPosition & ) = 0;
	virtual  TAQtStreamFormatter  &operator>>( TSpatialPoint & ) = 0;
	virtual  TAQtStreamFormatter  &operator<<( const TAngle & ) = 0;
	virtual  TAQtStreamFormatter  &operator<<( const TLength & ) = 0;
	virtual  TAQtStreamFormatter  &operator<<( const TSpatialPointName & ) = 0;
	virtual  TAQtStreamFormatter  &operator<<( const TSpatialPosition & ) = 0;
	virtual  TAQtStreamFormatter  &operator<<( const TSpatialPoint & ) = 0;
	
	virtual  void  skipCommentLines() = 0;


	// inherited member functions
    QIODevice	*device() const;
    void	setDevice( QIODevice * );
    void	unsetDevice();

    int		flags() const;
    int		flags( int f );
    int		setf( int bits );
    int		setf( int bits, int mask );
    int		unsetf( int bits );
	
    void	reset();

    void	setEncoding( QTextStream::Encoding );
    void	setCodec( QTextCodec* );


	//Input methods
    virtual  bool	atEnd();

    QString	readLine();
    QString	read();
    void	skipWhiteSpace();
	QChar   peek();
	
	virtual  TAQtStreamFormatter &operator>>( QChar & );
    virtual  TAQtStreamFormatter &operator>>( char & );
    virtual  TAQtStreamFormatter &operator>>( signed short & );
    virtual  TAQtStreamFormatter &operator>>( unsigned short & );
    virtual  TAQtStreamFormatter &operator>>( signed int & );
    virtual  TAQtStreamFormatter &operator>>( unsigned int & );
    virtual  TAQtStreamFormatter &operator>>( signed long & );
    virtual  TAQtStreamFormatter &operator>>( unsigned long & );
    virtual  TAQtStreamFormatter &operator>>( float & );
    virtual  TAQtStreamFormatter &operator>>( double & );
    virtual  TAQtStreamFormatter &operator>>( char * );
	virtual  TAQtStreamFormatter &operator>>( string );
    virtual  TAQtStreamFormatter &operator>>( QString & );
    virtual  TAQtStreamFormatter &operator>>( QCString & );
    virtual  TAQtStreamFormatter &operator>>( TSFFUNC );
    
	TAQtStreamFormatter &readRawBytes( char *, uint len );

	//Output methods
    int	  width()	const;
    int	  width( int );
    int	  fill()	const;
    int	  fill( int );
    int	  precision()	const;
    int	  precision( int );

    virtual  TAQtStreamFormatter &operator<<( char );
    virtual  TAQtStreamFormatter &operator<<( signed short );
    virtual  TAQtStreamFormatter &operator<<( unsigned short );
    virtual  TAQtStreamFormatter &operator<<( signed int );
    virtual  TAQtStreamFormatter &operator<<( unsigned int );
    virtual  TAQtStreamFormatter &operator<<( signed long );
    virtual  TAQtStreamFormatter &operator<<( unsigned long );
    virtual  TAQtStreamFormatter &operator<<( float );
    virtual  TAQtStreamFormatter &operator<<( double );
    virtual  TAQtStreamFormatter &operator<<( const char* );
	virtual  TAQtStreamFormatter &operator<<( string );
    virtual  TAQtStreamFormatter &operator<<( const QString & );
    virtual  TAQtStreamFormatter &operator<<( const QCString & );
    virtual  TAQtStreamFormatter &operator<<( void * ); 
    virtual  TAQtStreamFormatter &operator<<( QTSManip & );
    virtual  TAQtStreamFormatter &operator<<( TSFFUNC );

	virtual	 TAQtStreamFormatter& operator<<(TPointFormat& ptFormat);
	virtual	 TAQtStreamFormatter& operator<<(TObservationFormat& obsFormat);
    //TAQtStreamFormatter &operator<<( QTSFUNC );

    TAQtStreamFormatter &writeRawBytes( const char* , uint len );


protected:
	static TAngleFilter *getAngleFilter( TAngle::EUnits );
	static TLengthFilter *getLengthFilter( TLength::EUnits );
	static TSpatialPositionFilter *getPositionFilter( TSpatialPosition::ECoordinateSystem );

	// member attributes
	QTextStream  *fStream;
	TAngle::EUnits  fAngles;
	TAngleFilter  *fAngFilter;
	TLength::EUnits  fLengths;
	TLengthFilter  *fLenFilter;
	TSpatialPosition::ECoordinateSystem  fCoorSys;
	TSpatialPositionFilter  *fPosFilter;
	TSpatialPosition::ECoordToken  fCoordToken;
	TVReferenceFrame  *fRefFrame;

	TPointFormat			fPointFormat;
	TObservationFormat		fObservationFormat;

private:

	//ClassDef(TAQtStreamFormatter, 1)
};




//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////
inline TSpatialPosition::ECoordToken TAQtStreamFormatter::setCoordToken( TSpatialPosition::ECoordToken token )
{	TSpatialPosition::ECoordToken oldTok = fCoordToken; 
	fCoordToken = token; 
	return oldTok; }


inline TVReferenceFrame*  TAQtStreamFormatter::setReferenceFrame( TVReferenceFrame  *frame )
{	TVReferenceFrame *oldFrame = fRefFrame; 
	fRefFrame = frame; 
	return oldFrame; }


inline TAngle::EUnits TAQtStreamFormatter::getAngleUnits() const
{	return fAngles; }


inline TLength::EUnits TAQtStreamFormatter::getLengthUnits() const
{	return fLengths; }


inline TSpatialPosition::ECoordToken TAQtStreamFormatter::getCoordToken() const
{	return fCoordToken; }


inline TSpatialPosition::ECoordinateSystem  TAQtStreamFormatter::getCoordSys() const
{	return fCoorSys; }


inline TVReferenceFrame*  TAQtStreamFormatter::getReferenceFrame() const
{	return fRefFrame; }



inline QIODevice *TAQtStreamFormatter::device() const
{	return fStream->device(); }

inline void TAQtStreamFormatter::setDevice(QIODevice *device)
{	fStream->setDevice(device); return; }

inline void TAQtStreamFormatter::unsetDevice()
{	fStream->unsetDevice(); return; }


inline int TAQtStreamFormatter::flags() const
{	return fStream->flags(); }

inline int TAQtStreamFormatter::flags( int f )
{	return fStream->flags( f ); }

inline int TAQtStreamFormatter::setf( int bits )
{	return fStream->setf( bits ); }

inline int TAQtStreamFormatter::setf( int bits, int mask )
{	return fStream->setf( bits, mask ); }

inline int TAQtStreamFormatter::unsetf( int bits )
{	return fStream->unsetf( bits ); }


inline void TAQtStreamFormatter::reset()
{	fStream->reset(); return; }


inline void TAQtStreamFormatter::setEncoding( QTextStream::Encoding e)
{	fStream->setEncoding( e ); return; }

inline void TAQtStreamFormatter::setCodec( QTextCodec *codec )
{	fStream->setCodec( codec ); return; }

//Format related methods
inline void TAQtStreamFormatter::setPointFormat(TPointFormat ptFormat)
{ fPointFormat = ptFormat; }

inline void TAQtStreamFormatter::setObsFormat(TObservationFormat obsFormat)
{ fObservationFormat = obsFormat; }

inline const TPointFormat* TAQtStreamFormatter::getPointFormat() const
{ return &fPointFormat; }

inline const TObservationFormat* TAQtStreamFormatter::getObsFormat() const
{ return &fObservationFormat; }

//Input methods
inline bool TAQtStreamFormatter::atEnd()
{	this->skipCommentLines(); return fStream->atEnd(); }


inline QString TAQtStreamFormatter::readLine() 
{	return fStream->readLine(); }

inline QString TAQtStreamFormatter::read() 
{	return fStream->read(); }

inline void TAQtStreamFormatter::skipWhiteSpace() 
{	fStream->skipWhiteSpace(); return; }

//inline QChar TAQtStreamFormatter::peek() 
//{	return fStream->peek(); }


//Output methods
inline int TAQtStreamFormatter::width() const
{	return fStream->width(); }

inline int TAQtStreamFormatter::width( int w )
{	return fStream->width( w ); }

inline int TAQtStreamFormatter::fill() const
{	return fStream->fill(); }

inline int TAQtStreamFormatter::fill( int f )
{	return fStream->width( f ); }

inline int TAQtStreamFormatter::precision() const
{	return fStream->precision(); }

inline int TAQtStreamFormatter::precision( int p )
{	return fStream->precision( p ); }


//TAQtStreamFormatter &operator<<( TAQtStreamFormatter &tsf, TSFFUNC func )
//{	(*func)( tsf ); return tsf; }

TAQtStreamFormatter &fbin( TAQtStreamFormatter &s );	// set bin notation
TAQtStreamFormatter &foct( TAQtStreamFormatter &s );	// set oct notation
TAQtStreamFormatter &fdec( TAQtStreamFormatter &s );	// set dec notation
TAQtStreamFormatter &fhex( TAQtStreamFormatter &s );	// set hex notation
TAQtStreamFormatter &fendl( TAQtStreamFormatter &s );	// insert EOL ('\n')
TAQtStreamFormatter &fflush( TAQtStreamFormatter &s );	// flush output
TAQtStreamFormatter &fws( TAQtStreamFormatter &s );	// eat whitespace on input
TAQtStreamFormatter &freset( TAQtStreamFormatter &s );	// set default flags


#endif // !defined(SU_A_TEXT_STREAM_FORMATTER)
