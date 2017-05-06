#pragma once

#include "stdafx.h"


/*
Three types of data structs are included here: Stack,Queue and Heap

*/

template <class ElementType>
class Stack
{
	
private:
	int Capacity;
	int Pos;
	ElementType * fp;
public:
	Stack(int size)
		:Capacity(size)
	{
		fp=new ElementType[size];
		Pos=0;
	}

	~Stack(){
		delete [] fp;
	}

	bool Is_Empty(){
		if (Pos==0)
			return true;
		else
			return false;
	}

	bool Is_Full(){
		if (Pos==Capacity)
			return true;
		else
			return false;
	
	
	}

	ElementType Top(){
		ElementType tp;

		if (!Is_Empty())
			tp=fp[Pos-1];
		
		return tp;
	}

	ElementType Top_Pop(){
		ElementType tp;

		if (!Is_Empty())
			tp=fp[--Pos];
		return tp;
		
	}

	bool Push(ElementType a){
		bool r=false;

		if (!Is_Full())
		{
			fp[Pos++]=a;
			r=true;
		}
		return r;
	}

};


template <class ElementType>
class Queue
{
private:
	int Front;
	int Rear;
	int Capacity;
	bool Meet;
	ElementType *fp;
public:
	Queue(int size){
		fp=new ElementType[size];
		Front=0;
		Rear=0;
		Capacity=size;
		Meet=false;	
	}

	~Queue(){
		delete [] fp;
		
	}
	bool Is_Empty(){
		if (Rear==Front && !Meet)
			return true;
		else 
			return false;
	}

	
	bool Is_Full(){
		return Meet;	
	}

	bool Enqueue(ElementType a){
		bool r=false;

		if (!Meet)
		{
			r=true;
			fp[Front]=a;
			Front++;
			if (Front==Capacity)
				Front=0;
			if (Front==Rear)
				Meet=true;
		}	
		return r;
	}

	ElementType Dequeue(void){
		ElementType r;

		if (!Is_Empty())
		{
			Meet=false;
			r=fp[Rear++];
			if (Rear==Capacity)
				Rear=0;
		}
		return r;	
	}
};

template<class ElementType>
class Heap
{
	
private:
	int Capacity;
	int Pos;
	bool Min;
	ElementType * fp;
private:
	void PercolateDown(int i){//数组下标
		int min;
		int index;

		int next;
		unsigned char s;
		ElementType temp;

		index=i;
		while (1){
			s=0;
			min=fp[2*index];
			if (2*index+1<Pos){
				if (fp[2*index+1]<min ^ !Min){
					min=fp[2*index+1];
					s=1;
				}
			}
			if (min>=fp[index] ^ !Min)break;
			
			next=2*index+(int)s;
			
			temp=fp[index];
			fp[index]=fp[next];
			fp[next]=temp;
			

			index=next;
			if (index*2>=Pos)
				break;
		}
	}
public:
	Heap(int size,bool in){//true 输出最小 false 输出最大
		fp=new ElementType[size+1];//空出零位置
		Capacity=size;
		Pos=1;
		Min=in;
	}

	~Heap(){
		delete [] fp;	
	}

	bool Is_Full(void){
		return (Pos>Capacity);	
	}
	bool Is_Empty(void){
		return (Pos==1);
	
	}
	bool Build_Heap(ElementType * array,int num){
		bool ch=false;
		if	(num<=Capacity){
			int i;

			

			for (i=1;i<num+1;i++)
				fp[i]=array[i-1];
			Pos=num+1;//设置新的值

			for(i=num/2;i>0;i--)
				PercolateDown(i);	
			
			ch=true;		
		}
		return ch;
	}

	bool Insert(ElementType a){
		bool r=false;

		if(!Is_Full()){

			int i;
			int j;
			ElementType temp;
			
			i=Pos;
			j=Pos/2;
			fp[Pos++]=a;
			while (1){
				if (i==1)
					break;
				if (fp[i]>fp[j] ^ Min){//同时发生换位置
					temp=fp[i];
					fp[i]=fp[j];
					fp[j]=temp;
				}
				else
					break;
				i=j;
				j=j/2;
			}
			r=true;
		}

		return r;

	}

	ElementType Read(void){
		if(!Is_Empty())
			return fp[1];	
	}

	ElementType Read_Delete(void){
		ElementType r;


		if (!Is_Empty()){
			int current_p;
			int next_p;
			ElementType temp;
			
			current_p=1;
			r=fp[1];
			Pos--;//降位
			while (1){
				next_p=current_p*2;
				if (next_p>=Pos) break; // Stop while
				
				if (next_p+1<Pos)					
					if (fp[next_p+1]>fp[next_p] ^ Min)
						next_p++;

				if (fp[next_p]>fp[Pos] ^ !Min) break;// Jump out
				
				//swap
				temp=fp[current_p];
				fp[current_p]=fp[next_p];
				fp[next_p]=temp;
				//swap

				current_p=next_p;
			}
			fp[current_p]=fp[Pos];		
		}

		return r;	
	}
};