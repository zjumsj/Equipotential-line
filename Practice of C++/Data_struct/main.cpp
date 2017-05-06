#include "data_struct.h"


int main(void){
	
	Heap<int> Q(11,true);
	int i,data;

	while (1){
		cin>>i;
		if (i==0){
			cin>>data;
			Q.Insert(data);
		}
		else if (i==1){
			cout<<Q.Read_Delete()<<endl;
		
		
		}
		else if (i==2)
			cout<<Q.Read()<<endl;
		else if (i==3){
			cin>>data;
			int j;
			int * array=new int[data];
			
			for (j=0;j<data;j++){
				cin>>array[j];			
			}
			Q.Build_Heap(array,data);//新建heap N 数量级
			delete [] array;
		}
			
	}
	

	



	





}