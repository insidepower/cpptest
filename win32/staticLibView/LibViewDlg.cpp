// LibViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LibView.h"
#include "LibViewDlg.h"

#include "LibContent.h"
#include "dbghelp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibViewDlg dialog

CLibViewDlg::CLibViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLibViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLibViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibViewDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLibViewDlg, CDialog)
	//{{AFX_MSG_MAP(CLibViewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNSEL, OnBtnSelect)
	ON_BN_CLICKED(IDC_BTNEXPORT, OnBtnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibViewDlg message handlers

BOOL CLibViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CListCtrl *pcList = (CListCtrl*)GetDlgItem(IDC_LSTFUNC);

	pcList->ModifyStyle(LVS_EDITLABELS,LVS_SHOWSELALWAYS|LVS_REPORT);
	pcList->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	pcList->InsertColumn(0,"Undecorated",LVCFMT_RIGHT,230,0);
	pcList->InsertColumn(1,"#",LVCFMT_CENTER,30,0);
	pcList->InsertColumn(2,"Decorated",LVCFMT_LEFT,280,0);

	pcList->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	int nArr[] = {1,0,2,3,4};

	pcList->SetColumnOrderArray(3,nArr);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLibViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLibViewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLibViewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLibViewDlg::OnBtnSelect() 
{	
	CFileDialog cFDlg(true,NULL,NULL,OFN_FILEMUSTEXIST,"Library Files (*.Lib)|*.Lib|All Files (*.*)|*.*||",NULL);

	if(cFDlg.DoModal() == IDCANCEL)
		return;

	CString cszPath = cFDlg.GetPathName();
	SetDlgItemText(IDC_EDTFILEPATH,cszPath.GetBuffer(0));
	cszPath.ReleaseBuffer();

	
	CLibContent cLib;
	int nRet;
	void *lpMsgBuf;

	// open the lib and extract the symbols...
	nRet = cLib.Browse(cszPath.GetBuffer(0));
	if(nRet)
	{
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,nRet, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf, 0, NULL);
		MessageBox((LPTSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONERROR);
		LocalFree(lpMsgBuf);
		return;
	}
	cszPath.ReleaseBuffer();

	CListCtrl *pcList = (CListCtrl*)GetDlgItem(IDC_LSTFUNC);
	LVFINDINFO infoFind;

	char *szUndecorated;
	char *szDecorated;	
	DWORD dwCount,i;
	char szTxt[32];

	pcList->DeleteAllItems();
	dwCount = cLib.GetTotalCount();
	DWORD dwLstIndex =0;

	for(i=0;i<dwCount;i++)
	{
		nRet = cLib.GetFuncDetail(i,szDecorated,szUndecorated);
		if(nRet)
		{
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,nRet, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf, 0, NULL);
			MessageBox((LPTSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONERROR);
			LocalFree(lpMsgBuf);
			return;
		}

		infoFind.flags = LVFI_STRING;
		infoFind.psz = szUndecorated;

		nRet =pcList->FindItem(&infoFind);
		if(nRet >=0)
			continue; // no need to add same symbol again

		sprintf(szTxt,"%d",dwLstIndex);

		nRet = pcList->InsertItem(dwLstIndex,szUndecorated);
		nRet = pcList->SetItemText(dwLstIndex,1,szTxt);
		nRet = pcList->SetItemText(dwLstIndex,2,szDecorated);
		
		dwLstIndex++;
		
		delete szDecorated;
		delete szUndecorated;
	}
}

void CLibViewDlg::OnBtnExport() 
{
	CFileDialog cFDlg(false,".h",NULL,OFN_OVERWRITEPROMPT,"C++ Header Files (*.h)|*.h|All Files (*.*)|*.*||",NULL);

	if(cFDlg.DoModal() == IDCANCEL)
		return;

	int nRet;
	char szBuff[512];
	DWORD dwBytes;
	void *lpMsgBuf;

	CListCtrl *pcList = (CListCtrl*)GetDlgItem(IDC_LSTFUNC);
	int nCount;

	HANDLE hFile = CreateFile(cFDlg.GetPathName().GetBuffer(0),GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf, 0, NULL);
		MessageBox((LPTSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONERROR);
		LocalFree(lpMsgBuf);
		return;
	}
	
	nCount = pcList->GetItemCount();

	//"__imp__"	
	for(int i=0;i<nCount;i++)
	{
		pcList->GetItemText(i,0,szBuff,512);
		nRet = WriteFile(hFile,szBuff,strlen(szBuff),&dwBytes,0);
		if(!nRet)
		{
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf, 0, NULL);
			MessageBox((LPTSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONERROR);
			LocalFree(lpMsgBuf);
			return;
		}
		strcpy(szBuff,";\r\n");
		WriteFile(hFile,szBuff,strlen(szBuff),&dwBytes,0);
	}
	strcpy(szBuff,"\r\n");
	WriteFile(hFile,szBuff,strlen(szBuff),&dwBytes,0);
	CloseHandle(hFile);
}

