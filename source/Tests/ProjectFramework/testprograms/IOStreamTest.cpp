// Test File for the IOStreams

#include <iostream.h>
//#include <iomanip.h>

#include  "QFile.h"
#include  "QString.h"
#include  "TAngle.h"
#include  "TRadiansFilter.h"
#include  "TGonsFilter.h"
#include  "TDMSFilter.h"

#include  "TLength.h"
#include  "TKilometresFilter.h"
#include  "TMetresFilter.h"
#include  "TMillimetresFilter.h"

#include  "TSpatialPointName.h"

#include  "TSpatialPosition.h"
#include  "TSpatialPositionFilter.h"
#include  "T3DCartesianFilter.h"

#include  "TSpatialPoint.h"
#include  "TVReferenceFrame.h"

#include  "TWorkingPoints.h"

#include  "TTStreamFormatter.h"
#include  "TFreeFormatTStream.h"


int main();
void testBasicFreeFormatOutput();
void testBasicFreeFormatIO();
void testBasicFreeFormatFileIO();


int main()
{
	testBasicFreeFormatOutput();

	testBasicFreeFormatIO();

	testBasicFreeFormatFileIO();
		
	return 0;
}


void testBasicFreeFormatFileIO()
{
	// 
	// Test IO of Points to a file
	// using all the features of the FreeFormat stream formatter
	//
	TWorkingPoints*  pointData = new TWorkingPoints();
	QFile qFile( "c:\\Temp\\chk158.dat" ), qFile2( "c:\\Temp\\chk158.out" );


	if ( qFile.open( IO_ReadOnly ) )
	{
		TSpatialPoint  *newPoint;
		
		TTStreamFormatter &tstream = *( new TFreeFormatTStream( new QTextStream( &qFile ) ) );

		while ( !tstream.atEnd() )
		{
			newPoint = new TSpatialPoint();
			tstream >> *newPoint;

			pointData->addPoint( newPoint );
		}

		qFile.close();
	}
	
	cout << pointData->numberOfPoints() << '\n';

	if ( qFile2.open( IO_WriteOnly ) )
	{
		TTStreamFormatter &tstream = *( new TFreeFormatTStream( new QTextStream( &qFile2 ) ) );
		
		
		TWorkingPoints::PointIterator  iterator; 
		TWorkingPoints::PointIterator  end = pointData->getPointsEndIterator(); 

		for( iterator = pointData->getPointsBeginIterator(); iterator != end; iterator++)
		{
			tstream << qSetPrecision(5);
			tstream << qSetW(76);
			tstream << *iterator << fendl;
		}
		
		// This doesn't work.
		//copy(pointData->getPointsBeginIterator(), pointData->getPointsEndIterator(), ostream_iterator<TSpatialPoint>(tstream, "\n");

		if ( (iterator = pointData->getPoint( *(new TSpatialPointName( string("chk734"), string(""), string(" ") )) )) != pointData->getPointsEndIterator() )
			tstream << *iterator;

		qFile2.close();

	}

//emma

	return;
}


