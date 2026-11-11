// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <TOptionsCheck.h>
#include <PlainTransform.h>
#include <TPlainDataParameters.h>
#include <TDataParameters.h>
#include <TSpatialPosition.h>

#include <SpatialObjFns.h>

#include <TRefFrameInfo.h>
#include <TRefSystemFactory.h>

#include <tut/tut.hpp>
#include <tut/tut_macros.hpp>
#include <stdexcept>

#include "../../SpatialObjects/UnitTests/GeoidTestGrid.h"

#include <string>
#include <map>

#include <sstream>
#include <fstream>
#include <iostream>


namespace tut
{
    struct test_CSGeoDLLMultipleTransformations{};
    typedef test_group<test_CSGeoDLLMultipleTransformations> factory;
    typedef factory::object object;

    TPlainDataParameters inputParams;
	TPlainDataParameters outputParams;
	std::stringstream log;
	std::istringstream iss;
	std::string line;
	}


namespace tut
{
    tut::factory tf("Test of csgeoDLL");
}

namespace tut
{
    /*! Testing valid options */
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Transformation between CCS and other coordinate systems: forward and reverse");

        //transformation between CCS and other coordinate systems
        //CCS-->other coordinate system
        //other coordinate system-->CCS

        inputParams.fRefFrame = TRefSystemFactory::kCCS;
        inputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
        inputParams.fAngUnits = TAngle::kGons;
       		
        const double x_th = -884.485040000;
		const double y_th = 2643.742930000;
		const double z_th = 2402.509740000;

