#include "complex.h"
#include "math.h"

#define PI 3.14159265359

Complex::Complex()
	:u(0),v(0)
{
	;
}

Complex::Complex(double i,double j){
	u=i;
	v=j;
}

void Complex::in_xy(double i,double j){
	u=i;
	v=j;
}

void Complex::in_radian(double r,double alpha){
	u=r*cos(alpha);
	v=r*sin(alpha);
}
void Complex::in_degree(double r,double alpha){
	double belta;
	belta=alpha*PI/180;
	u=r*cos(belta);
	v=r*sin(belta);
}
void Complex::out_radian(double &r,double &alpha){
	double k;
	double belta;
	if (u==0 && v==0){
		alpha=0;
		r=0;
		return ;
	}
	
	if (fabs(v)<=fabs(u)){
		k=v/u;
		belta=atan(k);
		if (u<0 && v>=0)
			alpha=belta+PI;
		else if(u<0)
			alpha=belta-PI;
		else
			alpha=belta;
		
	}
	else{
		k=u/v;
		belta=atan(k);
		if (v<0)
			alpha=-PI/2-belta;
		else
			alpha=PI/2-belta;
	}
	r=sqrt(u*u+v*v);
	return;

}
void Complex::out_degree(double &r,double &alpha){
	double k;
	double belta;
	if (u==0 && v==0){
		alpha=0;
		r=0;
		return ;
	}
	
	if (fabs(v)<=fabs(u)){
		k=v/u;
		belta=atan(k);
		if (u<0 && v>=0)
			alpha=belta+PI;
		else if(u<0)
			alpha=belta-PI;
		else
			alpha=belta;
		
	}
	else{
		k=u/v;
		belta=atan(k);
		if (v<0)
			alpha=-PI/2-belta;
		else
			alpha=PI/2-belta;
	}
	alpha=alpha*180/PI;
	r=sqrt(u*u+v*v);
	return;

}
void Complex::operator =(double i){
	u=i;
	v=0;
}
void Complex::operator =(Complex &ano){
	u=ano.u;
	v=ano.v;

}

Complex Complex::operator +(double i){
	Complex ans;
	ans.u=u+i;
	ans.v=v;
	return ans;
}
Complex Complex::operator +(Complex &ano){
	Complex ans;
	ans.u=u+ano.u;
	ans.v=v+ano.v;
	return ans;
}

Complex Complex::operator -(double i){
	Complex ans;
	ans.u=u-i;
	ans.v=v;
	return ans;

}
Complex Complex::operator -(Complex &ano){
	Complex ans;
	ans.u=u-ano.u;
	ans.v=v-ano.v;
	return ans;
}

Complex Complex::operator *(double i){
	Complex ans;
	ans.u=u*i;
	ans.v=v*i;
	return ans;
}
Complex Complex::operator *(Complex &ano){
	Complex ans;
	ans.u=u*ano.u-v*ano.v;
	ans.v=v*ano.u+u*ano.v;
	return ans;
}

Complex Complex::operator /(double i){
	Complex ans;
	if (i==0){
		ans=(*this);
		return ans;
	}

	ans.u=u/i;
	ans.v=v/i;
	return ans;
}
Complex Complex::operator /(Complex &ano){
	Complex ans;
	double xishu;
	xishu=ano.u*ano.u+ano.v*ano.v;
	if( xishu==0){
		ans=(*this);
		return ans;
	}
	ans=(*this)*~ano;
	ans=ans/xishu;
	return ans;
}

Complex Complex::operator ^(int i){
	Complex ans;
	bool signal=false;
	ans.u=1;
	ans.v=0;
	if (i<0){
		i=-i;
		signal=true;
	}
	for (;i!=0;i--){
		ans=ans*(*this);
	}
	
	if (signal==true){
		ans=Complex(1,0)/ans;	
	}
	return ans;
}
Complex Complex::operator ~(void){
	Complex ans;
	ans.u=u;
	ans.v=-v;
	return ans;
}


void Complex::operator +=(double i){
	u+=i;
}
void Complex::operator +=(Complex &ano){
	u+=ano.u;
	v+=ano.v;
}

void Complex::operator -=(double i){
	u-=i;
}
void Complex::operator -=(Complex &ano){
	u-=ano.u;
	v-=ano.v;
}
void Complex::operator *=(double i){
	u*=i;
	v*=i;
}
void Complex::operator *=(Complex &ano){
	double iu;
	double iv;

	iu=u*ano.u-v*ano.v;
	iv=v*ano.u+u*ano.v;
	u=iu;
	v=iv;
}

void Complex::operator /=(double i){
	if (i==0)
		return;
	u/=i;
	v/=i;
}
void Complex::operator /=(Complex &ano){
	double iu,iv;
	double xishu;
	xishu=ano.u*ano.u+ano.v*ano.v;
	if( xishu==0){
		return;
	}
	iu=u*ano.u+v*ano.v;
	iv=v*ano.u-u*ano.v;
	iu/=xishu;
	iv/=xishu;
	u=iu;
	v=iv;
}

bool Complex::operator ==(Complex &ano){
	if (u==ano.u && v==ano.v)
		return true;
	else
		return false;

}
