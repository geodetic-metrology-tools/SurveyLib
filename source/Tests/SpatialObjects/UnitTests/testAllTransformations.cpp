// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>

#include <fstream>

#include <map>
#include <string>

#include "testdata.h"

namespace tut
{
    struct test_AllTransformations{};
    typedef test_group<test_AllTransformations> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test of all transformations");
}

typedef std::map<std::string, TSpatialPosition> TPointsMap;
//TPointsMap readPoints(const std::string & path, TRefSystemFactory::ERefFrame frame)
TPointsMap readPoints(const TrafoTestPoints::TTestPoints& refpt, TRefSystemFactory::ERefFrame frame)
{
	std::stringstream log;
	TPointsMap result;
	
	for (const auto& line : refpt) {
		std::stringstream indata(line);
		std::string pointName;
		double xCoord, yCoord, zCoord;
		indata >> pointName >> xCoord >> yCoord >> zCoord;
		TSpatialPosition position(
			TRefFrameInfo::getReferenceFrame(frame),
			xCoord, yCoord, zCoord,
			TRefFrameInfo::getDefaultCoordSys(frame));
			
		result.insert(std::pair<std::string, TSpatialPosition>(pointName, position));
	}

	return result;
}

void comparePointsXYH(const TPointsMap & actual, const TPointsMap & expected, const std::string & comment)
{
	std::stringstream log;
	for (TPointsMap::const_iterator iter = actual.begin(); iter != actual.end(); ++iter)
	{
		TPointsMap::const_iterator validationPoint = expected.find(iter->first);
		if(validationPoint != expected.end())
		{
			log.clear();
			log << comment << " Point:" << iter->first;
			TReal actualX = iter->second.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
			TReal actualY = iter->second.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
			TReal expectedX = validationPoint->second.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
			TReal expectedY = validationPoint->second.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
			tut::ensure_equals(log.str(), actualX, expectedX, static_cast<TReal>(0.001));
			tut::ensure_equals(log.str(), actualY, expectedY, static_cast<TReal>(0.001));
		}
		else
		{
			log.clear();
			log << comment << " Missing point in validation data:" << iter->first;
			tut::ensure(log.str(),false);
		}
	}
}

namespace tut
{
	template<>
	template<>
	void object::test<1>()
	{
		set_test_name("Test of LV95 [CCS->LV95]");
#ifndef _WIN32
        skip();
#else
		/*
		*
		*Read original data in CCS coordinate system
		*
		*/

		TRefSystemFactory::ERefFrame frame = TRefSystemFactory::kCCS;
		TPointsMap beforeTransformation = readPoints(TrafoTestPoints::LHC_CHpts, frame);

		/*
		*
		*Transform coordinates to Swiss LV95
		*
		*/
		std::map<std::string, TSpatialPosition> afterTransformation95;
		for (std::map<std::string, TSpatialPosition>::iterator iter = beforeTransformation.begin(); iter != beforeTransformation.end(); iter++)
		{
			bool result = iter->second.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh)); 
			ensure("Transformation should return true", result);
			afterTransformation95.insert(std::pair<std::string, TSpatialPosition>(iter->first, iter->second));
		}

		/*
		*
		*Read the file with coordinates transformed with CSGEO in LV95 and compare with current transformation
		*
		*/

		TrafoTestPoints::TTestPoints& refpt = TrafoTestPoints::_swisstopo_transformation_LV95;
		for (auto& line : refpt) {
			std::stringstream indataLV95(line);
			std::string pointName;
			double xCoordLV95, yCoordLV95;
			indataLV95 >> pointName >> xCoordLV95 >> yCoordLV95;
			if(indataLV95.fail()) continue;

			std::map<std::string, TSpatialPosition>::const_iterator it = afterTransformation95.find(pointName);
			if(it != afterTransformation95.end())
			{
				ensure_equals("Swiss LV95 X", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(xCoordLV95), static_cast<TReal>(0.001));
				ensure_equals("Swiss LV95 Y", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(yCoordLV95), static_cast<TReal>(0.001));
			}
			else
			{
				ensure("Missing point",false);
			}
		}
