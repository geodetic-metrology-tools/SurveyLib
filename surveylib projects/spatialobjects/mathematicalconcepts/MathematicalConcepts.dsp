# Microsoft Developer Studio Project File - Name="MathematicalConcepts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MathematicalConcepts - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MathematicalConcepts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MathematicalConcepts.mak" CFG="MathematicalConcepts - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MathematicalConcepts - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MathematicalConcepts - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "MathematicalConcepts - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\MathematicalConcepts"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MathematicalConcepts - Win32 Release"

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
LINK32=link.exe -lib
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\MathematicalConcepts.lib"

!ELSEIF  "$(CFG)" == "MathematicalConcepts - Win32 Debug"

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
LINK32=link.exe -lib
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "SU_MAKEDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\MathematicalConcepts.lib"

!ELSEIF  "$(CFG)" == "MathematicalConcepts - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MathematicalConcepts___Win32_Insure"
# PROP BASE Intermediate_Dir "MathematicalConcepts___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MathematicalConcepts___Win32_Insure"
# PROP Intermediate_Dir "MathematicalConcepts___Win32_Insure"
# PROP Target_Dir ""
LINK32=link.exe -lib
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "SU_MAKEDLL" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "SU_MAKEDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\MathematicalConcepts.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\MathematicalConcepts.lib"

!ENDIF 

# Begin Target

# Name "MathematicalConcepts - Win32 Release"
# Name "MathematicalConcepts - Win32 Debug"
# Name "MathematicalConcepts - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\T2DCartesianCoordSys.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\T2DCartesianPlusHSys.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\T3DCartesianCoordSys.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\T3DMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TACoordinateSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TACoordSysMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TACoordSysVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TANumericValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TColumnVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TCoordSysFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TDist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TDouble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TFreeVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TGeodeticCoordSys.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TLength.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TPositionVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\MathematicalConcepts\TRotationMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\mathematicalconcepts\TScalar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\T2DCartesianCoordSys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\T2DCartesianPlusHSys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\T3DCartesianCoordSys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\T3DMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TACoordinateSystem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TACoordSysMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TACoordSysVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TANumericValue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TColumnVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TCoordSysFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TDist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TDouble.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TFreeVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGeodeticCoordSys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TLength.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TPositionVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TRotationMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TScalar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVCoordinateSystem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVNumericValue.h
# End Source File
# End Group
# Begin Source File

SOURCE=F:\software\nagc\include\nag.h
# End Source File
# Begin Source File

SOURCE=F:\software\nagc\include\nagf03.h
# End Source File
# Begin Source File

SOURCE=F:\software\nagc\include\nagf04.h
# End Source File
# Begin Source File

SOURCE=F:\software\nagc\include\nagf06.h
# End Source File
# End Target
# End Project
