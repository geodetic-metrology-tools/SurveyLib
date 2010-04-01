# Microsoft Developer Studio Project File - Name="SpatialObjs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SpatialObjs - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SpatialObjs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SpatialObjs.mak" CFG="SpatialObjs - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SpatialObjs - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SpatialObjs - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SpatialObjs - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\SurveyLib Projects\SpatialObjects\SpatialObjs"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SpatialObjs - Win32 Release"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialObjs.lib"

!ELSEIF  "$(CFG)" == "SpatialObjs - Win32 Debug"

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
# ADD BASE F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialObjs.lib"

!ELSEIF  "$(CFG)" == "SpatialObjs - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SpatialObjs___Win32_Insure"
# PROP BASE Intermediate_Dir "SpatialObjs___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SpatialObjs___Win32_Insure"
# PROP Intermediate_Dir "SpatialObjs___Win32_Insure"
# PROP Target_Dir ""
LINK32=link.exe -lib
F90=df.exe
# ADD BASE F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD F90 /check:bounds /compile_only /debug:full /nologo /traceback /warn:argument_checking /warn:nofileopt
# ADD BASE CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialObjs.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\SpatialObjs.lib"

!ENDIF 

# Begin Target

# Name "SpatialObjs - Win32 Release"
# Name "SpatialObjs - Win32 Debug"
# Name "SpatialObjs - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TASpatialPtListener.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TSpatialLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TSpatialLineName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TSpatialPlane.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TSpatialPlaneName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TSpatialPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TSpatialPointName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\spatialobj\TVSpatialPtListener.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\..\include\TASpatialPtListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialLine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialLineName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPlane.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPlaneName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPointName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVSpatialPtListener.h
# End Source File
# End Group
# End Target
# End Project
