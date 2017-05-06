// Setting.cpp : implementation file
//

#include "stdafx.h"
#include "Use.h"
#include "Manipulate.h"
#include "UseDoc.h"
#include "UseView.h"
#include "Setting.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Setting dialog
extern int N;
extern int V;
extern Acceleration A;

Setting::Setting(CWnd* pParent /*=NULL*/)
	: CDialog(Setting::IDD, pParent)
{
	//{{AFX_DATA_INIT(Setting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	L_A=new Acceleration;
	*L_A=A;
	L_V=V;
	L_N=N;
	cuv=(CUseView *)pParent;
}
Setting::~Setting(){

	delete L_A;

}

void Setting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Setting)
	DDX_Control(pDX, IDC_SLIDER2, m_y);
	DDX_Control(pDX, IDC_SLIDER1, m_x);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Setting, CDialog)
	//{{AFX_MSG_MAP(Setting)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_ADD1, OnButtonAdd1)
	ON_BN_CLICKED(IDC_BUTTON_ADD2, OnButtonAdd2)
	ON_BN_CLICKED(IDC_BUTTON_MINUS2, OnButtonMinus2)
	ON_BN_CLICKED(IDC_BUTTON_MINUS1, OnButtonMinus1)
	ON_BN_CLICKED(IDC_BUTTON_MINUS3, OnButtonMinus3)
	ON_BN_CLICKED(IDC_BUTTON_ADD3, OnButtonAdd3)
	ON_WM_PAINT()
	ON_WM_CAPTURECHANGED()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Setting message handlers

BOOL Setting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CStatic * fp;
	CButton * bp;
	
	int shi;
	int ge;
	CString cs;
	
	shi=L_N/10;
	ge=L_N%10;
	
	if (shi==3){
		bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD1);
		bp->EnableWindow(FALSE);
	}
	else if (shi==0){
		bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS1);
		bp->EnableWindow(FALSE);

	}
	if (ge==9){
		bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD2);
		bp->EnableWindow(FALSE);
	}
	else if(ge==0){
		bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS2);
		bp->EnableWindow(FALSE);
	}

	cs.Format("%d",shi);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX1);
	fp->SetWindowText(cs);

	cs.Format("%d",ge);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX2);
	fp->SetWindowText(cs);
	//球数设置完毕

	shi=L_V;
	if (shi==9){
		bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD3);
		bp->EnableWindow(FALSE);
	}
	else if (shi==1){
		bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS3);
		bp->EnableWindow(FALSE);

	}

	cs.Format("%d",shi);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX3);
	fp->SetWindowText(cs);
	//速度等级设置完毕
	m_x.SetRange(0,20);
	m_x.SetPos((int)(10+L_A->ax*10));
	m_y.SetRange(0,20);
	m_y.SetPos((int)(10+L_A->ay*10));

	cs.Format("%.1f",L_A->ax);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX4);
	fp->SetWindowText(cs);

	cs.Format("%.1f",L_A->ay);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX5);
	fp->SetWindowText(cs);


	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Setting::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void Setting::OnButtonAdd1() 
{
	CString cs;
	CStatic * fp;
	CButton * bp;
	int shi;

	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX1);
	bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD1);
		
	L_N+=10;
	shi=L_N/10;
	if (shi==3){
		bp->EnableWindow(FALSE);
	}
	bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS1);
	bp->EnableWindow(TRUE);

	cs.Format("%d",shi);
	fp->SetWindowText(cs);

}

void Setting::OnButtonAdd2() 
{
	CString cs;
	CStatic * fp;
	CButton * bp;
	int ge;

	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX2);
	bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD2);
		
	L_N++;
	ge=L_N%10;
	if (ge==9){
		bp->EnableWindow(FALSE);
	}
	bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS2);
	bp->EnableWindow(TRUE);

	cs.Format("%d",ge);
	fp->SetWindowText(cs);	
}

