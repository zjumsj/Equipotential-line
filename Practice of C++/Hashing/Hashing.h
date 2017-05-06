#ifndef _HASHING_H
#define _HASHING_H
#endif

#include <iostream.h>

template <class ElementType> 
class Hashing{//Read Insert Can not Delete
private:	
	struct data_index{
		ElementType data;
		int index;	
	};

	int Capacity;
	int Pos;
	int Index;

	data_index * fp;
	int * header;

	int pointer;
public:
	Hashing(int size,int index_num)//index_num=0,1,2,...,index_num-1
	{
		if (index_num>size)
			cout<<"Fatal Error: index_num is bigger than size!"<<endl;
		else
		{
			Pos=0;
			pointer=-1;
			fp=new data_index[size];
			
			Capacity=size;
			Index=index_num;
			
			header=new int[index_num];
			
			int i;
			for (i=0;i<index_num;i++)
				header[i]=-1;
		}
	}

	~Hashing(){
		delete [] fp;
		delete [] header;	
	
	}

	bool Insert(int index,ElementType a)
	{
		bool ch=false;
		if (Is_Full())
			cout<<"Hashing table is full!"<<endl;
		else
		{
			if (index>=Index)
				cout<<"Out of Range!"<<endl;
			else
			{
				
				int temp;
				temp=header[index];
				
				fp[Pos].data=a;

				header[index]=Pos;
				fp[Pos].index=temp;

				Pos++;
				ch=true;
			}
		}
		return ch;
	}

	bool Search(ElementType a){
		bool ch=false;

		if (a>=Index)
			cout<<"Out of Range!"<<endl;
		else
		{
			pointer=header[a];
			ch=true;
		}
		return ch;
	} 

	ElementType * Read(void){
		ElementType * result;

		if (pointer==-1) 
			result=NULL;
		else
		{
			result=&(fp[pointer].data);
			pointer=fp[pointer].index;
		}
		return result;	
	}

	bool Is_Full()
	{	return(Pos>=Capacity);}

	bool Is_Empty()
	{	return(Pos==0);}

};