# Microsoft Developer Studio Project File - Name="ReferenceSurfaces" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ReferenceSurfaces - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ReferenceSurfaces.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReferenceSurfaces.mak" CFG="ReferenceSurfaces - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReferenceSurfaces - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ReferenceSurfaces - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ReferenceSurfaces - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\ReferenceSurfaces"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ReferenceSurfaces - Win32 Release"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\ReferenceSurfaces.lib"

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\ReferenceSurfaces.lib"

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ReferenceSurfaces___Win32_Insure"
# PROP BASE Intermediate_Dir "ReferenceSurfaces___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ReferenceSurfaces___Win32_Insure"
# PROP Intermediate_Dir "ReferenceSurfaces___Win32_Insure"
# PROP Target_Dir ""
LINK32=link.exe -lib
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\ReferenceSurfaces.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\ReferenceSurfaces.lib"

!ENDIF 

# Begin Target

# Name "ReferenceSurfaces - Win32 Release"
# Name "ReferenceSurfaces - Win32 Debug"
# Name "ReferenceSurfaces - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\ReferenceSurfaces\T3DLocalRefFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\ReferenceSurfaces\TA2DPlus1MapProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TA2DXYRefFrame.cpp

!IF  "$(CFG)" == "ReferenceSurfaces - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TA3DEuclideanRefFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\referencesurfaces\TAGeoidModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TAModifiedLocalAstronomicalRF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TAReferenceFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TCernGridGeoid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TCernParabolicGeoid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\referencesurfaces\TCernSphereGeoid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TGeodeticRefFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TGraphLocalAstronomicalRF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TGraphMLARF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TModifiedLocalAstronomicalRF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\referencesurfaces\TModifiedLocalGeodeticRF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\ReferenceSurfaces\TReferenceEllipsoid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\ReferenceSurfaces\TX0Y0HeProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\ReferenceSurfaces\TXYHeProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\ReferenceSurfaces\TXYHgProjection.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\T3DLocalRefFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TA2DPlus1MapProjection.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TA2DXYRefFrame.h

!IF  "$(CFG)" == "ReferenceSurfaces - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TA3DEuclideanRefFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAGeoidModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAModifiedLocalAstronomicalRF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAReferenceFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TCernGridGeoid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TCernParabolicGeoid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TCernSphereGeoid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGeodeticRefFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGraphLocalAstronomicalRF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGraphMLARF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TModifiedLocalAstronomicalRF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TModifiedLocalGeodeticRF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TReferenceEllipsoid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVGeoidModel.h

!IF  "$(CFG)" == "ReferenceSurfaces - Win32 Release"

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Debug"

!ELSEIF  "$(CFG)" == "ReferenceSurfaces - Win32 Insure"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVReferenceFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TX0Y0HeProjection.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHeProjection.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHgProjection.h
# End Source File
# End Group
# End Target
# End Project