        for(TRefFrameInfo::RefFrameSet::const_iterator it = TRefFrameInfo::getRefFrameSet().begin(); 
            it!=TRefFrameInfo::getRefFrameSet().end(); ++it)
        {
			double x = x_th;
			double y = y_th;
			double z = z_th;

			if (*it != TRefSystemFactory::ERefFrame::kCGRF_new)
			// We skip kCGRF_new (not yet implemented)
			{
				std::ostringstream info;
				info << "[CCS->" << TRefFrameInfo::getName(*it) << "->CCS]: ";
				std::cout << "\n Transforming " << info.str() << std::endl;
   
				outputParams.fRefFrame = (*it); 
				outputParams.fCoordSys = TRefFrameInfo::getDefaultCoordSys((*it));
				outputParams.fAngUnits = TAngle::kGons;

				if(TRefFrameInfo::isLocalRefFrame(*it) || TRefFrameInfo::isLocalRFWithMatrix(*it))
				    continue;

				// Special settings for terrestrial reference frame
				if (outputParams.fRefFrame == TRefSystemFactory::ERefFrame::kITRFin)
				{
					outputParams.fEpoch = 2020;
					outputParams.fSolution = "ITRF 2014";
					const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
					ensure_equals(info.str() + "Step 1 result code", result_step1, 18);
					const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
					ensure_equals(info.str() + "Step 2 result code", result_step2, 0);
				}
				else if (outputParams.fRefFrame == TRefSystemFactory::ERefFrame::kITRFout)
				{
					outputParams.fEpoch = 2020;
					outputParams.fSolution = "ITRF 2014";
					const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
					ensure_equals(info.str() + "Step 1 result code", result_step1, 0);
					const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
					ensure_equals(info.str() + "Step 2 result code", result_step2, 17);
				}
				else if (outputParams.fRefFrame == TRefSystemFactory::ERefFrame::kETRFin)
				{
					outputParams.fEpoch = 2020;
					outputParams.fSolution = "ETRF 2014";
					const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
					ensure_equals(info.str() + "Step 1 result code", result_step1, 18);
					const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
					ensure_equals(info.str() + "Step 2 result code", result_step2, 0);
				}
				else if (outputParams.fRefFrame == TRefSystemFactory::ERefFrame::kETRFout)
				{
					outputParams.fEpoch = 2020;
					outputParams.fSolution = "ETRF 2014";
					const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
					ensure_equals(info.str() + "Step 1 result code", result_step1, 0);
					const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
					ensure_equals(info.str() + "Step 2 result code", result_step2, 17);
				}
				else if ((outputParams.fRefFrame >= 109 && outputParams.fRefFrame <= 115) ||  //Swiss system and Mercator projection
					(outputParams.fRefFrame >= 205 && outputParams.fRefFrame <= 210))    //French system
					//We are not looking for accuracy better than 0.1 mm for global transformations
				{
					const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
					ensure_equals(info.str() + "Step 1 result code", result_step1, 0);
					const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
					ensure_equals(info.str() + "Step 2 result code", result_step2, 0);

					ensure_distance(info.str() + "X", x, x_th, 0.0001);
					ensure_distance(info.str() + "Y", y, y_th, 0.0001);
					ensure_distance(info.str() + "Z", z, z_th, 0.0001);
				}
				else
				{
					const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
					ensure_equals(info.str() + "Step 1 result code", result_step1, 0);
					const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
					ensure_equals(info.str() + "Step 2 result code", result_step2, 0);

					ensure_distance(info.str() + "X", x, x_th, 0.000001);
					ensure_distance(info.str() + "Y", y, y_th, 0.000001);
					ensure_distance(info.str() + "Z", z, z_th, 0.000001);
				}
			}               
        }   
    }

	/*! Testing valid options for ITRF */
	template<>
	template<>
	void object::test<2>()
	{
		set_test_name("Transformation between CCS and ITRF 2014: forward and reverse");

		// transformation between CCS and ITRF
		// CCS-->ITRF
		// ITRF-->CCS

		inputParams.fRefFrame = TRefSystemFactory::kCCS;
		inputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		inputParams.fAngUnits = TAngle::kGons;

		double x = -884.485040000;
		double y = 2643.742930000;
		double z = 2402.509740000;

		std::ostringstream info;
		info << "[CCS->ITRF 2014 at 2020.0->CCS]: ";
		std::cout << "\n Transforming " << info.str() << std::endl;

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kITRFout;
		outputParams.fCoordSys = TRefFrameInfo::getDefaultCoordSys(14);
		outputParams.fAngUnits = TAngle::kGons;
		outputParams.fEpoch = 2020;
		outputParams.fSolution = "ITRF 2014";
		const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
		ensure_equals(info.str() + "Step 1 result code", result_step1, 0);

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kITRFin;
		const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
		ensure_equals(info.str() + "Step 2 result code", result_step2, 0);

		ensure_distance(info.str() + "X", x, -884.485040000, 0.000001);
		ensure_distance(info.str() + "Y", y, 2643.742930000, 0.000001);
		ensure_distance(info.str() + "Z", z, 2402.509740000, 0.000001);
	}

	/*! Testing valid options for ETRF */
	template<>
	template<>
	void object::test<3>()
	{
		set_test_name("Transformation between CCS and ETRF 2014: forward and reverse");

		// transformation between CCS and ETRF
		// CCS-->ETRF
		// ETRF-->CCS

		inputParams.fRefFrame = TRefSystemFactory::kCCS;
		inputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		inputParams.fAngUnits = TAngle::kGons;

		double x = -884.485040000;
		double y = 2643.742930000;
		double z = 2402.509740000;

		std::ostringstream info;
		info << "[CCS-> ETRF 2014 at 2020.0 ->CCS]: ";
		std::cout << "\n Transforming " << info.str() << std::endl;

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kETRFout;
		outputParams.fCoordSys = TRefFrameInfo::getDefaultCoordSys(15);
		outputParams.fAngUnits = TAngle::kGons;
		outputParams.fEpoch = 2020;
		outputParams.fSolution = "ETRF 2014";
		const int result_step1 = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
		ensure_equals(info.str() + "Step 1 result code", result_step1, 0);

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kETRFin;
		const int result_step2 = transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL);
		ensure_equals(info.str() + "Step 2 result code", result_step2, 0);

		ensure_distance(info.str() + "X", x, -884.485040000, 0.000001);
		ensure_distance(info.str() + "Y", y, 2643.742930000, 0.000001);
		ensure_distance(info.str() + "Z", z, 2402.509740000, 0.000001);
	}

	template<>
    template<>
    void object::test<4>()
    {
		/*
		* DLL test using data file from Youri Robert
		* transformation between:
		* XYHg85 -> Ch1903plus
		*/

		// transformation parameters
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCernXYHg85; 
		inputParams.fCoordSys = TCoordSysFactory::k2DPlusH; 
		inputParams.fAngUnits = TAngle::kGons;

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCH1903plus; 
		outputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		outputParams.fAngUnits = TAngle::kGons; 

		// reading from a file transforming and writing to a file
		const std::string & path = ".\\test_files\\XYHg85.txt ";
		std::ofstream outFile("CH1903plusnew.txt");
		outFile << std::setprecision(13);

		std::ifstream indata;
		indata.open(path.c_str());
		log << "Could not open the test file: " << path;

		while(std::getline(indata, line)) {
			std::string pointName;
			double xCoord, yCoord, zCoord;

			iss.str(line);
			iss.clear();
			iss >> pointName >> xCoord >> yCoord >> zCoord;
			if(iss.fail()) continue;

			double x = xCoord;
			double y = yCoord;
			double z = zCoord;

			int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);

			if (outFile.is_open () && result == EStatusCode::kOk)
			{
				outFile<<pointName<<  "\t" << x << "\t" << y << "\t" << z <<std::endl;
			}
		}
		outFile.close();
    }

	template<>
    template<>
    void object::test<5>()
    {
		/*
		* DLL test using data file from Youri Robert
		* transformation between:
		* XYHg85 -> ITRF97
		*/

		//transformation parameters
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCernXYHg85; 
		inputParams.fCoordSys = TCoordSysFactory::k2DPlusH; 
        inputParams.fAngUnits = TAngle::kGons; 

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kITRF97;       
		outputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		outputParams.fAngUnits = TAngle::kGons;

		//reading from a file transforming and writing to a file
		const std::string & path = ".\\test_files\\XYHg85.txt";
		std::ofstream outFile("ITRF97new.txt");
		outFile << std::setprecision(13);

		std::ifstream indata; 
		indata.open(path.c_str());
		log << "Could not open the test file: " << path;

		while(std::getline(indata, line)) {
			std::string pointName;
			double xCoord, yCoord, zCoord;

			iss.str(line);
			iss.clear();
			iss >> pointName >> xCoord >> yCoord >> zCoord;
			if(iss.fail()) continue;

			double x = xCoord;
			double y = yCoord;
			double z = zCoord;

			int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);

			if (outFile.is_open ()&& result == EStatusCode::kOk)
			{
				outFile<<pointName<<  "\t" << x << "\t" << y << "\t" << z <<std::endl;
			}
		}
		outFile.close();

    }

