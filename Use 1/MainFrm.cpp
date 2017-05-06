// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Use.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_NEW_CONFIG, OnNewConfig)
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_WM_CREATE()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	 
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.style &= ~WS_MAXIMIZEBOX; //禁止窗口最大化
//   cs.style &= ~WS_MINIMIZEBOX; //禁止窗口最小化
//    cs.style &= ~WS_SYSMENU; //取消Title上的按钮
    cs.style &= ~WS_THICKFRAME;//使窗口不能用鼠标改变大小
    cs.lpszClass = AfxRegisterWndClass(0);
	cs.cx=1009;
	cs.cy=723;

	
	
	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnNewConfig() 
{
	// TODO: Add your command handler code here
	
}



void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnClose();
}

void CMainFrame::OnAppExit() //取消按钮
{
	SendMessage(WM_CLOSE);
	
}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);
	
	return 0;
}

