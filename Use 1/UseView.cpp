// UseView.cpp : implementation of the CUseView class
//

#include "stdafx.h"
#include "Use.h"

#include "UseDoc.h"
#include "UseView.h"
//
#include "Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseView

#include <afx.h>

#include "OpenBitmap.h"
#include "Manipulate.h"

#define D 30

extern int V;
extern int N;
extern Acceleration A;



IMPLEMENT_DYNCREATE(CUseView, CView)

BEGIN_MESSAGE_MAP(CUseView, CView)
	//{{AFX_MSG_MAP(CUseView)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_NEW_CONFIG, OnNewConfig)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseView construction/destruction

CUseView::CUseView()
{
	// TODO: add construction code here
	int i;
	HBITMAP hbitmap;
	CString cs;
	
	for (i=0;i<6;i++){
		cbitmap[i]=new CBitmap;
		cs.Format("%d",i+1);
		cs=CString("pic\\")+cs+CString(".bmp");
		OpenBitmap(cs,hbitmap,TRUE);
		cbitmap[i]->Attach(hbitmap);
	}

	//初始化
	N=30;
	V=5;
	A.ax=0;
	A.ay=0;

}

CUseView::~CUseView()
{
	int i;
	for (i=0;i<6;i++){
		delete cbitmap[i];
	}
	
}

BOOL CUseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUseView drawing
void CUseView::Paint_Picture(CDC * pDC){
	CRect rc;
	GetClientRect(&rc);//获得更新区域CDC bkgDC;
	
	CRect ballsize;
	
	CDC bkgDC;
	bkgDC.CreateCompatibleDC(pDC);
	
	//重新写入背景
	HBITMAP hbitmap;
	CBitmap * cbk;
	CString cs;
	cbk=new CBitmap;
	cs="pic\\冰.bmp";
	OpenBitmap(cs,hbitmap,TRUE);
	cbk->Attach(hbitmap);

	CBitmap * Oldbk=bkgDC.SelectObject(cbk);

	if (!N){
		pDC->BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&bkgDC,rc.left,rc.top,SRCCOPY);
		bkgDC.SelectObject(Oldbk);
		delete cbk;
		return ;
	}
	
	
	CDC ImageDC;//绘制球
	ImageDC.CreateCompatibleDC(pDC);
	
	int i;
	CBitmap * OldOne;
	for (i=0;i<mf->amount;i++){
		if (i==0)
			OldOne=ImageDC.SelectObject(mf->c_p[i].map);
		else
			ImageDC.SelectObject(mf->c_p[i].map);
		ballsize.left=mf->c_p[i].Position.x-D/2;
		ballsize.top=mf->c_p[i].Position.y-D/2;
		ballsize.right=mf->c_p[i].Position.x+D/2;
		ballsize.bottom=mf->c_p[i].Position.y+D/2;
		if (!TransparentBlt(
			bkgDC.m_hDC,
			ballsize.left,
			ballsize.top,
			D,
			D,
			ImageDC.m_hDC,
			0,0,D,D,
			RGB(0,0,0)))
			MessageBox("Error");
	}
	
	//将最终结果画在屏幕上
	pDC->BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&bkgDC,rc.left,rc.top,SRCCOPY);
	
	//还原画笔
	ImageDC.SelectObject(OldOne);
	bkgDC.SelectObject(Oldbk);

	//把画过的bitmap清理干净
	delete cbk;


}

void CUseView::OnDraw(CDC* pDC)
{
	CUseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	

	Paint_Picture(pDC);


}

/////////////////////////////////////////////////////////////////////////////
// CUseView diagnostics

#ifdef _DEBUG
void CUseView::AssertValid() const
{
	CView::AssertValid();
}

void CUseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUseDoc* CUseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUseDoc)));
	return (CUseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUseView message handlers
void  CUseView::OnTimer(UINT   nIDEvent) //插入函数
{
	int i;
	for (i=0;i<150;i++){
		mf->Move(0.0007*V);
	}
	mf->UpdateWindow();
	
}




void CUseView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	mf=new Manipulate(N,A,this);
	mf->Start();

	
}

BOOL CUseView::OnEraseBkgnd(CDC* pDC) 
{
	
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CUseView::OnFileNew() 
{
	if (!N) return ;

	delete mf;

	mf=new Manipulate(N,A,this);
	mf->Start();
	return;	
}



void CUseView::OnNewConfig() 
{
	Setting cad(this);
	cad.DoModal();
	
}
