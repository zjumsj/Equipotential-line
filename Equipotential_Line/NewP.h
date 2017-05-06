#if !defined(AFX_NEWP_H__F61CA9E7_35BD_4032_A9A8_27F9E49F7F40__INCLUDED_)
#define AFX_NEWP_H__F61CA9E7_35BD_4032_A9A8_27F9E49F7F40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewP dialog

class NewP : public CDialog
{
public:
	int who_do_it;
	unsigned long newp_color;//点的颜色
	CPoint newp_position;//点的相对位置
	CString newp_name;//点的名字
	double newp_Q;//点电荷量


// Construction
public:
	NewP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NewP)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_con;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NewP)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWP_H__F61CA9E7_35BD_4032_A9A8_27F9E49F7F40__INCLUDED_)
