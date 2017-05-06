#pragma once

//#include <iostream.h>

#define B.Merge(A) Merge1(B.fp,A)

template <class ElementType>
class Leftist
{
public:

	struct data_struct
	{
		ElementType data;
		int npl;
		data_struct * left;
		data_struct * right;
	}
	data_struct * fp;
	
public:
	Leftist()
		:fp(NULL);
	{
		;	
	}

	data_struct * Merge1(data_struct * One,data_struct * Ano)
	{
		if (One==NULL) return Ano;
		if (Ano==NULL) return One;

		data_struct * back;
		data_struct * temp;
		unsigned char i;
		int npl_left;

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
			One->right=Merge1(One->right,Ano);
		else
			Ano->right=Merge1(Ano->right,One);
		//swap
		if (i)
		{
			if (One->left==NULL)
				npl_left=0;
			else
				npl_left=One->left->npl;

			if (npl_left<npl_right)
			{
				temp=One->left;
				One->left=One->right;
				One->right=temp;
			}

		}
		else
		{
			if (Ano->left==NULL)
				npl_left=0;
			else
				npl_left=Ano->left->npl;
			
			if (npl_left<npl_right)
			{
				temp=Ano->left;
				Ano->left=Ano->right;
				Ano->right=temp;
			}
		}

		
		return back;
	}


};