#endif
	}

	template<>
	template<>
	void object::test<2>()
	{
		set_test_name("Test of LV95 [LV95 ->CCS]");
#ifndef _WIN32
        skip();
#else
		/*
		*
		*Read original data in LV95 coordinate system
		*
		*/

		TRefSystemFactory::ERefFrame frame = TRefSystemFactory::kSwissLV95_eh;
		TPointsMap beforeTransformation = readPoints(TrafoTestPoints::_swisstopo_transformation_LV95, frame);


		/*
		*
		*Transform coordinates to CCS
		*
		*/
		std::map<std::string, TSpatialPosition> afterTransformationCCS;
		for (std::map<std::string, TSpatialPosition>::iterator iter = beforeTransformation.begin(); iter != beforeTransformation.end(); iter++)
		{
			bool result = iter->second.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS)); 
			ensure("Transformation should return true", result);
			afterTransformationCCS.insert(std::pair<std::string, TSpatialPosition>(iter->first, iter->second));
		}

		/*
		*
		*Read the file with coordinates in CCS
		*and compare with transformation from CSGEO
		*
		*/

		TrafoTestPoints::TTestPoints& refpt = TrafoTestPoints::LHC_CHpts;
		for (auto& line : refpt) {
			std::stringstream indataCCS(line);
			std::string pointName;
			double xCoordCCS, yCoordCCS;
			indataCCS >> pointName >> xCoordCCS >> yCoordCCS;
			if(indataCCS.fail()) continue;

			std::map<std::string, TSpatialPosition>::const_iterator it = afterTransformationCCS.find(pointName);
			if(it != afterTransformationCCS.end())
			{
				ensure_equals("CCS X", it->second.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(xCoordCCS), static_cast<TReal>(0.001));
				ensure_equals("CCS Y", it->second.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(yCoordCCS), static_cast<TReal>(0.001));
			}
			else
			{
				ensure("Missing point",false);
			}
		}
#endif
	}

	template<>
	template<>
	void object::test<3>()
	{
		set_test_name("Test of LV03 [CCS->LV03; LV03 ->CCS]");
#ifndef _WIN32
        skip();
#else
		// TODO fix LV03 transormation
		tut::skip("Fix LV03 transormation: it currently dosn't work because the call to the reframe library is not correctly done.");

		/*
		*
		*Read original data in CCS coordinate system
		*
		*/

		TRefSystemFactory::ERefFrame frame = TRefSystemFactory::kCCS;
		TPointsMap beforeTransformation = readPoints(TrafoTestPoints::LHC_CHpts, frame);

		/*
		*
		*Transform coordinates to Swiss LV03
		*
		*/
		std::map<std::string, TSpatialPosition> afterTransformation03;
		for (std::map<std::string, TSpatialPosition>::iterator iter = beforeTransformation.begin(); iter != beforeTransformation.end(); iter++)
		{
			bool result = iter->second.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_eh)); 
			ensure("Transformation should return true", result);
			afterTransformation03.insert(std::pair<std::string, TSpatialPosition>(iter->first, iter->second));
		}

		/*
		*
		*Read the file with coordinates in LV03 transformed on Swisstopo web site
		*and compare with transformation from CSGEO
		*
		*/

		TrafoTestPoints::TTestPoints& refpt = TrafoTestPoints::_swisstopo_transformation_LV03;
		for (auto& line : refpt) {
			std::stringstream indataLV03(line);
			std::string pointName;
			double xCoordLV03, yCoordLV03;
			indataLV03 >> pointName >> xCoordLV03 >> yCoordLV03;
			std::map<std::string, TSpatialPosition>::const_iterator it = afterTransformation03.find(pointName);
			if(it != afterTransformation03.end())
			{
				ensure_equals("Swiss LV03 X", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(xCoordLV03), static_cast<TReal>(0.001));
				ensure_equals("Swiss LV03 Y", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(yCoordLV03), static_cast<TReal>(0.001));
			}
			else
			{
				ensure("Missing point",false);
			}
		}
