# Microsoft Developer Studio Project File - Name="EssaisLibrary" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=EssaisLibrary - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EssaisLibrary.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EssaisLibrary.mak" CFG="EssaisLibrary - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EssaisLibrary - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "EssaisLibrary - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU Source] SurveyLib|SurveyLib>SurveyLib\SurveyLib Projects\EssaisLibrary\EssaisLibrary"
# PROP Scc_LocalPath "."
CPP=cl.exe
F90=df.exe
RSC=rc.exe

!IF  "$(CFG)" == "EssaisLibrary - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "EssaisLibrary - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "EssaisLibrary - Win32 Release"
# Name "EssaisLibrary - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeodefs\Win32 Files\Source\errmesg.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgenmat\win32 files\Source\libgenmat.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeofit\win32 files\source\libgeofit.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\liblsapps\win32 files\source\liblsapps.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeofit\win32 files\source\libplnfit.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeodefs\Win32 Files\Source\primtvdefs.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeodefs\Win32 Files\Source\ptcovdefs.c"
# End Source File
# Begin Source File

SOURCE=..\TEssaisLibrary.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeodefs\Win32 Files\Source\vecmat.c"
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeodefs\Win32 Files\Source\vecmatdefs.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\cstructs.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\errmesg.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\geo_utils.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\libgenmat.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\libgeofit.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\liblsapps.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\libplnfit.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\primtvdefs.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\ptcovdefs.h
# End Source File
# Begin Source File

SOURCE=..\TEssaisLibrary.h
# End Source File
# Begin Source File

SOURCE=H:\software\include\vecmat.h
# End Source File
# Begin Source File

SOURCE="..\..\..\workspace\SUSOFT\libgeodefs\Win32 Files\Source\vecmatdefs.h"
# End Source File
# End Group
# End Target
# End Project
