// Define the variables necessary for the export of DLL functions

#ifndef __linux__

	#define SU_DECLSPEC __declspec(dllexport)
	#define DLLAPI __cdecl

#else

	#define DLLAPI
	#define SU_DECLSPEC

#endif
