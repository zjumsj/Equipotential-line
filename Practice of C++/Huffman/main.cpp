#include <iostream.h>
#include "huffman.h"


int main(void){
	int all,i;
	Linked_list * a;
	double data[80];
	cin>>all;
	for (i=0;i<all;i++){
		cin>>data[i];
	}
	a=Huffman(data,all);
	Print_leaves(a,8);
	Delete_Linked_list(a);
	cin>>all;

}