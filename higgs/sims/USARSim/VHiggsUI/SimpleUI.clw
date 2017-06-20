; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSimpleUIDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpleUI.h"

ClassCount=8
Class1=CSimpleUIApp
Class2=CSimpleUIDlg
Class3=CAboutDlg

<<<<<<< SimpleUI.clw
ResourceCount=9
Resource1=IDD_INFO_DLG (Chinese (P.R.C.))
=======
ResourceCount=9
Resource1=IDD_INFO_DLG (Chinese (P.R.C.))
>>>>>>> 1.7
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX (English (U.S.))
Class4=CSETUP
Class5=CControlDlg
Class6=CCmdSocket
Class7=CVideoSocket
Resource4=IDD_CONTROL_DLG (English (U.S.))
Resource5=IDD_ABOUTBOX
Resource6=IDD_SIMPLEUI_DIALOG
<<<<<<< SimpleUI.clw
Resource7=IDD_SIMPLEUI_DIALOG (English (U.S.))
=======
Resource7=IDD_SIMPLEUI_DIALOG (English (U.S.))
Class8=CInfoDlg
Resource8=IDD_INFO_DLG
Resource9=IDD_CONTROL_DLG
>>>>>>> 1.7

[CLS:CSimpleUIApp]
Type=0
HeaderFile=SimpleUI.h
ImplementationFile=SimpleUI.cpp
Filter=N

[CLS:CSimpleUIDlg]
Type=0
HeaderFile=SimpleUIDlg.h
ImplementationFile=SimpleUIDlg.cpp
Filter=D
LastObject=CSimpleUIDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SimpleUIDlg.h
ImplementationFile=SimpleUIDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SIMPLEUI_DIALOG]
Type=1
Class=CSimpleUIDlg
ControlCount=27
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CHOST,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CPORT,edit,1350639744
Control6=IDC_STATIC,static,1342308352
Control7=IDC_MODEL,combobox,1344340227
Control8=IDC_STATIC,static,1342308352
Control9=IDC_POSITION,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_VHOST,edit,1484849280
Control14=IDC_STATIC,static,1342308352
Control15=IDC_VPORT,edit,1484857472
Control16=IDC_STATIC,button,1342177287
Control17=IDC_REMOTE,button,1342308361
Control18=IDC_LOCAL,button,1342308361
Control19=IDC_STATIC,static,1342308352
Control20=IDC_RESOLUTION,msctls_trackbar32,1342242832
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_RESOLUTION2,edit,1342244992
Control24=IDC_STATIC,static,1342308352
Control25=IDC_FPS,edit,1350631552
Control26=IDC_FPS2,msctls_updown32,1342177312
Control27=IDC_START,button,1342242816

[CLS:CSETUP]
Type=0
HeaderFile=SETUP.h
ImplementationFile=SETUP.cpp
BaseClass=CDialog
Filter=D
LastObject=CSETUP
VirtualFilter=dWC

[DLG:IDD_CONTROL_DLG]
Type=1
Class=CControlDlg
ControlCount=29
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CUP,button,1342251008
Control3=IDC_CLEFT,button,1342242816
Control4=IDC_CRIGHT,button,1342242816
Control5=IDC_CDOWN,button,1342251008
Control6=IDC_STATIC,button,1342177287
Control7=IDC_VUP,button,1342251008
Control8=IDC_VLEFT,button,1342242816
Control9=IDC_VRIGHT,button,1342242816
Control10=IDC_VDOWN,button,1342251008
Control11=IDC_STATIC_VIDEO,button,1342177287
Control12=IDC_SPEED_UP,button,1342283776
Control13=IDC_SPEED_DOWN,button,1342283776
Control14=IDC_ZOOM_IN,button,1342275584
Control15=IDC_ZOOM_OUT,button,1342275584
Control16=IDC_STOP,button,1342283776
Control17=IDC_STATIC,static,1342308352
Control18=IDC_FPS,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_WIDTH,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_HEIGHT,edit,1350631552
Control23=IDC_UPDATE,button,1342210084
Control24=IDC_SHOWUT,button,1476493312
Control25=IDC_MSG_TREE,SysTreeView32,1350631431
Control26=IDC_STATIC,static,1342308352
Control27=IDC_VIDEO,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_LIGHT,button,1342242816

[CLS:CControlDlg]
Type=0
HeaderFile=controldlg.h
ImplementationFile=controldlg.cpp
BaseClass=CDialog
LastObject=CControlDlg
Filter=D
VirtualFilter=dWC

[CLS:CCmdSocket]
Type=0
HeaderFile=CmdSocket.h
ImplementationFile=CmdSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CCmdSocket
VirtualFilter=uq

[CLS:CVideoSocket]
Type=0
HeaderFile=VideoSocket.h
ImplementationFile=VideoSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CVideoSocket
VirtualFilter=uq

[DLG:IDD_CONTROL_DLG (English (U.S.))]
Type=1
Class=CControlDlg
ControlCount=29
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CUP,button,1342251008
Control3=IDC_CLEFT,button,1342242816
Control4=IDC_CRIGHT,button,1342242816
Control5=IDC_CDOWN,button,1342251008
Control6=IDC_STATIC,button,1342177287
Control7=IDC_VUP,button,1342251008
Control8=IDC_VLEFT,button,1342242816
Control9=IDC_VRIGHT,button,1342242816
Control10=IDC_VDOWN,button,1342251008
Control11=IDC_STATIC_VIDEO,button,1342177287
Control12=IDC_SPEED_UP,button,1342283776
Control13=IDC_SPEED_DOWN,button,1342283776
Control14=IDC_ZOOM_IN,button,1342275584
Control15=IDC_ZOOM_OUT,button,1342275584
Control16=IDC_STOP,button,1342283776
Control17=IDC_STATIC,static,1342308352
Control18=IDC_FPS,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_WIDTH,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_HEIGHT,edit,1350631552
Control23=IDC_UPDATE,button,1342210084
Control24=IDC_SHOWUT,button,1476493312
Control25=IDC_MSG_TREE,SysTreeView32,1350631431
Control26=IDC_STATIC,static,1342308352
Control27=IDC_VIDEO,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_LIGHT,button,1342242816

[DLG:IDD_SIMPLEUI_DIALOG (English (U.S.))]
Type=1
Class=CSimpleUIDlg
ControlCount=27
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CHOST,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CPORT,edit,1350639744
Control6=IDC_STATIC,static,1342308352
Control7=IDC_MODEL,combobox,1344340227
Control8=IDC_STATIC,static,1342308352
Control9=IDC_POSITION,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_VHOST,edit,1484849280
Control14=IDC_STATIC,static,1342308352
Control15=IDC_VPORT,edit,1484857472
Control16=IDC_STATIC,button,1342177287
Control17=IDC_REMOTE,button,1342308361
Control18=IDC_LOCAL,button,1342308361
Control19=IDC_STATIC,static,1342308352
Control20=IDC_RESOLUTION,msctls_trackbar32,1342242832
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_RESOLUTION2,edit,1342244992
Control24=IDC_STATIC,static,1342308352
Control25=IDC_FPS,edit,1350631552
Control26=IDC_FPS2,msctls_updown32,1342177312
Control27=IDC_START,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_INFO_DLG]
Type=1
Class=CInfoDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816

[CLS:CInfoDlg]
Type=0
HeaderFile=InfoDlg.h
ImplementationFile=InfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInfoDlg

[DLG:IDD_INFO_DLG (Chinese (P.R.C.))]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816

