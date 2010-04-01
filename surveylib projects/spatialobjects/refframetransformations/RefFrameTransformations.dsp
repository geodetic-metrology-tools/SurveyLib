# Microsoft Developer Studio Project File - Name="RefFrameTransformations" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RefFrameTransformations - Win32 Insure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RefFrameTransformations.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RefFrameTransformations.mak" CFG="RefFrameTransformations - Win32 Insure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RefFrameTransformations - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RefFrameTransformations - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RefFrameTransformations - Win32 Insure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "<[SU source] SurveyLib|SurveyLib>SurveyLib\SpatialObjects\RefFrameTransformations"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RefFrameTransformations - Win32 Release"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\RefFrameTransformations.lib"

!ELSEIF  "$(CFG)" == "RefFrameTransformations - Win32 Debug"

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
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\RefFrameTransformations.lib"

!ELSEIF  "$(CFG)" == "RefFrameTransformations - Win32 Insure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RefFrameTransformations___Win32_Insure"
# PROP BASE Intermediate_Dir "RefFrameTransformations___Win32_Insure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "RefFrameTransformations___Win32_Insure"
# PROP Intermediate_Dir "RefFrameTransformations___Win32_Insure"
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
# ADD BASE LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\RefFrameTransformations.lib"
# ADD LIB32 /nologo /out:".\..\..\..\lib\SpatialObjects\RefFrameTransformations.lib"

!ENDIF 

# Begin Target

# Name "RefFrameTransformations - Win32 Release"
# Name "RefFrameTransformations - Win32 Debug"
# Name "RefFrameTransformations - Win32 Insure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TARefFrameTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TGC2LGTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\refframetransformations\TGC2MLATransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\THelmertRefFrameTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TLA2LGTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TLG2GCTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TLG2LATransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\refframetransformations\TMLA2GCTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TMLA2XYHeTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\refframetransformations\TMLA2XYHsTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\RefFrameTransformations\TX0Y0He2XYHeTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\SpatialObjects\RefFrameTransformations\TXYHe2MLATransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\RefFrameTransformations\TXYHe2X0Y0HeTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\RefFrameTransformations\TXYHe2XYHgTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\RefFrameTransformations\TXYHg2XYHeTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\SpatialObjects\refframetransformations\TXYHs2MLATransformation.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\TARefFrameTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGC2LGTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TGC2MLATransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\THelmertRefFrameTransform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TLA2LGTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TLG2GCTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TLG2LATransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TMLA2GCTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TMLA2XYHeTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TMLA2XYHsTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVRefFrameTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TVTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TX0Y0He2XYHeTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHe2MLATransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHe2X0Y0HeTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHe2XYHgTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHg2XYHeTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\TXYHs2MLATransformation.h
# End Source File
# End Group
# End Target
# End Project
