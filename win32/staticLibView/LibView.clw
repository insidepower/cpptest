; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLibViewDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LibView.h"

ClassCount=3
Class1=CLibViewApp
Class2=CLibViewDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LIBVIEW_DIALOG

[CLS:CLibViewApp]
Type=0
HeaderFile=LibView.h
ImplementationFile=LibView.cpp
Filter=N

[CLS:CLibViewDlg]
Type=0
HeaderFile=LibViewDlg.h
ImplementationFile=LibViewDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CLibViewDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=LibViewDlg.h
ImplementationFile=LibViewDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LIBVIEW_DIALOG]
Type=1
Class=CLibViewDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDTFILEPATH,edit,1350633600
Control4=IDC_BTNSEL,button,1342242816
Control5=IDC_LSTFUNC,SysListView32,1350631945
Control6=IDC_BTNEXPORT,button,1342242816

