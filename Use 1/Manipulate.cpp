#include "stdafx.h"

#include "Manipulate.h"
#include "OpenBitmap.h"

#include "UseDoc.h"
#include "UseView.h"

#include "math.h"

#define D 30

int V;
int N;
Acceleration A;

Manipulate::Manipulate(int amount,Acceleration a,CUseView * fp)
	:state(FALSE)
{
	p_p=fp;
	this->amount=amount;
	this->a=a;
	c_p=new Ball[amount];
	int i;
	int rnd;
	for (i=0;i<amount;i++){//设置图像
		rnd=randEx(6);
		c_p[i].map=p_p->cbitmap[rnd];
	}
}

Manipulate::~Manipulate(){
	delete [] c_p;
	p_p->KillTimer(1);

}
void Manipulate::Start(void){
	state=TRUE;
	CRect rc;
	p_p->GetClientRect(&rc);
	
	int i;

	for (i=0;i<amount;i++){//设置位置，速度等
		//设置初始位置
		while(1){
			//rnd 函数继续获得新坐标
			
			c_p[i].Position.x=D/2+randEx(rc.right-D);
			c_p[i].Position.y=D/2+randEx(rc.bottom-D);
			if (Judge_Mutual(i,0))
				break;			
		}
		//设置初始速度
		c_p[i].Velocity.vx=randEx(10)+randEx(10)*0.1;
		c_p[i].Velocity.vy=randEx(10)+randEx(10)*0.1;
		//考虑速度方向
		if(randEx(2))
			c_p[i].Velocity.vx=-c_p[i].Velocity.vx;
		if(randEx(2))
			c_p[i].Velocity.vy=-c_p[i].Velocity.vy;

		//拷贝初始位置
		c_p[i].D_Position=c_p[i].Position;
		//设置初始质量
		c_p[i].M=1;
	}
	p_p->SetTimer(1,60,NULL);
	p_p->Invalidate();


}
void Manipulate::UpdateWindow(void){//更新无效区
	CRect rect;
	int i;
	for (i=0;i<amount;i++){//更新新的位置
		
		rect.left=c_p[i].D_Position.x-D/2;
		rect.top=c_p[i].D_Position.y-D/2;
		rect.right=c_p[i].D_Position.x+D/2;
		rect.bottom=c_p[i].D_Position.y+D/2;
		p_p->InvalidateRect(rect,TRUE);
		//覆盖旧值
	
		
		rect.left=c_p[i].Position.x-D/2;
		rect.top=c_p[i].Position.y-D/2;
		rect.right=c_p[i].Position.x+D/2;
		rect.bottom=c_p[i].Position.y+D/2;
		p_p->InvalidateRect(rect,TRUE);
		
		//更新旧的位置
		c_p[i].D_Position=c_p[i].Position;
	}
	
	return ;
}
BOOL Manipulate::Judge_Mutual(int n,char module){//module 0 布局 module 1 正式 
	int i;
	switch (module){
	case 0:
		for(i=0;i<n;i++)
			if (Distance(c_p[i],c_p[n],0)<1.415*D)
				if (Distance(c_p[i],c_p[n],1)<D)
					return FALSE;
		break;
				
	case 1:
		char * st;
		st=Tag;
		for (i=n+1;i<amount;i++){
			if (Distance(c_p[i],c_p[n],0)<1.415*D)
				if (Distance(c_p[i],c_p[n],1)<D){
					*(st++)=i+1;
					*(st++)=0;
				}
		}
		if (st!=Tag){
			*st=0;
			return FALSE;
		}
		break;
	};
	return TRUE;
}
double Manipulate::Distance(Ball & x1,Ball & x2,char module)const{//module 0 直角距离 module 1 直线距离
	double delta_x,delta_y;

	switch (module){
	case 0:
		delta_x=x1.Position.x-x2.Position.x;
		if (delta_x<0)
			delta_x=-delta_x;
		delta_y=x1.Position.y-x2.Position.y;
		if (delta_y<0)
			delta_y=-delta_y;
		
		return delta_x+delta_y;
		break;
	case 1:
		delta_x=x1.Position.x-x2.Position.x;
		delta_y=x1.Position.y-x2.Position.y;
		return sqrt(delta_x*delta_x+delta_y*delta_y);
		break;
	};
}

