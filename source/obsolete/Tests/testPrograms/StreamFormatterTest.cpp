// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

///////////////////////////////////////////////////////////////
//test
//10/2002
///////////////////////////////////////////////////////////////

//#include <iostream>
//#include <string>
//using namespace std;

#include "TAStreamFormatter.h"
#include "TSeparatedFormatTStream.h"
#include "TLGCFileReader.h"
#include "TLGCDataSet.h"
#include "TLGCProject.h"
#include "TLGCApplication.h"
//#include "TLSCalcDataSet.h"
#include "TGeodeticRefFrame.h"


void main()
{
	
//////////////////////////////////////////////////////////////
//Read a input LGCFilevv with the load function of TLGCProject
//////////////////////////////////////////////////////////////

	const char * LGCFile;
	LGCFile = "C:\\temp\\lgcInputTest.inp";

	// settings for Data parameters
	TDataParameters dp;
	dp.setRefFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	dp.setCoordSys(TCoordSysFactory::k3DCartesian);
	dp.setAngUnits(TAngle::kRadians);
	dp.setLenUnits(TLength::kMetres);
	dp.setAnglePrecision(6);
	dp.setLengthPrecision(5);
	dp.setCoordPrecision(TPointFormat::kMmTenth);

	// settings for file parameters
	TFileParameters fp;
	fp.setFileName(LGCFile);


	// creating an (empty) application and a project
	TLGCApplication application;
	TLGCProject project(&application);

	// use of load function
	project.load(fp, dp);


	

	PointIterator i, j;

	i=project.getDataSet()->getWorkingPoints()->getPointsBeginIterator();
	j=project.getDataSet()->getWorkingPoints()->getPointsEndIterator();

	while(i!=j)
	{
		TSpatialStatus::ESpatialStatus status = i->getPosition().getObjectStatus();
		string name=i->getPtName();
		real X =i->getPosition().getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue();
		real Y =i->getPosition().getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue();
		real Z =i->getPosition().getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue();
		real dist=i->getDist();
		int id=i->getId();
		string com=i->getComment();
		string head=i->getHeaderComment();
		string eol = i->getEOLComment();
		cout.precision(10);
		cout<<status<<endl;
		cout<<name<<", "<<X<<", "<<Y<<", "<<Z<<endl;
		cout<<"dist: "<<dist<<", id: "<<id<<", com: "<<com<<endl;
		cout<<"head: "<<head<<endl;
		cout<<"eol: "<<eol<<endl<<endl;
		i++;
	}

	/*
	const char* fileToWrite;
	const TLSCalcDataSet* lscDS = new TLSCalcDataSet(lgcDS);
	fileToWrite= "C:\\workspace\\LGC\\essaiecriture.lgc";
	TLGCFileWriter w (lgcDS, lscDS, fileToWrite);
	*/


	return;
}
