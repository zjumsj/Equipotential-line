#include <iostream.h>
#include "kruskal.h"
int main(void){
	int k;
	double w_in;
	Matrix<double> M;
	cin>>k;
	M.NewM(k,k);
	
	int i,j;
	char * y;
	for (i=0;i<k;i++)
		for (j=0;j<k;j++){
			cin>>w_in;
			M.Write_In(i+1,j+1,w_in);
		}
//	cout<<Kruskal(M,y)<<endl;
//	cout<<Prim(M,y)<<endl;
	cout<<Rosenstiehl(M,y)<<endl;
	cout<<y<<endl;
	delete [] y;
	cin>>k;
			
	




}