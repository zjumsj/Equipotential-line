#include "stdio.h"
#include "leftist.h"

int main(void){
	data_struct * x,* y,* z;
	int i;
	
	
	x=NULL;
	y=NULL;
	z=NULL;
	while (1){
		scanf("%d",&i);
		if (i<0)
			break;

		y=NewOne(i);
		x=Merge(x,y);	
	
	
	}
	while (1){
		scanf("%d",&i);
		if (i<0)
			break;

		y=NewOne(i);
		z=Merge(z,y);	
	
	
	}
	x=Merge(x,z);
	x=Delete(x);
	Destroy(x);
	
	getchar();
	getchar();
	getchar();
	





}