#pragma once

class CUseView;

struct Ball{
	double M;
	CBitmap * map;
	struct {
		double x;
		double y;
	}Position,D_Position;
	struct {
		double vx;
		double vy;
	}Velocity;

};

struct Acceleration{
	double ax;
	double ay;
};


class Manipulate{
//Attributes
public:
	BOOL state;
	Acceleration a;
	int amount;
	Ball * c_p;
	CUseView * p_p;
	char Tag[300];

//Actions	
public:
	void Move(double t);
	

	Manipulate(int amount,Acceleration a,CUseView * fp);
	~Manipulate();
	
	void Start(void);
	void UpdateWindow(void);

private:
	BOOL Judge_Mutual(int n,char module);
	BOOL Judge_Wall(int n);
	void Touch(int main,int ano);
	double Distance(Ball & x1,Ball & x2,char module) const;







};