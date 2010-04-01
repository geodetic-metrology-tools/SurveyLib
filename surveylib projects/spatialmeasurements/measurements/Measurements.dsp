# Microsoft Developer Studio Project File - Name="Measurements" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Measurements - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Measurements.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Measurements.mak" CFG="Measurements - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Measurements - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Measurements - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Measurements - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\SurveyLib Projects\SpatialMeasurements\Measurements"
# PROP Scc_LocalPath "."
CPP=cl.exe
F90=df.exe
RSC=rc.exe

!IF  "$(CFG)" == "Measurements - Win32 Release"

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
# ADD BASE F90 /compile_only /nologo /warn:nofileopt
# ADD F90 /compile_only /nologo /warn:nofileopt
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialMeasurements\Measurements.lib"

!ELSEIF  "$(CFG)" == "Measurements - Win32 Debug"

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
# ADD BASE F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialMeasurements\Measurements.lib"

!ELSEIF  "$(CFG)" == "Measurements - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Measurements___Win32_Insure"
# PROP BASE Intermediate_Dir "Measurements___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Measurements___Win32_Insure"
# PROP Intermediate_Dir "Measurements___Win32_Insure"
# PROP Target_Dir ""
# ADD BASE F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\SpatialMeasurements\Measurements.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialMeasurements\Measurements.lib"

!ENDIF 

# Begin Target

# Name "Measurements - Win32 Release"
# Name "Measurements - Win32 Debug"
# Name "Measurements - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\T2DOffsetMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TALineMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TAMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TAMeasurementListener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TAObjectMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TAPlaneMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TAPointMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TATargetlessMeas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\THorAngleMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\THorizontalDistMeas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TOffsetToSpaLineMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TOffsetToTheoPlaneMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TOffsetToVerLineMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TOffsetToVerPlaneMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TSpatialDistMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TVerticalDistMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TVMeasurementListener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TWireToWireDistMeas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TWPSMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialMeasurements\Measurements\TZenithDistMeasurement.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\..\include\T2DOffsetMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TALineMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAMeasurementListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAObjectMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAPlaneMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAPointMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TATargetlessMeas.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\THorAngleMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\THorizontalDistMeas.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TOffsetToSpaLineMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TOffsetToTheoPlaneMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TOffsetToVerLineMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TOffsetToVerPlaneMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialDistMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVerticalDistMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVMeasurementListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWireToWireDistMeas.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWPSMeasurement.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TZenithDistMeasurement.h
# End Source File
# End Group
# End Target
# End Project