#endif
	}
	template<>
	template<>
	void object::test<4>()
	{
		set_test_name("Test of LV95 [CCS->LV95; LV95 ->CCS]");
	}


	template<>
	template<>
	void object::test<5>()
	{
		set_test_name("Test of RGF93CC46 [CCS->RGF93CC46; RGF93CC46 ->CCS]");

		/*
		*
		*Read from a file original data in CCS coordinate system
		*
		*/

		TRefSystemFactory::ERefFrame frame = TRefSystemFactory::kCCS;
		TPointsMap beforeTransformation = readPoints(TrafoTestPoints::LHC_CHpts, frame);

		/*
		*
		*Transform coordinates to RGF93CC46
		*
		*/
		std::map<std::string, TSpatialPosition> afterTransformationRGF93CC46;
		for (std::map<std::string, TSpatialPosition>::iterator iter = beforeTransformation.begin(); iter != beforeTransformation.end(); iter++)
		{
			bool result = iter->second.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_eh)); 
			ensure("Transformation should return true", result);
			afterTransformationRGF93CC46.insert(std::pair<std::string, TSpatialPosition>(iter->first, iter->second));
		}

		/*
		*
		*Read the file with coordinates in RGF93CC46 transformed by Circe software from
		*oficial France web site
		*and compare with transformation from CSGEO
		*
		*/
		
		const TrafoTestPoints::TTestPoints& refpt = TrafoTestPoints::_circe_CC46_transformation;
		for (const auto& line : refpt) {
			std::stringstream indataRGF93CC46(line);
			std::string pointName;

			double xCoordRGF93CC46, yCoordRGF93CC46;
			indataRGF93CC46 >> pointName >> xCoordRGF93CC46 >> yCoordRGF93CC46;
			if(indataRGF93CC46.fail()) continue;

			std::map<std::string, TSpatialPosition>::const_iterator it = afterTransformationRGF93CC46.find(pointName);
			if(it != afterTransformationRGF93CC46.end())
			{
				ensure_equals("RGF93CC46 X", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(xCoordRGF93CC46), static_cast<TReal>(0.001));
				ensure_equals("RGF93CC46 Y", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(yCoordRGF93CC46), static_cast<TReal>(0.001));
			}
			else
			{
				ensure("Missing point",false);
			}
		}
	}




	template<>
	template<>
	void object::test<7>()
	{
		set_test_name("Test of Lambert93 [CCS->Lambert93; Lambert93 ->CCS]");

		/*
		*
		*Read from a file original data in CCS coordinate system
		*
		*/

		TRefSystemFactory::ERefFrame frame = TRefSystemFactory::kCCS;
		TPointsMap beforeTransformation = readPoints(TrafoTestPoints::LHC_CHpts, frame);

		/*
		*
		*Transform coordinates to French Lambert93
		*
		*/
		std::map<std::string, TSpatialPosition> afterTransformationLambert93;
		for (std::map<std::string, TSpatialPosition>::iterator iter = beforeTransformation.begin(); iter != beforeTransformation.end(); iter++)
		{
			bool result = iter->second.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_eh)); 
			ensure("Transformation should return true", result);
			afterTransformationLambert93.insert(std::pair<std::string, TSpatialPosition>(iter->first, iter->second));
		}

		/*
		*
		*Read the file with coordinates in Lambert93 transformed by Circe software from
		*oficial France web site
		*and compare with transformation from CSGEO
		*
		*/

		const TrafoTestPoints::TTestPoints& refpt = TrafoTestPoints::_circe_Lambert93_transformation;
		for (auto& line : refpt) {
			std::stringstream indataLambert93(line);
			std::string pointName;
			double xCoordLambert93, yCoordLambert93;
			indataLambert93 >> pointName >> xCoordLambert93 >> yCoordLambert93;
			if(indataLambert93.fail()) continue;

			std::map<std::string, TSpatialPosition>::const_iterator it = afterTransformationLambert93.find(pointName);
			if(it != afterTransformationLambert93.end())
			{
				ensure_equals("Lambert 93 X", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(xCoordLambert93), static_cast<TReal>(0.001));
				ensure_equals("Lambert 93 Y", it->second.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(yCoordLambert93), static_cast<TReal>(0.001));
			}
			else
			{
				ensure("Missing point",false);
			}
		}
	}
}
