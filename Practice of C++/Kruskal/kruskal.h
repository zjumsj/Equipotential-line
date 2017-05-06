#pragma once

#include "matrix.h"

struct E{//链表
	int u;//smaller one
	int v;//larger one
	double w;
	E * np;

};
//破圈法
double Rosenstiehl(Matrix<double> & st,char * & ans);//输入一个对称矩阵（关联矩阵），返还最大割集的权和割集
//避圈法
double Prim(Matrix<double> & st,char * & ans);//输入一个对称矩阵（关联矩阵），找到最优树
double Kruskal(Matrix<double> & st,char * & ans);//输入一个对称矩阵（关联矩阵）,找到最优树

//Private Functions:
static char * write_char(char * inn,int num);
static int find_root(int ser,int *all);
static void cut_circle(char * Ins,int n);