void Setting::OnButtonMinus2() 
{
	CString cs;
	CStatic * fp;
	CButton * bp;
	int ge;

	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX2);
	bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS2);
		
	L_N--;
	ge=L_N%10;
	if (ge==0){
		bp->EnableWindow(FALSE);
	}
	bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD2);
	bp->EnableWindow(TRUE);

	cs.Format("%d",ge);
	fp->SetWindowText(cs);		
}

void Setting::OnButtonMinus1() 
{
	CString cs;
	CStatic * fp;
	CButton * bp;
	int shi;

	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX1);
	bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS1);
		
	L_N-=10;
	shi=L_N/10;
	if (shi==0){
		bp->EnableWindow(FALSE);
	}
	bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD1);
	bp->EnableWindow(TRUE);

	cs.Format("%d",shi);
	fp->SetWindowText(cs);
	
}

void Setting::OnButtonMinus3() 
{
	CString cs;
	CStatic * fp;
	CButton * bp;


	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX3);
	bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS3);
		
	L_V--;
	
	if (L_V==1){
		bp->EnableWindow(FALSE);
	}
	bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD3);
	bp->EnableWindow(TRUE);

	cs.Format("%d",L_V);
	fp->SetWindowText(cs);	
}

void Setting::OnButtonAdd3() 
{
	CString cs;
	CStatic * fp;
	CButton * bp;


	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX3);
	bp=(CButton *)GetDlgItem(IDC_BUTTON_ADD3);
		
	L_V++;
	
	if (L_V==9){
		bp->EnableWindow(FALSE);
	}
	bp=(CButton *)GetDlgItem(IDC_BUTTON_MINUS3);
	bp->EnableWindow(TRUE);

	cs.Format("%d",L_V);
	fp->SetWindowText(cs);		
}

void Setting::OnOK() 
{
	
	if(L_A->ax==A.ax && L_A->ay==A.ay && L_N==N ){//不作处理
		V=L_V;
	}
	else{//重新开始
		if (N)
			delete cuv->mf;
		N=L_N;
		A=*L_A;
		V=L_V;
		if (N){
			cuv->mf=new Manipulate(N,A,cuv);
			cuv->mf->Start();
		}
		else
			cuv->Invalidate();
	}
	
	
	CDialog::OnOK();
}

void Setting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CPen cb(PS_SOLID,2,RGB(120,200,0));


	dc.Ellipse(20,120,100,200);

	CPen * Ocb=dc.SelectObject(&cb);
	dc.MoveTo(60,160);
	dc.LineTo(60+40*L_A->ax,160+40*L_A->ay);

	dc.SelectObject(Ocb);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void Setting::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CDialog::OnCaptureChanged(pWnd);
}

void Setting::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (fabs(point.x-60)+fabs(point.y-160)<=80)
		if (pow((point.x-60),2)+pow((point.y-160),2)<=1600){
			L_A->ax=(int)((point.x-60)/4.0+0.5)/10.0;
			L_A->ay=(int)((point.y-160)/4.0+0.5)/10.0;
			CStatic * fp;
			CString  cs;
			
			
			cs.Format("%.1f",L_A->ax);
			fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX4);
			fp->SetWindowText(cs);

			cs.Format("%.1f",L_A->ay);
			fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX5);
			fp->SetWindowText(cs);

			m_x.SetPos((int)(10+L_A->ax*10));
			m_y.SetPos((int)(10+L_A->ay*10));

			InvalidateRect(CRect(20,120,100,200));



			
			CDialog::OnLButtonDown(nFlags, point);
		}
}

void Setting::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString cs;
	CStatic * fp;
	
	L_A->ax=(m_x.GetPos()-10)*0.1;	
	cs.Format("%.1f",L_A->ax);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX4);
	fp->SetWindowText(cs);
	*pResult = 0;
	InvalidateRect(CRect(20,120,100,200));
}

void Setting::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString cs;
	CStatic * fp;
	
	L_A->ay=(m_y.GetPos()-10)*0.1;	
	cs.Format("%.1f",L_A->ay);
	fp=(CStatic *)GetDlgItem(IDC_STATIC_BOX5);
	fp->SetWindowText(cs);
	InvalidateRect(CRect(20,120,100,200));

	*pResult = 0;
}
