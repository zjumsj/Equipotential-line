// Use.h : main header file for the USE application
//

#if !defined(AFX_USE_H__44DDEF3D_A164_446B_9078_9EE7043C8865__INCLUDED_)
#define AFX_USE_H__44DDEF3D_A164_446B_9078_9EE7043C8865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUseApp:
// See Use.cpp for the implementation of this class
//
class CAboutDlg;

class CUseApp : public CWinApp
{
public:
	CUseApp();
	



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CUseApp)
	afx_msg void OnAppAbout();

	
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USE_H__44DDEF3D_A164_446B_9078_9EE7043C8865__INCLUDED_)