void   testBasicFreeFormatIO()
{
    //
	// Test IO of Angles, Lengths, and Points
	// using all the features of the FreeFormat stream formatter
	//

	//Test Angle and Length filters
	QString text1;
	TAngle myAng1, myAng2, myAng3;
	TLength myLen1, myLen2, myLen3;
	TVReferenceFrame*  myRefFrame = new TGeodeticRefFrame();
	TSpatialPosition myPosition1( *myRefFrame );
	TSpatialPosition* myPosition2 = new TSpatialPosition( *myRefFrame );
	TSpatialPointName myName2;
	TSpatialPoint  myPoint1;

	//FILE	*myFile;
	QFile qFile( "c:\\Temp\\myout.txt" ), qFile2( "c:\\Temp\\myout2.txt" );


	if ( qFile.open( IO_ReadOnly ) )
	{
		TTStreamFormatter &tstream = *( new TFreeFormatTStream( new QTextStream( &qFile ) ) );

		//Test Angle and Length filters

		tstream >> text1;
		//cout << text1.ascii() << endl;
		
		// test angle input
		tstream >> myAng1;
		//cout << myAng.getRadiansValue();

		tstream.setAngleUnits(TAngle::kRadians);
		tstream >> myAng2;
		//cout << myAng.getGonsValue() << endl;

		tstream.setAngleUnits(TAngle::kDMS);
		tstream >> myAng3;
		//cout << myAng.getDegreesValue() << myAng.getMinutesValue() << myAng.getSecondsValue() << endl;

		//test length input
		tstream >> myLen1;
		//cout << myLen << endl;

		tstream.setLengthUnits(TLength::kMillimetres);
		tstream >> myLen2;
		//cout << myLen << endl;

		tstream.setLengthUnits(TLength::kKilometres);
		tstream >> myLen3;
		//cout << myLen << endl;

		// test position input
		tstream.setLengthUnits(TLength::kMetres);
		tstream >> myPosition1;
		//cout << myPosition.getXCoord() << myPosition.getYCoord() << myPosition.getZCoord() << endl;
		
		//tstream >> myName2;
		//tstream >> *myPosition2;
		tstream >> myPoint1;

		qFile.close();
	}

	if ( qFile2.open( IO_WriteOnly ) )
	{
		
		TTStreamFormatter &tstream = *( new TFreeFormatTStream( new QTextStream( &qFile2 ) ) );

		tstream << text1;
		tstream << fendl;

		// test angle output
		tstream << setw(10);
		tstream << myAng1 << fendl;

		tstream.setAngleUnits(TAngle::kRadians);
		tstream << myAng2 << fendl;

		tstream.setAngleUnits(TAngle::kDMS);
		tstream << myAng3 << fendl;

		tstream << fendl;

		// test length output
		tstream << myLen1 << fendl;

		tstream.setLengthUnits(TLength::kMillimetres);
		tstream << myLen2 << fendl;

		tstream.setLengthUnits(TLength::kKilometres);
		tstream << myLen3 << fendl;

		// test position output
		tstream.setLengthUnits(TLength::kMetres);
		tstream << myPosition1 << fendl;

		//tstream << myName2;
		//tstream << myPosition2  << fendl;
		//myPoint1.setPtName( myName2 );
		//myPoint1.setPosition( myPosition2 );
		tstream << qSetPrecision(4);
		tstream << qSetW(50);
		tstream << myPoint1 << fendl;
	/*
		fclose(myFile);
	}*/
		
		qFile2.close();

	}


	return;
}



void  testBasicFreeFormatOutput()
{
    //
	// Test output of Angles, Lengths, and Points
	// using all the features of the FreeFormat stream formatter
	//

	//FILE	*myFile;
	QFile qFile( "c:\\Temp\\myout.txt" );


	if ( qFile.open( IO_WriteOnly ) )
	{
		
		TTStreamFormatter &tstream = *( new TFreeFormatTStream( new QTextStream( &qFile ) ) );


	/*if ( myFile = fopen(( "c:\\Temp\\myout.txt" ), "w") )
	{
		QTextStream tstream( myFile, IO_WriteOnly );
	*/
				
		//Test Angle and Length filters
		TAngle myAng(.785);
		TLength myLen(10.5789478);

		tstream << "hello";
		tstream << fendl;

		// test angle output
		tstream << setw(10);
		tstream << myAng << fendl;

		tstream.setAngleUnits(TAngle::kRadians);
		tstream << myAng << fendl;

		tstream.setAngleUnits(TAngle::kDMS);
		tstream << myAng << fendl;

		tstream << fendl;

		// test length output
		tstream << myLen << fendl;

		tstream.setLengthUnits(TLength::kMillimetres);
		tstream << myLen << fendl;

		tstream.setLengthUnits(TLength::kKilometres);
		tstream << myLen << fendl;

		// test position output
		TSpatialPosition* myPosition;
		myPosition = new TSpatialPosition();
		myPosition->setXCoord(myLen);
		myLen.setMetresValue(30.1234);
		myPosition->setYCoord(myLen);
		myLen.setMetresValue(50.0);
		myPosition->setZCoord(myLen);
		tstream.setLengthUnits(TLength::kMetres);
		tstream << *myPosition << fendl;

		TSpatialPointName myName("Point", 'E', "1");

		TSpatialPoint myPoint( myName, myPosition );

		tstream << myPoint << fendl;

	/*
		fclose(myFile);
	}*/
		
		qFile.close();

	}


	return;
}
