#if !defined(AFX_SETTING_H__CA27238E_E2FD_49F2_B006_FE0A46AF9744__INCLUDED_)
#define AFX_SETTING_H__CA27238E_E2FD_49F2_B006_FE0A46AF9744__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Setting dialog
struct Acceleration;

class Setting : public CDialog
{
//Attribute
public:
	int L_N;
	Acceleration * L_A;
	int L_V;
	CUseView * cuv;

// Construction
public:
	Setting(CWnd* pParent = NULL);   // standard constructor
	~Setting();


// Dialog Data
	//{{AFX_DATA(Setting)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_y;
	CSliderCtrl	m_x;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Setting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Setting)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonAdd1();
	afx_msg void OnButtonAdd2();
	afx_msg void OnButtonMinus2();
	afx_msg void OnButtonMinus1();
	afx_msg void OnButtonMinus3();
	afx_msg void OnButtonAdd3();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTING_H__CA27238E_E2FD_49F2_B006_FE0A46AF9744__INCLUDED_)
