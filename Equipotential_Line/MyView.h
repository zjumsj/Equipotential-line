// MyView.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYVIEW_H__65EE8CA2_A8D3_4C17_A27F_B0F584CA55C4__INCLUDED_)
#define AFX_MYVIEW_H__65EE8CA2_A8D3_4C17_A27F_B0F584CA55C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

struct point_charge{
	CString name;
	double Q;
	int x;
	int y;
	unsigned long color;
}; 

class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();
	unsigned long cmyview_color;
	CPoint cmyview_position;//鼠标点击的绝对位置
	CPoint cmyview_yuandian;//原点的绝对位置
	double cmyview_Q;//点电荷电量
	CRect kehuqu;
	vector<point_charge> TAT;
	int count;//统计电荷总数
	int scanwidth;//扫描长度
	double potential_slice;//达到多少扫描一次 阶


// Operations
public:
	void Draw_potential(CDC * pDC);
	double Potential(double ix,double iy);	//计算电势
	void Line(double &ix,double &iy,double &alpha);//计算电场线
	

	void Reclined_Dich(double &x,double &y,double alpha,double trigger);//倾斜线的二分法
	double Line_Dich(double line,double x,double y,double trigger);//直线的二分法

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnNewPoint();
	afx_msg void OnNewPoint1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyView.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYVIEW_H__65EE8CA2_A8D3_4C17_A27F_B0F584CA55C4__INCLUDED_)
