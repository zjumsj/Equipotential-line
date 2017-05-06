// UseView.h : interface of the CUseView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USEVIEW_H__DD2A37BC_5596_4094_9DE9_73F3E5847C33__INCLUDED_)
#define AFX_USEVIEW_H__DD2A37BC_5596_4094_9DE9_73F3E5847C33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Manipulate;
class CUseView : public CView
{
protected: // create from serialization only
	CUseView();
	DECLARE_DYNCREATE(CUseView)

// Attributes
public:
	CUseDoc * GetDocument();
	CBitmap * cbitmap[6];
	Manipulate * mf;
	

// Operations
public:
	void Paint_Picture(CDC * pDC);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUseView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileNew();
	afx_msg void OnNewConfig();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in UseView.cpp
inline CUseDoc* CUseView::GetDocument()
   { return (CUseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEVIEW_H__DD2A37BC_5596_4094_9DE9_73F3E5847C33__INCLUDED_)
