#include "stdlib.h"
#include "leftist.h"


data_struct * Merge(data_struct * One,data_struct * Ano)
{
	data_struct * back;
	data_struct * temp;
	unsigned char i;
	int npl_left;
	
	
	if (One==NULL) return Ano;
	if (Ano==NULL) return One;

	

	if(One->data<Ano->data){
		back=One;
		i=1;
	}
	else{
		back=Ano;
		i=0;
	}
	//get fp
	if (i)
		One->right=Merge(One->right,Ano);
	else
		Ano->right=Merge(Ano->right,One);
	//swap
	if (i)
	{
		if (One->left==NULL)
			npl_left=-1;
		else
			npl_left=One->left->npl;

		if (npl_left<One->right->npl)
		{
			temp=One->left;
			One->left=One->right;
			One->right=temp;

			One->npl=npl_left+1;
		}
		else
			One->npl=One->right->npl+1;
		

	}
	else
	{
		if (Ano->left==NULL)
			npl_left=-1;
		else
			npl_left=Ano->left->npl;
		
		if (npl_left<Ano->right->npl)
		{
			temp=Ano->left;
			Ano->left=Ano->right;
			Ano->right=temp;

			Ano->npl=npl_left+1;
		}
		else
			Ano->npl=Ano->right->npl+1;
	}
	
	
	return back;
}

data_struct * NewOne(ElementType a)
{
	data_struct * b;
	b=malloc(sizeof(data_struct));
	b->left=b->right=NULL;
	b->npl=0;
	b->data=a;
	return b;
}

data_struct * Delete(data_struct * One)
{
	data_struct * left_c,* right_c;
	left_c=One->left;
	right_c=One->right;
	free(One);
	return Merge(left_c,right_c);

}

void Destroy(data_struct * One)
{
	if (One->left==NULL && One->right==NULL)
		free(One);
	else
	{
		if (One->left!=NULL)
			Destroy(One->left);
		if (One->right!=NULL)
			Destroy(One->right);
	}
	return;

}