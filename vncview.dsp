# Microsoft Developer Studio Project File - Name="vncview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE x86em) Application" 0x0b01
# TARGTYPE "Win32 (WCE MIPS) Application" 0x0a01
# TARGTYPE "Win32 (WCE SH) Application" 0x0901

CFG=vncview - Win32 (WCE x86em) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vncview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vncview.mak" CFG="vncview - Win32 (WCE x86em) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vncview - Win32 (WCE x86em) Release" (based on\
 "Win32 (WCE x86em) Application")
!MESSAGE "vncview - Win32 (WCE x86em) Debug" (based on\
 "Win32 (WCE x86em) Application")
!MESSAGE "vncview - Win32 (WCE MIPS) Release" (based on\
 "Win32 (WCE MIPS) Application")
!MESSAGE "vncview - Win32 (WCE MIPS) Debug" (based on\
 "Win32 (WCE MIPS) Application")
!MESSAGE "vncview - Win32 (WCE SH) Debug" (based on\
 "Win32 (WCE SH) Application")
!MESSAGE "vncview - Win32 (WCE SH) Release" (based on\
 "Win32 (WCE SH) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/vncview", PRBAAAAA"
# PROP Scc_LocalPath "."
# PROP WCE_Configuration "H/PC Ver. 2.00"

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86emRel"
# PROP BASE Intermediate_Dir "x86emRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86emRel"
# PROP Intermediate_Dir "x86emRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /O2 /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /YX /c
# ADD CPP /nologo /W3 /O2 /I "omnithreadce" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /YX"stdhdrs.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x809 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG"
# ADD RSC /l 0x809 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /subsystem:windows /machine:I386 /windowsce:emulation
# ADD LINK32 winsockm.lib commctrl.lib coredll.lib /nologo /subsystem:windows /machine:I386 /windowsce:emulation
EMPFILE=empfile.exe
# ADD BASE EMPFILE -COPY
# ADD EMPFILE -COPY

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86emDbg"
# PROP BASE Intermediate_Dir "x86emDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86emDbg"
# PROP Intermediate_Dir "x86emDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /Zi /Od /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /YX /c
# ADD CPP /nologo /W3 /Gm /Zi /Od /I "omnithreadce" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /FR /YX"stdhdrs.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x809 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_"
# ADD RSC /l 0x809 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /subsystem:windows /debug /machine:I386 /windowsce:emulation
# ADD LINK32 winsockm.lib commctrl.lib coredll.lib /nologo /subsystem:windows /debug /machine:I386 /windowsce:emulation
EMPFILE=empfile.exe
# ADD BASE EMPFILE -COPY
# ADD EMPFILE -COPY

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSRel"
# PROP BASE Intermediate_Dir "WMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSRel"
# PROP Intermediate_Dir "WMIPSRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /ML /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /QMRWCE /c
# ADD CPP /nologo /ML /W3 /O2 /I "omnithreadce" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX"stdhdrs.h" /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x809 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x809 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 winsock.lib commctrl.lib coredll.lib /nologo /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSDbg"
# PROP BASE Intermediate_Dir "WMIPSDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSDbg"
# PROP Intermediate_Dir "WMIPSDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /MLd /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /QMRWCE /c
# ADD CPP /nologo /MLd /W3 /Zi /Od /I "omnithreadce" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX"stdhdrs.h" /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x809 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x809 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 winsock.lib commctrl.lib coredll.lib /nologo /debug /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESHDbg"
# PROP BASE Intermediate_Dir "WCESHDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESHDbg"
# PROP Intermediate_Dir "WCESHDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /MLd /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX /c
# ADD CPP /nologo /MLd /W3 /Zi /Od /I "omnithreadce" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /FR /YX"stdhdrs.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x809 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x809 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /debug /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 winsock.lib commctrl.lib coredll.lib /nologo /debug /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vncview_"
# PROP BASE Intermediate_Dir "vncview_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESHRel"
# PROP Intermediate_Dir "WCESHRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /ML /W3 /O2 /I "omnithreadce" /D "NDEBUG" /D "SH3" /D "_SH3_" /D "_WIN32_WCE" /D "UNICODE" /YX"stdhdrs.h" /c
# ADD CPP /nologo /ML /W3 /O2 /I "omnithreadce" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /YX"stdhdrs.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x809 /r /d "SH3" /d "_SH3_" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x809 /r /d "SH3" /d "_SH3_" /d "_WIN32_WCE" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winsockm.lib commctrl.lib coredll.lib /nologo /machine:IX86 /windowsce:emulation
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 winsock.lib commctrl.lib coredll.lib /nologo /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ENDIF 

# Begin Target

# Name "vncview - Win32 (WCE x86em) Release"
# Name "vncview - Win32 (WCE x86em) Debug"
# Name "vncview - Win32 (WCE MIPS) Release"
# Name "vncview - Win32 (WCE MIPS) Debug"
# Name "vncview - Win32 (WCE SH) Debug"
# Name "vncview - Win32 (WCE SH) Release"
# Begin Source File

SOURCE=.\AboutBox.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_ABOUT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_ABOUT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_ABOUT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_ABOUT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_ABOUT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_ABOUT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_ABOUT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_ABOUT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_ABOUT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_ABOUT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_ABOUT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_ABOUT=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AboutBox.h
# End Source File
# Begin Source File

SOURCE=.\AuthDialog.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_AUTHD=\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_AUTHD=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_AUTHD=\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_AUTHD=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_AUTHD=\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_AUTHD=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_AUTHD=\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_AUTHD=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_AUTHD=\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_AUTHD=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_AUTHD=\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_AUTHD=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AuthDialog.h
# End Source File
# Begin Source File

SOURCE=.\ClientConnection.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_CLIEN=\
	".\AboutBox.h"\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIEN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_CLIEN=\
	".\AboutBox.h"\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIEN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_CLIEN=\
	".\AboutBox.h"\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIEN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_CLIEN=\
	".\AboutBox.h"\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIEN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_CLIEN=\
	".\AboutBox.h"\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIEN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_CLIEN=\
	".\AboutBox.h"\
	".\AuthDialog.h"\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIEN=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClientConnection.h
# End Source File
# Begin Source File

SOURCE=.\ClientConnectionCopyRect.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_CLIENT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_CLIENT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_CLIENT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_CLIENT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_CLIENT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENT=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_CLIENT=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENT=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClientConnectionCoRRE.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_CLIENTC=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTC=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_CLIENTC=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTC=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_CLIENTC=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTC=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_CLIENTC=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTC=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_CLIENTC=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTC=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_CLIENTC=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTC=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClientConnectionHextile.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_CLIENTCO=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCO=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_CLIENTCO=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCO=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_CLIENTCO=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCO=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_CLIENTCO=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCO=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_CLIENTCO=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCO=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_CLIENTCO=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCO=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClientConnectionRaw.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_CLIENTCON=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCON=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_CLIENTCON=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCON=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_CLIENTCON=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCON=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_CLIENTCON=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCON=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_CLIENTCON=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCON=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_CLIENTCON=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCON=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClientConnectionRRE.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_CLIENTCONN=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCONN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_CLIENTCONN=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCONN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_CLIENTCONN=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCONN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_CLIENTCONN=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCONN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_CLIENTCONN=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCONN=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_CLIENTCONN=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_CLIENTCONN=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\d3des.c

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_D3DES=\
	".\d3des.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_D3DES=\
	".\d3des.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_D3DES=\
	".\d3des.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_D3DES=\
	".\d3des.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_D3DES=\
	".\d3des.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_D3DES=\
	".\d3des.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3des.h
# End Source File
# Begin Source File

SOURCE=.\Exception.h
# End Source File
# Begin Source File

SOURCE=.\History.txt
# End Source File
# Begin Source File

SOURCE=.\res\idr_tray.ico
# End Source File
# Begin Source File

SOURCE=.\KeyMap.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_KEYMA=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_KEYMA=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_KEYMA=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_KEYMA=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_KEYMA=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_KEYMA=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_KEYMA=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_KEYMA=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_KEYMA=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_KEYMA=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_KEYMA=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_KEYMA=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KeyMap.h
# End Source File
# Begin Source File

SOURCE=.\keysymdef.h
# End Source File
# Begin Source File

SOURCE=.\Log.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_LOG_C=\
	".\Log.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_LOG_C=\
	".\Log.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_LOG_C=\
	".\Log.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_LOG_C=\
	".\Log.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_LOG_C=\
	".\Log.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_LOG_C=\
	".\Log.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\MRU.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_MRU_C=\
	".\MRU.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_MRU_C=\
	".\MRU.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_MRU_C=\
	".\MRU.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_MRU_C=\
	".\MRU.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_MRU_C=\
	".\MRU.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_MRU_C=\
	".\MRU.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MRU.h
# End Source File
# Begin Source File

SOURCE=.\res\resource.h
# End Source File
# Begin Source File

SOURCE=.\rfb.h
# End Source File
# Begin Source File

SOURCE=.\rfbproto.h
# End Source File
# Begin Source File

SOURCE=.\SessionDialog.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_SESSI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_SESSI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_SESSI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_SESSI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_SESSI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_SESSI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_SESSI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_SESSI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_SESSI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_SESSI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_SESSI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\MRU.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\SessionDialog.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_SESSI=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SessionDialog.h
# End Source File
# Begin Source File

SOURCE=.\stdhdrs.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_STDHD=\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	
# ADD CPP /Yc"stdhdrs.h"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_STDHD=\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	
# ADD CPP /Yc"stdhdrs.h"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_STDHD=\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	
# ADD CPP /Yc"stdhdrs.h"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_STDHD=\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	
# ADD CPP /Yc"stdhdrs.h"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_STDHD=\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	
# ADD CPP /Yc"stdhdrs.h"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_STDHD=\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	
# ADD BASE CPP /Yc"stdhdrs.h"
# ADD CPP /Yc"stdhdrs.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\stdhdrs.h
# End Source File
# Begin Source File

SOURCE=.\res\vnc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vnc32.BMP
# End Source File
# Begin Source File

SOURCE=.\vncauth.c

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_VNCAU=\
	".\d3des.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_VNCAU=\
	".\d3des.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_VNCAU=\
	".\d3des.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_VNCAU=\
	".\d3des.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_VNCAU=\
	".\d3des.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_VNCAU=\
	".\d3des.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\vncauth.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vncauth.h
# End Source File
# Begin Source File

SOURCE=.\VNCOptions.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_VNCOP=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCOP=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_VNCOP=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCOP=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_VNCOP=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCOP=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_VNCOP=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCOP=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_VNCOP=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCOP=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_VNCOP=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCOP=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VNCOptions.h
# End Source File
# Begin Source File

SOURCE=.\vncviewer.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_VNCVI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_VNCVI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_VNCVI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_VNCVI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_VNCVI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVI=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_VNCVI=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVI=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vncviewer.h
# End Source File
# Begin Source File

SOURCE=.\res\vncviewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\vncviewer.rc

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VNCviewerApp.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_VNCVIE=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCVIE=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_VNCVIE=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCVIE=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_VNCVIE=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCVIE=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_VNCVIE=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCVIE=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_VNCVIE=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCVIE=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_VNCVIE=\
	".\ClientConnection.h"\
	".\Exception.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\Log.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\vncviewer.h"\
	".\VNCviewerApp.h"\
	
NODEP_CPP_VNCVIE=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VNCviewerApp.h
# End Source File
# Begin Source File

SOURCE=.\VNCViewerAppCE.cpp

!IF  "$(CFG)" == "vncview - Win32 (WCE x86em) Release"

DEP_CPP_VNCVIEW=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVIEW=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE x86em) Debug"

DEP_CPP_VNCVIEW=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVIEW=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Release"

DEP_CPP_VNCVIEW=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVIEW=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE MIPS) Debug"

DEP_CPP_VNCVIEW=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVIEW=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Debug"

DEP_CPP_VNCVIEW=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVIEW=\
	".\omnithread.h"\
	

!ELSEIF  "$(CFG)" == "vncview - Win32 (WCE SH) Release"

DEP_CPP_VNCVIEW=\
	".\ClientConnection.h"\
	".\KeyMap.h"\
	".\keysymdef.h"\
	".\omnithreadce\ce.h"\
	".\omnithreadce\omnithreadce.h"\
	".\rfb.h"\
	".\rfbproto.h"\
	".\stdhdrs.h"\
	".\VNCOptions.h"\
	".\VNCviewerApp.h"\
	".\VNCviewerAppCE.h"\
	
NODEP_CPP_VNCVIEW=\
	".\omnithread.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VNCviewerAppCE.h
# End Source File
# End Target
# End Project