#ifdef USE_SWISSTOPO
	template<>
    template<>
    void object::test<6>()
    {
		/*
		* DLL test using data file from Youri Robert
		* transformation between:
		* XYHg85 -> LV95
		*/

		//transformation parameters
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCernXYHg85;
		inputParams.fCoordSys = TCoordSysFactory::k2DPlusH;
        inputParams.fAngUnits = TAngle::kGons;

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kSwissLV95_eh;      
		outputParams.fCoordSys = TCoordSysFactory::k2DPlusH; 
		outputParams.fAngUnits = TAngle::kGons;

		//reading from a file transforming and writing to a file
		const std::string & path = ".\\test_files\\XYHg85.txt";
		std::ofstream outFile("LV95new.txt");
		outFile << std::setprecision(13);

		std::ifstream indata; 
		indata.open(path.c_str());
		log << "Could not open the test file: " << path;

		while(std::getline(indata, line)) {
			std::string pointName;
			double xCoord, yCoord, zCoord;

			iss.str(line);
			iss.clear();
			iss >> pointName >> xCoord >> yCoord >> zCoord;
			if(iss.fail()) continue;

			double x = xCoord;
			double y = yCoord;
			double z = zCoord;

			int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);

			if (outFile.is_open() && result == EStatusCode::kOk)
			{
				outFile<<pointName<<  "\t" << x << "\t" << y << "\t" << z <<std::endl;
			}
		}
		outFile.close();

    }

	//Test of the new format of input file for swiss LV95 
	template<>
    template<>
    void object::test<7>()
    {
		/*
		* DLL test using data file from Youri Robert
		* transformation between:
		* LV95 -> XYHg85
		*/

		//transformation parameters
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kSwissLV95_eh; 
		inputParams.fCoordSys = TCoordSysFactory::k2DPlusH; 
        inputParams.fAngUnits = TAngle::kGons; 

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCernXYHg85;      
		outputParams.fCoordSys = TCoordSysFactory::k2DPlusH; 
		outputParams.fAngUnits = TAngle::kGons; 

		//reading from a file transforming and writing to a file
		const std::string & path = ".\\test_files\\LV95new.txt ";
		std::ofstream outFile("XYHg85new.txt");
		outFile << std::setprecision(13);

		std::ifstream indata; 
		indata.open(path.c_str());
		log << "Could not open the test file: " << path;

		while(std::getline(indata, line)) {
			std::string pointName;
			double xCoord, yCoord, zCoord;

			iss.str(line);
			iss.clear();
			iss >> pointName >> xCoord >> yCoord >> zCoord;
			if(iss.fail()) continue;

			double x = xCoord;
			double y = yCoord;
			double z = zCoord;

			int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);


			if (outFile.is_open() && result == EStatusCode::kOk)
			{
				outFile<<pointName<<  "\t" << x << "\t" << y << "\t" << z <<std::endl;
			}
		}
		outFile.close();

    }
