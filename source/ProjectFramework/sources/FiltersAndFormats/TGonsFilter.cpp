// TGonsFilter.cpp
//
// Concrete Class of the TAngleFilter PABC.
// Handles the IO of an TAngle object angles in a text stream with 
// gons units. 
// 
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TTStreamFormatter object. 
//
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// Other forward declarations
#include "TAngle.h"
#include "TObservationFormat.h"
#include "TPointFormat.h"
#include "TGonsFilter.h"
//////////////////////////////////////////////////////////////////////


//ClassImp(TGonsFilter)



//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
TGonsFilter *TGonsFilter::fFilter = 0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TGonsFilter::TGonsFilter()
{}

TGonsFilter::~TGonsFilter()
{}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TGonsFilter *TGonsFilter::instance()
{
	if( fFilter == nullptr )
	{
		fFilter = new TGonsFilter;
	}

	return fFilter;
}


void	TGonsFilter::input(TAStreamFormatter& iStream, TAngle& angle)const
{	// function to get a gons angle from a QTextStream object
	// and set the value in a TAngle object
	TReal	gons;

	iStream.skipWhiteSpace();
	if(iStream.peek()=='\n')
	{//check if there's coordinate to read
		angle.setGonsValue(NO_VALf);
		iStream.setError("No angle value to read");
	}

	else
	{
		iStream >> gons;
		if(!(iStream.fail()))
			angle.setGonsValue(gons);
		else
		{
			angle.setGonsValue(NO_VALf);
			//make iStream's flags to "goodbit"
			iStream.clear();
			//read the wrong gons value
			while(iStream.peek()!=' ' && iStream.peek()!='\n')
			{
				iStream.readChar();
			}
			iStream.setError("Invalid angle value");
		}
	}

	
	
	return;
}

/////////////////////////////////////////////////////////
// outputs an angle formatted in Gons units to the stream
/////////////////////////////////////////////////////////
void	TGonsFilter::output(TAStreamFormatter& oStream,const TAngle& angle)const
{	// function to put a gons angle to a QTextStream object.
	// Gets the value from a TAngle object

	oStream.setf(std::ios::fixed, std::ios::floatfield);
	oStream.width(oStream.getWidthFormat());
	oStream.precision(oStream.getPrecisionFormat());

	// provisoire
	TAngle a(angle);
	if (a.getRadiansValue()<LITERAL(0.0))
      a += (2.0*TAngle::pi());
	
   oStream << a.getGonsValue();
	
	return;
}




//////////////////////////////////////////////////////////////////////
// End 
//////////////////////////////////////////////////////////////////////

