# Microsoft Developer Studio Project File - Name="FiltersAndFormats" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FiltersAndFormats - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FiltersAndFormats.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FiltersAndFormats.mak" CFG="FiltersAndFormats - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FiltersAndFormats - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FiltersAndFormats - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FiltersAndFormats - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\FiltersAndFormats"
# PROP Scc_LocalPath "."
CPP=cl.exe
F90=df.exe
RSC=rc.exe

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\ProjectFramework\FiltersAndFormats.lib"

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\ProjectFramework\FiltersAndFormats.lib"

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FiltersAndFormats___Win32_Insure"
# PROP BASE Intermediate_Dir "FiltersAndFormats___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FiltersAndFormats___Win32_Insure"
# PROP Intermediate_Dir "FiltersAndFormats___Win32_Insure"
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
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\ProjectFramework\FiltersAndFormats.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\ProjectFramework\FiltersAndFormats.lib"

!ENDIF 

# Begin Target

# Name "FiltersAndFormats - Win32 Release"
# Name "FiltersAndFormats - Win32 Debug"
# Name "FiltersAndFormats - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;f90;for;f;fpp"
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\T100MicroGonsFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\T2DPlusHFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\T3DCartesianFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TDMSFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TGeodeticFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TGonsFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TKilometresFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TLengthFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TMetresFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TMillimetresFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TRadiansFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TWPS2DFilter.cpp

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TWPSTFilter.cpp

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TWPSVFilter.cpp

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TWTW2DFilter.cpp

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TWTWHFilter.cpp

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\source\ProjectFramework\FiltersAndFormats\TWTWVFilter.cpp

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\..\include\setformat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\T100MicroGonsFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\T2DPlusHFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\T3DCartesianFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TAngleFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TDMSFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGeodeticFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGonsFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TKilometresFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TLengthFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TMetresFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TMillimetresFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TRadiansFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TSpatialPositionFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWPS2DFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWPSFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWPSTFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWPSVFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWTW2DFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWTWFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWTWHFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\include\TWTWVFilter.h

!IF  "$(CFG)" == "FiltersAndFormats - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "FiltersAndFormats - Win32 Insure"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
