/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

// Define the variables necessary for the export and import of DLL functions

#ifndef __linux__

	//#ifdef SU_MAKEDLL
	   #define  SU_DECLSPEC  __declspec(dllexport)
	//#else
	//   #define  SU_DECLSPEC  __declspec(dllimport)
	//#endif


	#define DLLAPI __stdcall
	//#define DLLAPI __cdecl

#else

	#define DLLAPI
	#define SU_DECLSPEC

#endif
