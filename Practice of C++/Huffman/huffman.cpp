#include <iostream.h>
#include "huffman.h"



	Heap_H::Heap_H(int size){//true 输出最小
		fp=new Linked_list * [size+1];//空出零位置
		Capacity=size;
		Pos=1;
		
	}

	Heap_H::~Heap_H(){
		delete [] fp;	
	}

	bool Heap_H::Is_Full(void){
		return (Pos>Capacity);	
	}
	bool Heap_H::Is_Empty(void){
		return (Pos==1);
	
	}

	bool Heap_H::Insert(Linked_list * a){
		bool r=false;

		if (Is_Full())
			cout<<"Heap is full!"<<endl;
		else{

			int i;
			int j;
			Linked_list * temp;
			
			i=Pos;
			j=Pos/2;
			fp[Pos++]=a;
			while (1){
				if (i==1)
					break;
				if (!(fp[i]->data>fp[j]->data)){//同时发生换位置
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


	Linked_list * Heap_H::Read_Delete(void){
		Linked_list * r;

	

		if (Is_Empty())
			cout<<"Heap is empty!"<<endl;
		else{
			int current_p;
			int next_p;
			Linked_list * temp;
		
			current_p=1;
			r=fp[1];
			Pos--;//降位
			while (1){
				next_p=current_p*2;
				if (next_p>=Pos) break; // Stop while
			
				if (next_p+1<Pos)					
					if (!(fp[next_p+1]->data > fp[next_p]->data ))
						next_p++;

				if (fp[next_p]->data>fp[Pos]->data) break;// Jump out
				
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


Linked_list * Huffman(ElementType * fp,int num){//首地址指针，元素个数
	Linked_list * header;
	Linked_list * x,* y,* z;

	if (num<1) return (Linked_list *)NULL;
	
	Heap_H heap(num);
	int i;
	int count=num;

	for (i=0;i<num;i++){
		z=new Linked_list;
		z->data=fp[i];
		z->Left=NULL;
		z->Right=NULL;
		heap.Insert(z);
	}
	while(1){
		if (count==1) {
			header=heap.Read_Delete();
			break; //结束
		}
		x=heap.Read_Delete();
		y=heap.Read_Delete();
		z=new Linked_list;
		z->data=x->data+y->data;
		z->Left=x;
		z->Right=y;
		heap.Insert(z);
		count--;
	}
	return header;
}
void Print_leaves(Linked_list * list,int num){
	Linked_list * * array=new Linked_list * [num];
	Linked_list * current;
	int rear;
	int front;
	bool full;
	int i,j;
	int line;

	front=1;
	rear=0;

	current=list;
	array[0]=list;
	full=false;
	i=1;j=0;line=0;
	cout<<"Depth "<<line<<": ";

	while (1){
		current=array[rear++];
		i--;
		
		if (rear==num) rear=0;
		
		if (current->Left==NULL & current->Right==NULL )
			cout<<current<<" "<<current->data<<" ";
		else{
			if(current->Left!=NULL){
				if (full){
					cout<<"Queue is full!"<<endl;
					return;
				}
				array[front++]=current->Left;
				j++;
				if (front==num)
					front=0;
				if (front==rear)
					full=true;
			}
			if(current->Right!=NULL){
				if (full){
					cout<<"Queue is full!"<<endl;
					return;
				}
				array[front++]=current->Right;
				j++;
				if (front==num)
					front=0;
				if (front==rear)
					full=true;
			}
		}

		if (i==0){
			line++;
			cout<<endl;
			i=j;
			j=0;
			if (i==0) break; //jump out
			cout<<"Depth "<<line<<": ";
		}

		
	}



}
void Delete_Linked_list(Linked_list * list){		//删除链表

	if (list->Left!=NULL)
		Delete_Linked_list(list->Left);
	if (list->Right!=NULL)
		Delete_Linked_list(list->Right);
	delete list;		
}