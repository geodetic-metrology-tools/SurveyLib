# Microsoft Developer Studio Project File - Name="SpatialSystems" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SpatialSystems - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SpatialSystems.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SpatialSystems.mak" CFG="SpatialSystems - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SpatialSystems - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SpatialSystems - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SpatialSystems - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\SpatialSystems"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialSystems.lib"

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialSystems.lib"

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SpatialSystems___Win32_Insure"
# PROP BASE Intermediate_Dir "SpatialSystems___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SpatialSystems___Win32_Insure"
# PROP Intermediate_Dir "SpatialSystems___Win32_Insure"
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
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialSystems.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialSystems.lib"

!ENDIF 

# Begin Target

# Name "SpatialSystems - Win32 Release"
# Name "SpatialSystems - Win32 Debug"
# Name "SpatialSystems - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialsystems\TASpatialAttribute.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialsystems\TSpatialOrientation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialsystems\TSpatialOrientationError.cpp

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\SpatialSystems\TSpatialPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\SpatialSystems\TSpatialPositionError.cpp

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialsystems\TSpatialStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\SpatialSystems\TSpatialVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialsystems\TSpatialVectorError.cpp

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\counted_ptr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TASpatialAttribute.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialOrientation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialOrientationError.h

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPosition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPositionError.h

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialVectorError.h

!IF  "$(CFG)" == "SpatialSystems - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "SpatialSystems - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