#endif

	/*! Testing valid options for ETRF */
	template<>
	template<>
	void object::test<8>()
	{
		set_test_name("Transformation between CCS and CHTRF95 with heights above a custom geoid");

		const std::string grid = geoidtestgrid::createGrid("surveylib_test_geoid_A_v1.tif");

		inputParams.fRefFrame = TRefSystemFactory::kCCS;
		inputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		inputParams.fAngUnits = TAngle::kGons;
		inputParams.fGeoidPath = "";

		const double x_th = -884.485040000;
		const double y_th = 2643.742930000;
		const double z_th = 2402.509740000;

		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCHTRF95;
		outputParams.fCoordSys = TCoordSysFactory::kGeodetic;
		outputParams.fAngUnits = TAngle::kDeciDegs;

		// Reference: ellipsoidal height
		double xh = x_th, yh = y_th, zh = z_th;
		outputParams.fGeoidPath = "";
		ensure_equals("Ellipsoidal result code", transformPoint(&xh, &yh, &zh, &inputParams, NULL, &outputParams, NULL), 0);

		// Height above the custom geoid
		double x = x_th, y = y_th, z = z_th;
		outputParams.fGeoidPath = grid.c_str();
		ensure_equals("Step 1 result code", transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL), 0);

		ensure_distance("Longitude unchanged", x, xh, 1e-10);
		ensure_distance("Latitude unchanged", y, yh, 1e-10);
		// the geoid is defined in ETRF93: tolerance covers the (sub-millimetric) CHTRF95 / ETRF93 difference
		ensure_distance("H = h - N", z, zh - geoidtestgrid::expectedN(x, y), 1e-3);

		// Back to CCS
		ensure_equals("Step 2 result code", transformPoint(&x, &y, &z, &outputParams, NULL, &inputParams, NULL), 0);
		ensure_distance("X", x, x_th, 0.000001);
		ensure_distance("Y", y, y_th, 0.000001);
		ensure_distance("Z", z, z_th, 0.000001);

		outputParams.fGeoidPath = "";
	}

	/*! Testing invalid geoid options */
	template<>
	template<>
	void object::test<9>()
	{
		set_test_name("Invalid custom geoid options");

		const std::string grid = geoidtestgrid::createGrid("surveylib_test_geoid_A_v1.tif");

		inputParams.fRefFrame = TRefSystemFactory::kCCS;
		inputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		inputParams.fAngUnits = TAngle::kGons;
		inputParams.fGeoidPath = "";

		double x = -884.485040000, y = 2643.742930000, z = 2402.509740000;

		// 3D cartesian coordinates have no height
		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCHTRF95;
		outputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
		outputParams.fAngUnits = TAngle::kGons;
		outputParams.fGeoidPath = grid.c_str();
		ensure_equals("3D cartesian", transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL), static_cast<int>(kInvalidOutputGeoid));

		// Frame already using a vertical datum
		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kLambert93_ign69;
		outputParams.fCoordSys = TCoordSysFactory::k2DPlusH;
		ensure_equals("vertical datum", transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL), static_cast<int>(kInvalidOutputGeoid));

		// Missing file
		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kCHTRF95;
		outputParams.fCoordSys = TCoordSysFactory::kGeodetic;
		outputParams.fGeoidPath = "this/file/does/not/exist.tif";
		ensure_equals("missing file", transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL), static_cast<int>(kInvalidOutputGeoid));

		// Geoid on a CCS input
		inputParams.fGeoidPath = grid.c_str();
		outputParams.fGeoidPath = "";
		ensure_equals("geoid on CCS", transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL), static_cast<int>(kInvalidInputGeoid));

		inputParams.fGeoidPath = "";
		outputParams.fGeoidPath = "";
	}
	}