BOOL Manipulate::Judge_Wall(int n){//1 左墙 2 上墙 3 右墙 4 下墙 
	CRect rect;
	p_p->GetClientRect(&rect);
	
	char * ty=Tag;
	
	//不仅要考虑边界还要考虑速度方向
	if (c_p[n].Position.x<D/2 && c_p[n].Velocity.vx<0){
		*(ty++)=1;
		*(ty++)=0;
	}
	else if (c_p[n].Position.x>rect.right-D/2 && c_p[n].Velocity.vx>0){
		*(ty++)=3;
		*(ty++)=0;
	}
	if (c_p[n].Position.y<D/2 && c_p[n].Velocity.vy<0){
		*(ty++)=2;
		*(ty++)=0;
	}
	else if (c_p[n].Position.y>rect.bottom-D/2 && c_p[n].Velocity.vy>0){
		*(ty++)=4;
		*(ty++)=0;
	}

	if (ty!=Tag){
		*ty=0;
		return FALSE;
	}
	else
		return TRUE;
}
static double Value(double v1,double v2){//计算长度
	double sum;

	sum=v1*v1+v2*v2;

	return sqrt(sum);
}

static int Di(double x){//类似狄利克雷函数
	if (x>=0)
		return 1;
	else 
		return -1;
} 
void Manipulate::Touch(int main,int ano){//处理两球相撞后的弹开
	struct Direction{
		double i;
		double j;
		double value;
	};

	Direction p1,p2;

	//从main指向ano的向量，碰撞法线
	p1.i=c_p[ano].Position.x-c_p[main].Position.x;
	p1.j=c_p[ano].Position.y-c_p[main].Position.y;
	p1.value=Value(p1.i,p1.j);
	//垂直p1的向量，碰撞切线
	p2.i=1;
	p2.j=0-p2.i*p1.i/p1.j;
	p2.value=Value(p2.i,p2.j);

	Direction vmI,vm_,vaI,va_;

	//main的两个向量
	vm_.value=(c_p[main].Velocity.vx*p2.i+c_p[main].Velocity.vy*p2.j)/p2.value;
	vm_.i=p2.i*vm_.value/p2.value;
	vm_.j=p2.j*vm_.value/p2.value;

	vmI.i=c_p[main].Velocity.vx-vm_.i;
	vmI.j=c_p[main].Velocity.vy-vm_.j;
	vmI.value=Value(vmI.i,vmI.j);

	//ano的两个向量
	va_.value=(c_p[ano].Velocity.vx*p2.i+c_p[ano].Velocity.vy*p2.j)/p2.value;
	va_.i=p2.i*va_.value/p2.value;
	va_.j=p2.j*va_.value/p2.value;

	vaI.i=c_p[ano].Velocity.vx-va_.i;
	vaI.j=c_p[ano].Velocity.vy-va_.j;
	vaI.value=Value(vaI.i,vaI.j);

	//
	Direction cmp;
	cmp.i=vaI.i-vmI.i;
	cmp.j=vaI.j-vmI.j;
	if (Di(cmp.j)==Di(p1.j)){
		;//未碰撞
	}
	else{

		
		//切线方向保持不变
		c_p[main].Velocity.vx=vm_.i;
		c_p[main].Velocity.vy=vm_.j;

		c_p[ano].Velocity.vx=va_.i;
		c_p[ano].Velocity.vy=va_.j;
		//加上法线方向互相交换

		c_p[main].Velocity.vx+=vaI.i;
		c_p[main].Velocity.vy+=vaI.j;

		c_p[ano].Velocity.vx+=vmI.i;
		c_p[ano].Velocity.vy+=vmI.j;
	
	}
}
void Manipulate::Move(double t){
	int i;
	char * ma;
	int ano;
	
	for (i=0;i<amount;i++){//全体移位
		c_p[i].Position.x+=c_p[i].Velocity.vx*t;
		c_p[i].Position.y+=c_p[i].Velocity.vy*t;
		//全体加速
		c_p[i].Velocity.vx+=a.ax*t;
		c_p[i].Velocity.vy+=a.ay*t;
	}
		
	for (i=0;i<amount;i++){//撞球处理
		if (!Judge_Mutual(i,1)){
			ma=Tag;
			while(1){
				ano=(int )*ma-1;
				Touch(i,ano);
				ma+=2;
				if (*ma==0)
					break;	
			}
		}
	}	
	for (i=0;i<amount;i++){//撞墙处理
		if (!Judge_Wall(i)){
			ma=Tag;
			while (1){
				switch (*ma){
				case 1://左墙
				case 3://右墙
					c_p[i].Velocity.vx=-c_p[i].Velocity.vx;
					break;
				
					
				case 2://上墙
				case 4://下墙
					c_p[i].Velocity.vy=-c_p[i].Velocity.vy;				
				}			
				ma+=2;
				if (*ma==0)
					break;
			}
		}
	}
}
