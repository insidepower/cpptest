// LibView.h : main header file for the LIBVIEW application
//

#if !defined(AFX_LIBVIEW_H__4D9A1A9E_7228_447D_8FB2_605330DE618A__INCLUDED_)
#define AFX_LIBVIEW_H__4D9A1A9E_7228_447D_8FB2_605330DE618A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLibViewApp:
// See LibView.cpp for the implementation of this class
//

class CLibViewApp : public CWinApp
{
public:
	CLibViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLibViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBVIEW_H__4D9A1A9E_7228_447D_8FB2_605330DE618A__INCLUDED_)
