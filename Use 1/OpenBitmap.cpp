#include "stdafx.h"

#include <windows.h>  
#include <stdlib.h>

#include "OpenBitmap.h"


void OpenBitmap(LPCTSTR path_way,HBITMAP & hbitmap,bool Ty){//Ty=TRUE 自动加入当前路径 示例“24.bmp”
	HBITMAP hBitmap;
	if (Ty){
		char st[1000];
		GetCurrentDirectory(1000,st);
		int i=0;
	
		while (1){
			if (st[i]==0) break;
			i++;
		}
		st[i]='\\';
		char * su=&st[i]+1;
		i=0;
		while (1){
			if (path_way[i]==0) break;
			su[i]=path_way[i];
			i++;
		}
		su[i]=0;
		hBitmap=(HBITMAP)::LoadImage(NULL,st,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	}
	else{
		hBitmap=(HBITMAP)::LoadImage(NULL,path_way,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	}	
	hbitmap=hBitmap;
	return ;
}




int randEx(int x){
	LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(seed.QuadPart);//初始化一个以微秒为单位的时间种子
    
	return rand()%x;
}




