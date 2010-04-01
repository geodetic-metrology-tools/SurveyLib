# Microsoft Developer Studio Project File - Name="LSAlgoTests" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=LSAlgoTests - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LSAlgoTests.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LSAlgoTests.mak" CFG="LSAlgoTests - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LSAlgoTests - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "LSAlgoTests - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU Source] SurveyLib|SurveyLib>SurveyLib\SurveyLib Projects\LSAlgorithms\LSAlgoTests"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LSAlgoTests - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "LSAlgoTests - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LSAlgoTests - Win32 Release"
# Name "LSAlgoTests - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\source\LSAlgorithms\LSAlgoTests\ErelExtractTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\LSAlgorithms\LSAlgoTests\LSAlgoTests.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\..\..\lib\ConstraintMeasurements.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\ContributionsGenerators.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\FiltersAndFormats.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\InstrumentStations.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\LocalSystemCG.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\MeasurementConstants.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\Measurements.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\ProjectData.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\ROMs.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\SpatialMeas.lib
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\AffineTransformations\Debug\AffineTransformations.lib
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\MathematicalConcepts\Debug\MathematicalConcepts.lib
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\ReferenceSurfaces\Debug\ReferenceSurfaces.lib
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\RefFrameTransformations\Debug\RefFrameTransformations.lib
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\ShortestPath\Debug\ShortestPath.lib
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\SpatialSystems\Debug\SpatialSystems.lib
# End Source File
# Begin Source File

SOURCE=G:\Support\SurveyingEng\software\nagc\dll\nagc.lib
# End Source File
# Begin Source File

SOURCE="..\..\..\..\LGC++\LGCppVCppProjects\LSCalcObservations\Debug\LSCalcObservations.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\LGC++\LGCppVCppProjects\LSCalcObservationSet\Debug\LSCalcObservationSet.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\LGC++\LGCppVCppProjects\Observations\Debug\Observations.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\LGC++\LGCppVCppProjects\ObservationSet\Debug\ObservationSet.lib"
# End Source File
# Begin Source File

SOURCE=..\..\SpatialObjects\SpatialObjs\Debug\SpatialObjs.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\StreamFormatters.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\CalcElements.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\lgcProject.lib
# End Source File
# Begin Source File

SOURCE=..\geodeticsystemcg\Debug\GeodeticSystemCG.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\CtoCPP\lsapps.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\CtoCPP\geodefs.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\CtoCPP\genmat.lib
# End Source File
# End Target
# End Project
