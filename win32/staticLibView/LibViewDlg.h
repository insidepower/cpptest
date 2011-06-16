// LibViewDlg.h : header file
//

#if !defined(AFX_LIBVIEWDLG_H__65874128_2540_4208_979E_3CF122D01A91__INCLUDED_)
#define AFX_LIBVIEWDLG_H__65874128_2540_4208_979E_3CF122D01A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLibViewDlg dialog 

class CLibViewDlg : public CDialog
{
// Construction
public:
	CLibViewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLibViewDlg)
	enum { IDD = IDD_LIBVIEW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	
	// Generated message map functions
	//{{AFX_MSG(CLibViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSelect();
	afx_msg void OnBtnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBVIEWDLG_H__65874128_2540_4208_979E_3CF122D01A91__INCLUDED_)
