; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUseView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Use.h"
LastPage=0

ClassCount=6
Class1=CUseApp
Class2=CUseDoc
Class3=CUseView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=Setting
Resource3=IDD_DIALOG1

[CLS:CUseApp]
Type=0
HeaderFile=Use.h
ImplementationFile=Use.cpp
Filter=N
LastObject=CUseApp

[CLS:CUseDoc]
Type=0
HeaderFile=UseDoc.h
ImplementationFile=UseDoc.cpp
Filter=N
LastObject=CUseDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CUseView]
Type=0
HeaderFile=UseView.h
ImplementationFile=UseView.cpp
Filter=C
LastObject=CUseView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Use.cpp
ImplementationFile=Use.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_NEW_CONFIG
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_NEW_CONFIG
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
CommandCount=9

[DLG:IDD_DIALOG1]
Type=1
Class=Setting
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_BUTTON_ADD1,button,1342242816
Control5=IDC_BUTTON_MINUS1,button,1342242816
Control6=IDC_STATIC_BOX1,static,1350696960
Control7=IDC_BUTTON_ADD2,button,1342242816
Control8=IDC_BUTTON_MINUS2,button,1342242816
Control9=IDC_STATIC_BOX2,static,1350696960
Control10=IDC_STATIC,button,1342177287
Control11=IDC_BUTTON_ADD3,button,1342242816
Control12=IDC_BUTTON_MINUS3,button,1342242816
Control13=IDC_STATIC_BOX3,static,1350696960
Control14=IDC_STATIC,button,1342177287
Control15=IDC_SLIDER1,msctls_trackbar32,1342242840
Control16=IDC_SLIDER2,msctls_trackbar32,1342242840
Control17=IDC_STATIC_BOX4,static,1350696960
Control18=IDC_STATIC_BOX5,static,1350696960
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352

[CLS:Setting]
Type=0
HeaderFile=Setting.h
ImplementationFile=Setting.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

