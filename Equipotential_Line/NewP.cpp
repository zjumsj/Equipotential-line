// NewP.cpp : implementation file
//

#include "stdafx.h"
#include "My.h"
#include "NewP.h"
#include "math.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static bool Yuan(int x,int y);

/////////////////////////////////////////////////////////////////////////////
// NewP dialog


NewP::NewP(CWnd* pParent /*=NULL*/)
	: CDialog(NewP::IDD, pParent)
{
	who_do_it=0;
	newp_color=0;
	newp_position.x=newp_position.y=-1;
	newp_Q=1;
	newp_name="";

	//{{AFX_DATA_INIT(NewP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void NewP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NewP)
	DDX_Control(pDX, IDC_NAME, m_con);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NewP, CDialog)
	//{{AFX_MSG_MAP(NewP)
	ON_WM_PAINT()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewP message handlers

void NewP::OnOK() 
{
	//Write in some useful data

	CString cs;
	const char * ch ;
	
	GetDlgItemText(IDC_X,cs);//获得字符串
	ch=cs;
	newp_position.x=(int)atof(ch);

	GetDlgItemText(IDC_Y,cs);//获得字符串
	ch=cs;
	newp_position.y=(int)atof(ch);

	GetDlgItemText(IDC_Q,cs);//获得字符串
	ch=cs;
	newp_Q=atof(ch);

	GetDlgItemText(IDC_NAME,cs);
	newp_name=cs;

	CDialog::OnOK();
}

BOOL NewP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	switch(who_do_it){//根据不同的切入位置来判断显示的标题
	case 1:
	case 2:
		this->SetWindowText("新建点电荷");
		break;


	};

	//读取点的位置
	CStatic * cs;
	CString temp1;

	if (who_do_it==2){
		cs=(CStatic *)GetDlgItem(IDC_X);
		cs->SetWindowText("0");

		cs=(CStatic *)GetDlgItem(IDC_Y);
		cs->SetWindowText("0");
	
	}
	else{
		cs=(CStatic *)GetDlgItem(IDC_X);
		temp1.Format("%d",newp_position.x);
		cs->SetWindowText(temp1);

		cs=(CStatic *)GetDlgItem(IDC_Y);
		temp1.Format("%d",newp_position.y);
		cs->SetWindowText(temp1);
	}
	
	//读取点电荷的值
	cs=(CStatic *)GetDlgItem(IDC_Q);
	temp1.Format("%lf",newp_Q);
	cs->SetWindowText(temp1);
	
	//读取点电荷的名字
	cs=(CStatic *)GetDlgItem(IDC_NAME);
	cs->SetWindowText(newp_name);

	m_con.SetLimitText(10);
	


	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void NewP::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CPen cp;
	CPen * old_cp;
	CBrush cb;
	CBrush * old_cb;

	cp.CreatePen(PS_NULL,0,(unsigned long)0);
	cb.CreateSolidBrush(newp_color);
	
	old_cp=dc.SelectObject(&cp);
	old_cb=dc.SelectObject(&cb);

	dc.Ellipse(305,10,345,50);

	//还原
	dc.SelectObject(old_cp);
	dc.SelectObject(old_cb);




	
	
}

void NewP::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void NewP::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (Yuan(point.x,point.y)){
		CColorDialog myC(newp_color,CC_FULLOPEN,this);
		if (myC.DoModal())
		{
			newp_color=myC.GetColor();
		}
		InvalidateRect(CRect(305,10,345,50));
	
	}
}

static bool Yuan(int x,int y){
	int sum;
	sum=fabs(x-325)+fabs(y-30);
	if ((double)sum>1.42*20)
		return false;
	else{
		sum=(x-325)*(x-325);
		sum+=(y-30)*(y-30);
		if (sqrt(sum)<=20.0)
			return true;
		
	}
	return false;

}

void NewP::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
