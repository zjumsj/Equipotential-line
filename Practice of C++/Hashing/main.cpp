#include "Hashing.h"

int main(void){
	Hashing<int> H(20,5);

	int instruction,data,ind;

	while (1){
		cin>>instruction;
		if (instruction==0)
		{
			cin>>ind;
			cin>>data;
			H.Insert(ind,data);
		}
		else if (instruction==1){
			int * i;
			if ((i=H.Read())!=NULL)
				cout<<*i<<endl;
		}
		else if (instruction==2){
			cin>>ind;
			H.Search(ind);
		}
	
	
	}








}