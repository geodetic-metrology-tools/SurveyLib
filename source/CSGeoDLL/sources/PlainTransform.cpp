// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <PlainTransform.h>
#include <TOptionsCheck.h>

#include  <SpatialObjFns.h>

#include <TPlainDataParameters.h>
#include <utils/PositionVectorUtils.h>

#include <TDataParameters.h>
#include <TRefFrameInfo.h>
#include <TAngle.h>
#include <TLength.h>
#include <TPositionVector.h>
#include <TSpatialPosition.h>
#include <TSpatialPoint.h>

#include <memory>
#include <stdexcept>

#include <string>

#include <iostream>
#include <sstream>

#ifdef USE_SWISSTOPO
#using "ReframeLibWrapper.dll"
#using "swisstopo.reframelib.dll"
#using "swisstopo.data.dll"
using namespace System; // Object
using namespace System::IO; // Path
using namespace System::Reflection; // Assembly
using namespace System::Runtime::InteropServices; // Marshal

static Assembly^ AssemblyResolveWrapper(Object^ Sender, ResolveEventArgs^ args) 
{
	AssemblyName^ assemblyName = gcnew AssemblyName(args->Name);
	if (assemblyName->Name == "ReframeLibWrapper") 
	{
		String^ path = Path::Combine(Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location), "ReframeLibWrapper.dll");
		return Assembly::LoadFile(path);
	
	}
	return nullptr;
}

static Assembly^ AssemblyResolveLib(Object^ Sender, ResolveEventArgs^ args) 
{
	AssemblyName^ assemblyName = gcnew AssemblyName(args->Name);
	if (assemblyName->Name == "swisstopo.reframelib") 
	{
		String^ path = Path::Combine(Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location), "swisstopo.reframelib.dll");
		return Assembly::LoadFile(path);
		
	}
	return nullptr;
}
static Assembly^ AssemblyResolveData(Object^ Sender, ResolveEventArgs^ args)
{
	AssemblyName^ assemblyName = gcnew AssemblyName(args->Name);
	if (assemblyName->Name == "swisstopo.data")
		{
			String^ path = Path::Combine(Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location), "swisstopo.data.dll");
			return Assembly::LoadFile(path);
		}
	return nullptr;
}
#endif
extern "C"
{
#ifdef USE_SWISSTOPO
	bool isInitialized = false;

	void Initialize()
	{
		if (!isInitialized)
		{
			AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(AssemblyResolveWrapper);
			AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(AssemblyResolveLib);
			AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(AssemblyResolveData);

			isInitialized = true;
		}
	}
#endif

	SU_DECLSPEC int DLLAPI transformPoint(double *x_long, double *y_lat, double *z_h, const TPlainDataParameters *inputParams, const TPlainLocalSystemOrigin *inputLSO,
		const TPlainDataParameters *outputParams, const TPlainLocalSystemOrigin *outputLSO)
	{
#ifdef USE_SWISSTOPO
		Initialize();
#endif

		std::shared_ptr<TOptionsCheck> options;
		try
		{
			options.reset(new TOptionsCheck(*inputParams, inputLSO, *outputParams, outputLSO));
		}
		catch (EStatusCode e)
		{
			return e;
		}
		const TDataParameters &inputDp = options->getInputDataParameters();
		const TDataParameters &outputDp = options->getOutputDataParameters();

		// Create a spatial position in the input reference frame
		TSpatialPosition position(inputDp.getRefFrame());

		// Populate the spatial position with the input coordinates
		try
		{
			position.setCoordinates(utils::getPositionVector(*x_long, *y_lat, *z_h, inputDp));
		}
		catch (const std::invalid_argument &e)
		{
			std::cerr << "CSGEODLL: Could not create the TPositionVector from the given input parameters: " << e.what() << std::endl;
			return kInvalidInputCoordSys;
		}

		// Transform the position to output reference frame
		try
		{
			position.transform(outputDp.getRefFrame());
		}
		catch (const std::exception &e)
		{
			std::cerr << "CSGEODLL: Transformation error: " << e.what() << std::endl;
			return kTransformError;
		}

		// Attempt to extract the new coordinates from the position
		try
		{
			utils::extractCoordinates(position, x_long, y_lat, z_h, outputDp);
		}
		catch (const std::invalid_argument &e)
		{
			std::cerr << "CSGEODLL: Could not extract the coordinates from the transformed TSpatialPosition: " << e.what() << std::endl;
			return kInvalidOutputCoordSys;
		}

		return kOk;
	}
}
