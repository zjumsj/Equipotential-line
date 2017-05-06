/*

	左倾堆得C算法实现   by mark 2015.11.8  

*/

#ifndef _LEFTIST_H
#define _LEFTIST_H
#endif

typedef int ElementType;


typedef struct da_lf
{
	ElementType data;
	int npl;	
	struct da_lf * left;
	struct da_lf * right;
	
}data_struct;


data_struct * Merge(data_struct * One,data_struct * Ano);//两个左倾堆做Merge
data_struct * NewOne(ElementType a);					//把一个元素变成链表结构
data_struct * Delete(data_struct * One);				//把最小的那个元素删除
void Destroy(data_struct * One);				//销毁 释放内存
