#pragma once

class Complex{
public:
//Attributes
	double u;
	double v;
public:
//Actions
	Complex();
	Complex(double i,double j);
	void in_radian(double r,double alpha);
	void in_degree(double r,double alpha);
	void in_xy(double i,double j);

	void out_radian(double &r,double &alpha);
	void out_degree(double &r,double &alpha);
	
	void operator =(double i);
	void operator =(Complex &ano);

	Complex operator +(double i);
	Complex operator +(Complex &ano);

	Complex operator -(double i);
	Complex operator -(Complex &ano);

	Complex operator *(double i);
	Complex operator *(Complex &ano);

	Complex operator /(double i);
	Complex operator /(Complex &ano);

	Complex operator ^(int i);
	Complex operator ~(void);

	void operator +=(double i);
	void operator +=(Complex &ano);

	void operator -=(double i);
	void operator -=(Complex &ano);

	void operator *=(double i);
	void operator *=(Complex &ano);

	void operator /=(double i);
	void operator /=(Complex &ano);

	bool operator ==(Complex &ano);

};