# Microsoft Developer Studio Project File - Name="testSpatialObj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=testSpatialObj - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "testSpatialObj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "testSpatialObj.mak" CFG="testSpatialObj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "testSpatialObj - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "testSpatialObj - Win32 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName "<[SU Source] SurveyLib|SurveyLib>Win32 SurveyLib Files\testSpatialObj"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "testSpatialObj - Win32 Release"

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
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "testSpatialObj - Win32 Debug"

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
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "testSpatialObj - Win32 Release"
# Name "testSpatialObj - Win32 Debug"
# Begin Group "AffineTransformations"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\TAAffineTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TAAffineTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TAffineTransformWrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TAffineTransformWrapper.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TCompositeAffTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TCompositeAffTransform.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TEnlargement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TEnlargement.h
# End Source File
# Begin Source File

SOURCE=..\..\source\THelmertTransformation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\THelmertTransformation.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TReflection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TReflection.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TRotation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TRotation.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TTranslation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TTranslation.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TVAffineTransformation.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\source\TAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\Source\TANumericValue.h
# End Source File
# Begin Source File

SOURCE=..\..\source\testTransformations.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TFreeVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\TFreeVector.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TLength.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TLength.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TPositionVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\TPositionVector.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TRotationMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TRotationMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TSpatialOrientation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TSpatialOrientation.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TSpatialPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\TSpatialPosition.h
# End Source File
# Begin Source File

SOURCE=..\..\source\TSpatialVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\TSpatialVector.h
# End Source File
# End Target
# End Project
