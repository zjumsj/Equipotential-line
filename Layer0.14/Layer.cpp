#include "stdafx.h"
#include "Layer.h"
#include "string.h"
#include "math.h"

Layer::~Layer(){
	if (!tzero)
		delete _fall;
	layer_unit * temp;
	temp=_fin;
	if (temp==NULL) return;
	while(1){
		delete temp->_con;
		if (temp->_latter==NULL){
			delete temp;
			break;
		}
		else{
			temp=temp->_latter;	
			delete temp->_former;
		}
	}
}

bool Layer::Load_Pic(char * apath,CBitmap * cbitmap,UINT ut){//cbitmap 必须存在 IMAGE_BITMAP IMAGE_CURSOR IMAGE_ICON
	HBITMAP hBitmap;
	hBitmap=(HBITMAP)::LoadImage(NULL,apath,ut,0,0,LR_LOADFROMFILE);
	if (!hBitmap)
		return false;
	else{
		cbitmap->Attach(hBitmap);
		return true;
	}
}


Layer::Layer()
:zero(true),tzero(true),cursor(-1),_fin(NULL),_fcur(NULL)
{
	//_DC.CreateCompatibleDC(dc);//内建一个匹配DC
	//_DC.CreateDC(TEXT("DISPLAY"),NULL,NULL,NULL);
}

void Layer::Visible(bool real){if (cursor<0) return; _fcur->_visible=real; return;}


bool Layer::LoadBackGround(char * apath,UINT ut){
	
	if(!zero)
		layerbk.DeleteObject();

	HBITMAP hBitmap;
	hBitmap=(HBITMAP)::LoadImage(NULL,apath,ut,0,0,LR_LOADFROMFILE);
	
	if (!hBitmap)
		return false;
	else{

		BITMAP bm;

		layerbk.Attach(hBitmap);
		layerbk.GetBitmap(&bm);
		_width=bm.bmWidth;
		_height=bm.bmHeight;
		//
		 //FP 未初始
		//
		zero=false;
		return true;
	}	
}

/*
void Layer::Match(void){
	_DC.SelectObject(&layerbk);//在BackGroud没有生成之前使用会出错
}
*/

void Layer::CreateBackGround(unsigned int width,unsigned int height,COLORREF color){

	if (width<1 || height<1)
		return;
	if (!zero)
		layerbk.DeleteObject();

	int i;
	_width=width;
	_height=height;
	DWORD * memory=new DWORD[width*height];
	for (i=0;i<width*height;i++)
		memory[i]=color;

	layerbk.CreateBitmap((int)width,(int)height,1,32,memory);
	delete [] memory;
	zero=false;
}

void Layer::Newlayer(char * c){
	layer_unit * newlayer=new layer_unit;
	//新图层永远置顶
	if (_fin) _fin->_former=newlayer;
	newlayer->_former=NULL;
	newlayer->_latter=_fin;
	newlayer->_visible=true;
	_fin=newlayer;
	_fcur=_fin;

	cursor=0;
	strcpy(newlayer->name,c);//复制名字
	newlayer->_con=new PicMat;
}
void Layer::Copylayer(char * c){
	layer_unit * newlayer=new layer_unit;
	layer_unit * formerlayer;
	formerlayer=_fcur;//保存当前layer位置
	//新图层永远置顶
	if (_fin) _fin->_former=newlayer;
	newlayer->_former=NULL;
	newlayer->_latter=_fin;
	newlayer->_visible=true;
	_fin=newlayer;
	_fcur=_fin;

	cursor=0;
	strcpy(newlayer->name,c);//复制名字
	//赋值
	newlayer->_con=new PicMat;
	(*(newlayer->_con))=(*(formerlayer->_con));
}
PicMat * Layer::Current(void){
	return _fcur->_con;
}
//置顶
void Layer::Top(void){
	if (cursor<0) 
		return;
	if (_fin==_fcur)//已经置顶
		return;

	//调整移出位置
	(_fcur->_former)->_latter=_fcur->_latter;
	if (_fcur->_latter!=NULL)
		(_fcur->_latter)->_former=_fcur->_former;
	//调整移出块
	_fcur->_former=NULL;
	_fcur->_latter=_fin;
	//调整移入位置
	_fin->_former=_fcur;
	_fin=_fcur;
	cursor=0;
}
//置底部
void Layer::Bottom(void){
	if (cursor<0)
		return;
	int btt=cursor;
	layer_unit * temp;

	temp=_fcur;
	while (temp->_latter!=NULL){
		btt++;
		temp=temp->_latter;
	}
	if (temp==_fcur)
		return;//已经置底
	
	//调整移出位置前后 可能有BUG
	if(_fcur->_former!=NULL)
		(_fcur->_former)->_latter=_fcur->_latter;
	else
		_fin=_fcur->_latter;//调整首地址指针
	(_fcur->_latter)->_former=_fcur->_former;
	//调整移入位置
	temp->_latter=_fcur;
	//调整移出块
	_fcur->_latter=NULL;
	_fcur->_former=temp;
	
	cursor=btt;
}

bool Layer::Find(char * c){
	if (cursor<0)
		return false;
	int btt;
	layer_unit * temp;
	
	btt=0;
	temp=_fin;
	while (1){
		if (strcmp(temp->name,c)==0)
		{
			_fcur=temp;
			cursor=btt;
			return true;
		}
		btt++;
		if (temp->_latter!=NULL)
			temp=temp->_latter;
		else
			break;
	}
	return false;
}
void Layer::Draw(CDC * pDC,CView * cv){
	if (zero) return;//缺失背景
	_fp=new unsigned char[4*_width*_height];//长 宽 一个像素点4个Byte

	/*伪代码
	把图片信息用矩阵表示出来
	从底层开始
	用透明度算法进行叠加
	将叠加结果CBitmap
	CBitmap被select
	复制到外部CPaitDC
	*/
	
	//读取背景
	BITMAP bm;

	LONG bmWidth;
	LONG bmHeight;
	LONG bmWidthBytes;

	int i,j,k;

	unsigned char * memory;//开辟一个内存空间
	
	unsigned char * fp;
	unsigned char  binary;
	unsigned char flag;
	int a,b;

	layerbk.GetBitmap(&bm);
	
	bmWidth=bm.bmWidth;
	bmHeight=bm.bmHeight;
	bmWidthBytes=bm.bmWidthBytes;

	memory=new unsigned char[bmHeight*bmWidthBytes];//缓存
	layerbk.GetBitmapBits(bmHeight*bmWidthBytes,memory);//读取数据


	

	if(bmWidthBytes/bmWidth>=3){
		for (j=0;j<bmHeight;j++){//CBitmap中图像好像是四通道 16色是单通道的
			fp=memory+j*bmWidthBytes;
			for(i=0;i<bmWidth;i++){
				_fp[j*_width*4+i*4]=fp[i*4];//B
				_fp[j*_width*4+i*4+1]=fp[i*4+1];//G
				_fp[j*_width*4+i*4+2]=fp[i*4+2];//R
				_fp[j*_width*4+i*4+3]=0;//A 设置为不透明？
			}
		}
	}
	else	
	{
		for (j=0;j<bmHeight;j++){//CBitmap中用来处理二值用到了
			fp=memory+j*bmWidthBytes;
			a=0;b=0;
			for(i=0;i<bmWidth;i++){//顺序有待考证
				binary=fp[a];
				flag=0;
				switch(b){//数据存储顺序 高位到低位
				case 0: if (binary & 0x80) flag=1;break;
				case 1: if (binary & 0x40) flag=1;break;
				case 2: if (binary & 0x20) flag=1;break;
				case 3: if (binary & 0x10) flag=1;break;
				case 4: if (binary & 0x08) flag=1;break;
				case 5: if (binary & 0x04) flag=1;break;
				case 6: if (binary & 0x02) flag=1;break;
				case 7: if (binary & 0x01) flag=1;break;				
				}
				_fp[j*_width*4+4*i]=flag*255;
				_fp[j*_width*4+4*i+1]=flag*255;
				_fp[j*_width*4+4*i+2]=flag*255;
				_fp[j*_width*4+4*i+3]=0;//设置为不透明？
				b++;
				if (b==8){
					b=0;
					a++;
				}
			}
		}
	}
	delete [] memory;

	//从底层开始绘制
	PicMat * apicmat;
	CRect acrect;
	int intt;
	int xx,yy;//被绘制图层的偏移
	unsigned int innerwidth;//被绘制图层宽度
	int lp1;
	int lp2;
	double p;//权


	if (cursor>-1){
		int btt=cursor;
		layer_unit * temp=_fcur;
		while (temp->_latter!=NULL){
			btt++;
			temp=temp->_latter;
		}
		//开始绘制
		while (1){
			if (temp->_visible){//可见
				apicmat=temp->_con;
				innerwidth=2*apicmat->_width;

				//Left
				intt=(apicmat->_bias).x-apicmat->_width;
				if (intt>0){
					acrect.left=intt;
					xx=0;
				}
				else{
					acrect.left=0;
					xx=0-intt;
				}

				//Top
				intt=(apicmat->_bias).y-apicmat->_height;
				if (intt>0){
					acrect.top=intt;
					yy=0;
				}
				else{
					acrect.top=0;
					yy=0-intt;
				}
				
				//Right
				intt=(apicmat->_bias).x+apicmat->_width;
				if (intt<_width)
					acrect.right=intt;
				else
					acrect.right=_width;

				//Bottom
				intt=(apicmat->_bias).y+apicmat->_height;
				if (intt<_height)
					acrect.bottom=intt;
				else
					acrect.bottom=_height;

				for(i=xx,a=acrect.left;a<acrect.right;i++,a++){
					for (j=yy,b=acrect.top;b<acrect.bottom;j++,b++){
						p=apicmat->_fp[4*j*innerwidth+4*i+3];
						lp1=4*b*_width+4*a;
						lp2=4*j*innerwidth+4*i;
						for (k=0;k<3;k++,lp1++,lp2++){
							_fp[lp1]=(unsigned char)((_fp[lp1]*p+(255-p)*apicmat->_fp[lp2])/255.0+0.5);
						}
					}
				}			
			}
			if(temp->_former==NULL)//跳出循环
				break;
			else
				temp=temp->_former;
		}
	}
	//开始匹配
	CBitmap * _all=new CBitmap;
	CRect acr;

	_all->CreateBitmap(_width,_height,1,32,NULL);
	_all->SetBitmapBits(4*_width*_height,_fp);
	_DC.CreateCompatibleDC(pDC);
	_DC.SelectObject(_all);
    
	
	cv->GetClientRect(&acr);
	pDC->StretchBlt(0,0,acr.Width(),acr.Height(),&_DC,0,0,_width,_height,SRCCOPY);
	_DC.DeleteDC();

	
	if (!tzero)
		delete _fall;
	
	_fall=_all;
	tzero=false;
	delete [] _fp;
}
void Layer::Draw(CPaintDC * dc,CDialog * dia){
	if (zero) return;//缺失背景
	_fp=new unsigned char[4*_width*_height];//长 宽 一个像素点4个Byte

	/*伪代码
	把图片信息用矩阵表示出来
	从底层开始
	用透明度算法进行叠加
	将叠加结果CBitmap
	CBitmap被select
	复制到外部CPaitDC
	*/
	
	//读取背景
	BITMAP bm;

	LONG bmWidth;
	LONG bmHeight;
	LONG bmWidthBytes;

	int i,j,k;

	unsigned char * memory;//开辟一个内存空间
	
	unsigned char * fp;
	unsigned char  binary;
	unsigned char flag;
	int a,b;

	layerbk.GetBitmap(&bm);
	
	bmWidth=bm.bmWidth;
	bmHeight=bm.bmHeight;
	bmWidthBytes=bm.bmWidthBytes;

	memory=new unsigned char[bmHeight*bmWidthBytes];//缓存
	layerbk.GetBitmapBits(bmHeight*bmWidthBytes,memory);//读取数据


	

	if(bmWidthBytes/bmWidth>=3){
		for (j=0;j<bmHeight;j++){//CBitmap中图像好像是四通道 16色是单通道的
			fp=memory+j*bmWidthBytes;
			for(i=0;i<bmWidth;i++){
				_fp[j*_width*4+i*4]=fp[i*4];//B
				_fp[j*_width*4+i*4+1]=fp[i*4+1];//G
				_fp[j*_width*4+i*4+2]=fp[i*4+2];//R
				_fp[j*_width*4+i*4+3]=0;//A 设置为不透明？
			}
		}
	}
	else	
	{
		for (j=0;j<bmHeight;j++){//CBitmap中用来处理二值用到了
			fp=memory+j*bmWidthBytes;
			a=0;b=0;
			for(i=0;i<bmWidth;i++){//顺序有待考证
				binary=fp[a];
				flag=0;
				switch(b){//数据存储顺序 高位到低位
				case 0: if (binary & 0x80) flag=1;break;
				case 1: if (binary & 0x40) flag=1;break;
				case 2: if (binary & 0x20) flag=1;break;
				case 3: if (binary & 0x10) flag=1;break;
				case 4: if (binary & 0x08) flag=1;break;
				case 5: if (binary & 0x04) flag=1;break;
				case 6: if (binary & 0x02) flag=1;break;
				case 7: if (binary & 0x01) flag=1;break;				
				}
				_fp[j*_width*4+4*i]=flag*255;
				_fp[j*_width*4+4*i+1]=flag*255;
				_fp[j*_width*4+4*i+2]=flag*255;
				_fp[j*_width*4+4*i+3]=0;//设置为不透明？
				b++;
				if (b==8){
					b=0;
					a++;
				}
			}
		}
	}
	delete [] memory;

	//从底层开始绘制
	PicMat * apicmat;
	CRect acrect;
	int intt;
	int xx,yy;//被绘制图层的偏移
	unsigned int innerwidth;//被绘制图层宽度
	int lp1;
	int lp2;
	double p;//权


	if (cursor>-1){
		int btt=cursor;
		layer_unit * temp=_fcur;
		while (temp->_latter!=NULL){
			btt++;
			temp=temp->_latter;
		}
		//开始绘制
		while (1){
			if (temp->_visible){//可见
				apicmat=temp->_con;
				innerwidth=2*apicmat->_width;

				//Left
				intt=(apicmat->_bias).x-apicmat->_width;
				if (intt>0){
					acrect.left=intt;
					xx=0;
				}
				else{
					acrect.left=0;
					xx=0-intt;
				}

				//Top
				intt=(apicmat->_bias).y-apicmat->_height;
				if (intt>0){
					acrect.top=intt;
					yy=0;
				}
				else{
					acrect.top=0;
					yy=0-intt;
				}
				
				//Right
				intt=(apicmat->_bias).x+apicmat->_width;
				if (intt<_width)
					acrect.right=intt;
				else
					acrect.right=_width;

				//Bottom
				intt=(apicmat->_bias).y+apicmat->_height;
				if (intt<_height)
					acrect.bottom=intt;
				else
					acrect.bottom=_height;

				for(i=xx,a=acrect.left;a<acrect.right;i++,a++){
					for (j=yy,b=acrect.top;b<acrect.bottom;j++,b++){
						p=apicmat->_fp[4*j*innerwidth+4*i+3];
						lp1=4*b*_width+4*a;
						lp2=4*j*innerwidth+4*i;
						for (k=0;k<3;k++,lp1++,lp2++){
							_fp[lp1]=(unsigned char)((_fp[lp1]*p+(255-p)*apicmat->_fp[lp2])/255.0+0.5);
						}
					}
				}			
			}
			if(temp->_former==NULL)//跳出循环
				break;
			else
				temp=temp->_former;
		}
	}
	//开始匹配
	CBitmap * _all=new CBitmap;
	CRect acr;

	_all->CreateBitmap(_width,_height,1,32,NULL);
	_all->SetBitmapBits(4*_width*_height,_fp);
	_DC.CreateCompatibleDC(dc);
	_DC.SelectObject(_all);
    
	dia->GetWindowRect(&acr);
	dc->StretchBlt(0,0,acr.Width(),acr.Height(),&_DC,0,0,_width,_height,SRCCOPY);
	_DC.DeleteDC();

	
	if (!tzero)
		delete _fall;
	
	_fall=_all;
	tzero=false;
	delete [] _fp;
}
//--------------------PicMat---------------------------
CPoint PicMat::Bias(void){return _bias;}
unsigned int PicMat::Width(void){return _width;}
unsigned int PicMat::Height(void){return _height;}

PicMat::PicMat(CPoint cp,unsigned int width,unsigned int height){
	if (width<1 || height<1){
		_bias.x=_bias.y=0;
		_width=0;
		_height=0;
		_fp=NULL;
		zero=true;
	}
	else{
		_bias=cp;
		_width=width;
		_height=height;
		_fp=new unsigned char[2*width*2*height*4];
		zero=false;
	}
}

PicMat::PicMat(){
	_bias.x=_bias.y=0;
	_width=0;
	_height=0;
	_fp=NULL;
	zero=true;
}
PicMat::~PicMat(){
	if (!zero){
		delete [] _fp;	
	}
}
void PicMat::operator =(const PicMat & one){
	if (!zero)
		delete [] _fp;
	_bias=one._bias;
	_width=one._width;
	_height=one._height;
	zero=one.zero;
	if(!zero){
		_fp=new unsigned char[2*_width*2*_height*4];
		memcpy(_fp,one._fp,2*_width*2*_height*4);
	}
}
bool PicMat::LoadPic(CPoint cp,char * apath,UINT ut){
	int i,j;
	
	CBitmap cbitmap;
	HBITMAP hBitmap;
	BITMAP bitmap;

	LONG bmWidth;
	LONG bmHeight;
	LONG bmWidthBytes;

	unsigned char symbol;
	unsigned char * memory;//开辟一个内存空间
	
	hBitmap=(HBITMAP)::LoadImage(NULL,apath,ut,0,0,LR_LOADFROMFILE);
	if (!hBitmap)
		return false;
	cbitmap.Attach(hBitmap);
	
	_bias=cp;

	
	cbitmap.GetBitmap(&bitmap);//获取Bitmap信息
	bmWidth=bitmap.bmWidth;
	bmHeight=bitmap.bmHeight;
	bmWidthBytes=bitmap.bmWidthBytes;
	
	symbol=0;
	_width=(bmWidth+1)/2;
	symbol=symbol+0x10*(bmWidth%2);//高位表示行
	_height=(bmHeight+1)/2;
	symbol=symbol+(bmHeight%2);//低位表示列

	if (!zero)
		delete [] _fp;
	_fp=new unsigned char[2*_width*2*_height*4];//新建内存

	memory=new unsigned char[bmHeight*bmWidthBytes];//缓存
	cbitmap.GetBitmapBits(bmHeight*bmWidthBytes,memory);//读取数据
	
	//数据拷贝
	unsigned char * fp;
	unsigned char  binary;
	unsigned char flag;
	int a,b;

	if(bmWidthBytes/bmWidth>=3){
		for (j=0;j<bmHeight;j++){//CBitmap中图像好像是四通道 16色是单通道的
			fp=memory+j*bmWidthBytes;
			for(i=0;i<bmWidth;i++){
				_fp[j*2*_width*4+i*4]=fp[i*4];//B
				_fp[j*2*_width*4+i*4+1]=fp[i*4+1];//G
				_fp[j*2*_width*4+i*4+2]=fp[i*4+2];//R
				_fp[j*2*_width*4+i*4+3]=0;//A 设置为不透明？
			}
			if (symbol & 0x10)
				_fp[(j+1)*2*_width*4-1]=255;//设置为透明？
		}
		if (symbol & 0x01)
			for (i=0;i<_width*2;i++)
				_fp[(2*_height-1)*2*_width*4+4*i+3]=255;//A 设置为透明？
	}
	else	
	{
		for (j=0;j<bmHeight;j++){//CBitmap中用来处理二值用到了
			fp=memory+j*bmWidthBytes;
			a=0;b=0;
			for(i=0;i<bmWidth;i++){//顺序有待考证
				binary=fp[a];
				flag=0;
				switch(b){//存储顺序 高位到低位
				case 0: if (binary & 0x80) flag=1;break;
				case 1: if (binary & 0x40) flag=1;break;
				case 2: if (binary & 0x20) flag=1;break;
				case 3: if (binary & 0x10) flag=1;break;
				case 4: if (binary & 0x08) flag=1;break;
				case 5: if (binary & 0x04) flag=1;break;
				case 6: if (binary & 0x02) flag=1;break;
				case 7: if (binary & 0x01) flag=1;break;				
				}
				_fp[j*2*_width*4+4*i]=flag*255;
				_fp[j*2*_width*4+4*i+1]=flag*255;
				_fp[j*2*_width*4+4*i+2]=flag*255;
				_fp[j*2*_width*4+4*i+3]=0;//设置为不透明？
				b++;
				if (b==8){
					b=0;
					a++;
				}
			}
		    if (symbol & 0x10)
			   _fp[(j+1)*2*_width*4-1]=255;//设置为透明？
		}
		if (symbol & 0x01)
			for (i=0;i<_width*2;i++)
				_fp[(2*_height-1)*2*_width*4+4*i+3]=255;//A 设置为透明？
	}
	delete [] memory;
	zero=false;
	return true;
}

void PicMat::NewMat(CPoint cp,unsigned int width,unsigned int height ,COLORREF color){
	if (width<1 || height<1){
		_bias.x=_bias.y=0;
		_width=0;
		_height=0;
		_fp=NULL;
		zero=true;
	}
	else{
		_bias=cp;
		_width=width;
		_height=height;
		_fp=new unsigned char[2*_width*2*_height*4];
		int i;

		DWORD * k=(DWORD * ) _fp;
		for (i=0;i<4*_width*_height;i++)
			k[i]=color;		
		zero=false;
	}
}
void PicMat::Moveto(CPoint cp){
	if (!zero){
		_bias=cp;
	}
}
void PicMat::Move(CPoint cp){
	if (!zero){
		_bias=_bias+cp;
	}
}

void PicMat::Transparent(COLORREF color){
	int i;
	DWORD * fp=(DWORD *)_fp;

	if (!zero){
		color=color & 0x00FFFFFF;//不比较A
		for (i=0;i<_width*2*_height*2;i++)
			if ((fp[i] & 0x00FFFFFF)-color==0)
				_fp[i*4+3]=255;//设置为透明
	}
}

void PicMat::SetTransparent(unsigned char alpha,bool force){
	int i;
	if (force){
		for (i=0;i<4*_width*_height;i++){
			_fp[4*i+3]=alpha;
		}
	}
	else{
		for (i=0;i<4*_width*_height;i++){
			if(_fp[4*i+3]<255)
				_fp[4*i+3]=alpha;
		}	
	}
}
//--------------RGB-HSI-------------------------
void PicMat::RGB2HSI(unsigned char r,unsigned char g,unsigned char b,float &h,float &s,float &i){
	float theta;
	unsigned char mid;
	float PI=3.14159265359;
	//H 除数为零
	theta=sqrt((r-g)*(r-g)+(r-b)*(g-b));
	if (theta){
		theta=0.5*(2*r-g-b)/theta;
		theta=acos(theta);
	}
	if (g>=b){
		h=theta;
	}
	else{
		h=2*PI-theta;
	}
	//S
	if (r<g)
		mid=r;
	else
		mid=g;
	//
	if (mid>b)
		mid=b;
	s=1-mid*3.0/(r+g+b);
	//I
	i=(r+g+b)/(3.0*255);
}
void PicMat::HSI2RGB(float h,float s,float i,unsigned char &r,unsigned char &g,unsigned char &b){
	float PI=3.14159265359;
	float fr,fg,fb;
	bool c=false;
	//int n;

	//-----------归一化--------------
/*------------归一化--------------
	//整理I
	if(i<0)
		i=0;
	else if(i>1)
		i=1;
	//整理S
	if(s<0)
		s=0;
	else if (s>1)
		s=1;
	//整理H
	if(h<0){
		h=-h;
		c=true;
	}
	n=ceil((h/(2*PI)));
	h=h-n*(2*PI);
	if(c)
		h=2*PI-h;
*/
	//--------------------------------
	if ( h<PI*2/3 ){
		/* RG 扇区
		B=I(1-S)
		R=I(1+Scos(H)/cos(60-H))
		G=3I-(R+B) 
		*/
		fb=i*(1-s);
		fr=i*(1+s*cos(h)/cos(PI/3-h));
		fg=3*i-fb-fr;
	}
	else if(h<PI*4/3){
		/* GB 扇区
		R=I(1-S)
		G=I(1+Scos(H)/cos(60-H))
		B=3I-(R+G)
		*/
		h=h-2*PI/3;
		fr=i*(1-s);
		fg=i*(1+s*cos(h)/cos(PI/3-h));
		fb=3*i-fr-fg;
	}
	else{
		/* BR 扇区
		G=I(1-S)
		B=I(1+Scos(H)/cos(60-H))
		R=3I-(G+B)
		*/
		h=h-4*PI/3;
		fg=i*(1-s);
		fb=i*(1+s*cos(h)/cos(PI/3-h));
		fr=3*i-fg-fb;
	}
	//Debug
	if (fg>1)fg=1;
	if (fb>1) fb=1;
	if (fr>1) fr=1;
	//
	b=(unsigned char)(255*fb+0.499);
	r=(unsigned char)(255*fr+0.499);
	g=(unsigned char)(255*fg+0.499);
}
//--------------PicMat 功能支持-----------------
void PicMat::Inverse(void){
	int i;
	int j;
	for (i=0;i<4*_width*_height;i++){
		j=4*i;
		_fp[j]=255-_fp[j++];
		_fp[j]=255-_fp[j++];
		_fp[j]=255-_fp[j++];	
	}
	return;
}

void PicMat::Brightness(float rate){
	int i;
	int j;
	int te;
	for (i=0;i<4*_width*_height;i++){
		j=4*i;
		te=(int)(_fp[j]*rate+0.5);
		_fp[j++]=te>255 ? 255 : te;
		te=(int)(_fp[j]*rate+0.5);
		_fp[j++]=te>255 ? 255 : te;
		te=(int)(_fp[j]*rate+0.5);
		_fp[j++]=te>255 ? 255 : te;
	}
}
void PicMat::Saturation(float rate){
	int k;
	unsigned char * j;
	float h,s,i;
	for (k=0;k<4*_width*_height;k++){
		j=_fp+4*k;
		RGB2HSI(j[2],j[1],j[0],h,s,i);
		s=s*rate;
		if(s>1)//溢出处理
			s=1;
		HSI2RGB(h,s,i,j[2],j[1],j[0]);
	}
}
void PicMat::Phase(float alpha){
	int k;	int n;
	bool c; float PI=3.14159265359;
	unsigned char * j;
	float h,s,i;
	for (k=0;k<4*_width*_height;k++){
		j=_fp+4*k;
		RGB2HSI(j[2],j[1],j[0],h,s,i);
		h=h+alpha;
		//h 整合
		c=false;
		if(h<0){
			h=-h;
			c=true;
		}
		n=floor((h/(2*PI)));
		h=h-n*(2*PI);
		if(c)
			h=2*PI-h;
		//
		HSI2RGB(h,s,i,j[2],j[1],j[0]);
	}
}
//寻址
unsigned int PicMat::Index(int x,int y,int i){
	unsigned int index;
	index=(2*_width)*(_height-y)+(x+_width);
	index=4*index+i;
	return index;
}

void PicMat::Rotate(float alpha,bool inter){
	if(zero) return;//防止出错
	if(!inter){
		Rotate_U(alpha);
		return;
	}//执行非插值变化
//---------------------------------
/*
	100 50
	从50画到149号点
*/
	double x1,x2;
	double y1,y2;
	unsigned int new_width;
	unsigned int new_height;
	int _width,_height;
	int x,y;
	float xx,yy;//反坐标变换浮点
	int nx,ny;//向负无穷取整
	unsigned int index_a;//坐标对应点的序号
	bool out;
	unsigned char * mem;
	float u,v;//插值系数
	int i;
	float buff[4];
	_width=this->_width;
	_height=this->_height;

	//边缘模糊化
	for (i=0;i<2*_width;i++)
		_fp[i*4+3]=255;
	for (i=0;i<2*_width;i++)
		_fp[(_width*2*(2*_height-1)+i)*4+3]=255;
	for (i=0;i<2*_height;i++)
		_fp[(_width*2*i)*4+3]=255;
	for (i=0;i<2*_height;i++)
		_fp[(_width*2*(i+1)-1)*4+3]=255;
	//x'=x*cos-y*sin
	//y'=x*sin+y*cos
	x1=_width*cos(alpha)-_height*sin(alpha);
	y1=_width*sin(alpha)+_height*cos(alpha);
	x2=_width*cos(alpha)+_height*sin(alpha);
	y2=_width*sin(alpha)-_height*cos(alpha);
	//
	x1=fabs(x1);x2=fabs(x2);
	y1=fabs(y1);y2=fabs(y2);
	if (x1<x2)
		new_width=ceil(x2);
	else
		new_width=ceil(x1);
	//
	if (y1<y2)
		new_height=ceil(y2);
	else
		new_height=ceil(y1);
	//
	index_a=0;

	//开空间
	mem=new unsigned char [2*new_width*2*new_height*4];
	
	for (y=new_height;y>-(int)new_height;y--){
		for (x=-new_width;x<(int)new_width;x++){
			xx=x*cos(alpha)+y*sin(alpha);
			yy=-x*sin(alpha)+y*cos(alpha);
			nx=floor(xx);
			ny=floor(yy);
			//Initialize
			out=false;
			u=xx-nx;v=yy-ny;
			buff[0]=buff[1]=buff[2]=buff[3]=0;
			//
			if (nx<-_width-1){//外侧
				out=true;
			}
			else if(nx<-_width){//左侧
				if(ny<-_height){//外侧
					out=true;
				}
				else if(ny<-_height+1){//底部
					for (i=0;i<4;i++){
						buff[i]+=_fp[Index(-_width,-_height+1,i)];//右上
					}
				}
				else if(ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-v)*_fp[Index(-_width,ny,i)];//右下
						buff[i]+=v*_fp[Index(-_width,ny+1,i)];//右上
					}
				}
				else if(ny<_height+1){//上部
					for(i=0;i<4;i++){
						buff[i]+=_fp[Index(-_width,_height,i)];//右下
					}
				}
				else{//外侧
					out=true;
				}			
			}
			else if(nx<_width-1){//中间
				if(ny<-_height){//外侧
					out=true;
				}
				else if (ny<-_height+1){//底部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*_fp[Index(nx,-_height+1,i)];//左上
						buff[i]+=u*_fp[Index(nx+1,-_height+1,i)];//右上
					}
				}
				else if (ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*(1-v)*_fp[Index(nx,ny,i)];//左下
						buff[i]+=u*(1-v)*_fp[Index(nx+1,ny,i)];//右下
						buff[i]+=(1-u)*v*_fp[Index(nx,ny+1,i)];//左上
						buff[i]+=u*v*_fp[Index(nx+1,ny+1,i)];//右上
					}
				}
				else if (ny<_height+1){//上部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*_fp[Index(nx,_height,i)];//左下
						buff[i]+=u*_fp[Index(nx+1,_height,i)];//右下
					}
				}
				else{
					out=true;
				}
			}
			else if(nx<_width){//右侧
				if(ny<-_height){//外侧
					out=true;
				}
				else if (ny<-_height+1){//底部
					for(i=0;i<4;i++){
						buff[i]+=_fp[Index(_width-1,-_height+1,i)];//左上
					}
				}
				else if (ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-v)*_fp[Index(_width-1,ny,i)];//左下
						buff[i]+=v*_fp[Index(_width-1,ny+1,i)];//左上
					}
				}
				else if (ny<_height+1){//上部
					for (i=0;i<4;i++){
						buff[i]+=_fp[Index(_width-1,_height,i)];//左下
					}
				}
				else{
					out=true;
				}			
			}
			else{//外侧
				out=true;
			}
			//--------------------
			if(out){//外侧
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			else{
				for (i=0;i<4;i++)//赋值
					mem[index_a+i]=(unsigned char)(buff[i]+0.5);			
			}
				
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=new_width;
	this->_height=new_height;
}
//-------------------------不使用双线性插值法------------------------
void PicMat::Rotate_U(float alpha){
	double x1,x2;
	double y1,y2;
	unsigned int new_width;
	unsigned int new_height;
	int _width,_height;
	int x,y;
	float xx,yy;//浮点数
	int nx,ny;//最近整数点
	unsigned int index_a;//坐标对应点的序号
	bool out;
	unsigned char * mem;
	int i;

	_width=this->_width;
	_height=this->_height;
	//x'=x*cos-y*sin
	//y'=x*sin+y*cos
	x1=_width*cos(alpha)-_height*sin(alpha);
	y1=_width*sin(alpha)+_height*cos(alpha);
	x2=_width*cos(alpha)+_height*sin(alpha);
	y2=_width*sin(alpha)-_height*cos(alpha);
	//
	x1=fabs(x1);x2=fabs(x2);
	y1=fabs(y1);y2=fabs(y2);
	if (x1<x2)
		new_width=ceil(x2);
	else
		new_width=ceil(x1);
	//
	if (y1<y2)
		new_height=ceil(y2);
	else
		new_height=ceil(y1);
	//
	index_a=0;

	//开空间
	mem=new unsigned char [2*new_width*2*new_height*4];
	
	for (y=new_height;y>-(int)new_height;y--){
		for (x=-new_width;x<(int)new_width;x++){
			xx=x*cos(alpha)+y*sin(alpha);
			yy=-x*sin(alpha)+y*cos(alpha);
			nx=floor(xx+0.5);
			ny=floor(yy+0.5);
			out=true;
			if(nx>=-_width && nx<_width ){
				if(ny>-_height && ny<=_height){
					for (i=0;i<4;i++)//简单赋值
						mem[index_a+i]=_fp[Index(nx,ny,i)];
					out=false;
				}			
			}
			//赋值
			if (out){
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			index_a+=4;
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=new_width;
	this->_height=new_height;
}
void PicMat::Stretch(unsigned int x,unsigned int y,bool inter){
	if(zero) return;//防止出错
	if (!inter){
		Stretch_U(x,y);
		return;
	}

//  100 50
//  从50画到149号点

	float kx,ky;
	unsigned char * mem;
	float xx,yy;//坐标变换后的浮点坐标
	int nx,ny;//取整之后结果
	int ix,iy;//移动的变量
	unsigned int index_a;//坐标对应点
	float u,v;int i;
	int _width,_height;
	bool out;
	float buff[4];

	_width=this->_width;
	_height=this->_height;
	//新坐标x,y
	kx=(float)x/_width;
	ky=(float)y/_height;
	index_a=0;
	mem=new unsigned char[x*y*4*4];
	
	for (iy=y;iy>-(int)y;iy--){
		for (ix=-x;ix<(int)x;ix++){
			xx=ix/kx;
			yy=iy/ky;
			nx=floor(xx);
			ny=floor(yy);
			//Initialize
			out=false;
			u=xx-nx;v=yy-ny;
			buff[0]=buff[1]=buff[2]=buff[3]=0;
			//
			if (nx<-_width-1){//外侧
				out=true;
			}
			else if(nx<-_width){//左侧
				if(ny<-_height){//外侧
					out=true;
				}
				else if(ny<-_height+1){//底部
					for (i=0;i<4;i++){
						buff[i]+=_fp[Index(-_width,-_height+1,i)];//右上
					}
				}
				else if(ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-v)*_fp[Index(-_width,ny,i)];//右下
						buff[i]+=v*_fp[Index(-_width,ny+1,i)];//右上
					}
				}
				else if(ny<_height+1){//上部
					for(i=0;i<4;i++){
						buff[i]+=_fp[Index(-_width,_height,i)];//右下
					}
				}
				else{//外侧
					out=true;
				}			
			}
			else if(nx<_width-1){//中间
				if(ny<-_height){//外侧
					out=true;
				}
				else if (ny<-_height+1){//底部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*_fp[Index(nx,-_height+1,i)];//左上
						buff[i]+=u*_fp[Index(nx+1,-_height+1,i)];//右上
					}
				}
				else if (ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*(1-v)*_fp[Index(nx,ny,i)];//左下
						buff[i]+=u*(1-v)*_fp[Index(nx+1,ny,i)];//右下
						buff[i]+=(1-u)*v*_fp[Index(nx,ny+1,i)];//左上
						buff[i]+=u*v*_fp[Index(nx+1,ny+1,i)];//右上
					}
				}
				else if (ny<_height+1){//上部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*_fp[Index(nx,_height,i)];//左下
						buff[i]+=u*_fp[Index(nx+1,_height,i)];//右下
					}
				}
				else{
					out=true;
				}
			}
			else if(nx<_width){//右侧
				if(ny<-_height){//外侧
					out=true;
				}
				else if (ny<-_height+1){//底部
					for(i=0;i<4;i++){
						buff[i]+=_fp[Index(_width-1,-_height+1,i)];//左上
					}
				}
				else if (ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-v)*_fp[Index(_width-1,ny,i)];//左下
						buff[i]+=v*_fp[Index(_width-1,ny+1,i)];//左上
					}
				}
				else if (ny<_height+1){//上部
					for (i=0;i<4;i++){
						buff[i]+=_fp[Index(_width-1,_height,i)];//左下
					}
				}
				else{
					out=true;
				}			
			}
			else{//外侧
				out=true;
			}
			//--------------------
			if(out){//外侧
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			else{
				for (i=0;i<4;i++)//赋值
					mem[index_a+i]=(unsigned char)(buff[i]+0.5);			
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=x;
	this->_height=y;
}
//---------------不使用双线性变换--------------------------
void PicMat::Stretch_U(unsigned int x,unsigned int y){
	float kx,ky;
	unsigned char * mem;
	float xx,yy;//坐标变换后的浮点坐标
	int nx,ny;//取整之后结果
	int ix,iy;//移动的变量
	unsigned int index_a;//坐标对应点
	int i;
	int _width,_height;
	bool out;

	_width=this->_width;
	_height=this->_height;
	//新坐标x,y
	kx=(float)x/_width;
	ky=(float)y/_height;
	index_a=0;
	mem=new unsigned char[x*y*4*4];
	
	for (iy=y;iy>-(int)y;iy--){
		for (ix=-x;ix<(int)x;ix++){
			xx=ix/kx;
			yy=iy/ky;
			nx=floor(xx+0.5);
			ny=floor(yy+0.5);
			//Initialize
			out=false;
			//
			if (nx>=-_width && nx<(int)_width){
				if(ny<=_height && ny>-(int)_height){
					for (i=0;i<4;i++)
						mem[index_a+i]=_fp[Index(nx,ny,i)];
					out=true;
				}
			}
			//--------------------
			if(!out){//外侧
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=x;
	this->_height=y;
}
void PicMat::Stretch(double ratex,double ratey,bool inter){
	unsigned int inx,iny;
	inx=floor(ratex*_width+0.5);
	iny=floor(ratey*_height+0.5);
	Stretch(inx,iny,inter);
	return;
}
void PicMat::Mirror(bool x,bool y){
	unsigned char * stack;
	unsigned char * fp;
	int index;
	int indexy;
	int i;
	int j;
	//x轴镜面反射
	if(x){
		stack=new unsigned char [4*2*_height];
		for(j=0;j<2*_width;j++){//刷列
			fp=stack;
			indexy=j*4;
			//入栈
			for (index=0;index<2*_height;index++){//栈的深度
				for(i=0;i<4;i++){
					fp[i]=_fp[indexy+i];
				}
				fp+=4;
				indexy+=4*(2*_width);
			}
			//出栈
			indexy=j*4;
			fp-=4;
			for (index=0;index<2*_height;index++){//栈的深度
				for(i=0;i<4;i++){
					_fp[indexy+i]=fp[i];
				}
				fp-=4;
				indexy+=4*(2*_width);
			}
		}
		delete [] stack;
	}
	if (y){
		stack=new unsigned char [4*2*_width];
		for (j=0;j<2*_height;j++){//刷行
			fp=stack;
			indexy=(2*_width)*j*4;
			//入栈
			for (index=0;index<2*_width;index++){//栈的深度
				for (i=0;i<4;i++){
					fp[i]=_fp[indexy+i];
				}
				fp+=4;
				indexy+=4;
			}
			indexy=(2*_width)*j*4;
			fp-=4;
			for (index=0;index<2*_width;index++){//栈的深度
				for(i=0;i<4;i++){
					_fp[indexy+i]=fp[i];
				}
				fp-=4;
				indexy+=4;
			}
		}
		delete [] stack;
	}
}

void PicMat::Cut(CPoint center,unsigned int width,unsigned int height){
	int cx,cy;
	unsigned char * mem;
	int ix,iy;//刷行、刷列
	int nx,ny;//取整之后结果
	unsigned int index_a;//坐标对应点
	int i;
	int _width,_height;
	bool out;

	_width=this->_width;
	_height=this->_height;
	//新坐标x,y
	cx=center.x;
	cy=center.y;
	index_a=0;
	mem=new unsigned char[width*height*4*4];
	
	for (iy=height;iy>-(int)height;iy--){
		for (ix=-width;ix<(int)width;ix++){
			nx=ix+cx;
			ny=iy+cy;
			//Initialize
			out=false;
			//
			if (nx>=-_width && nx<(int)_width){
				if(ny<=_height && ny>-(int)_height){
					for (i=0;i<4;i++)
						mem[index_a+i]=_fp[Index(nx,ny,i)];
					out=true;
				}
			}
			//--------------------
			if(!out){//外侧
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=width;
	this->_height=height;
}
void PicMat::Affine(CPoint right_top,CPoint right_bottom,bool inter){
	if(zero) return;//防止出错


//  100 50
//  从50画到149号点

	float kx,ky;//x 向变换因子
	float jx,jy;//y 向变换因子
	unsigned char * mem;
	unsigned int new_width,new_height;
	float xx,yy;//坐标变换后的浮点坐标
	int nx,ny;//取整之后结果
	int ix,iy;//移动的变量
	unsigned int index_a;//坐标对应点
	float u,v;int i;
	int _width,_height;
	bool out;
	float buff[4];float Det;
	int x1,x2,y1,y2;
	_width=this->_width;
	_height=this->_height;
	//获得画布大小
	x1=abs(right_top.x);x2=abs(right_bottom.x);
	y1=abs(right_top.y);y2=abs(right_bottom.y);
	if (x1<x2)
		new_width=x2;
	else
		new_width=x1;
	//
	if (y1<y2)
		new_height=y2;
	else
		new_height=y1;
	//
	//获得x,y
	jx=(float)(right_top.x-right_bottom.x)/(2*_height);
	jy=(float)(right_top.y-right_bottom.y)/(2*_height);
	kx=(float)(right_top.x+right_bottom.x)/(2*_width);
	ky=(float)(right_top.y+right_bottom.y)/(2*_width);
	Det=jx*ky-jy*kx;
	mem=new unsigned char[new_width*new_height*4*4];

	//------------------分母为零的处理方法-------------
	if(Det==0){//分母为零的处理方法
		for(i=0;i<4*new_width*new_height;i++){
			mem[4*i]=255;//白色透明
			mem[4*i+1]=255;
			mem[4*i+2]=255;
			mem[4*i+3]=255;
		}
		delete [] _fp;
		_fp=mem;
		this->_width=new_width;
		this->_height=new_height;
		return;
	}
	//---------------------end------------------------
	//非线性插值 不推荐的方法
	if (!inter){
		Affine_U(kx,ky,jx,jy,new_width,new_height,mem);
		return;
	}
	//Next
	index_a=0;
	//边缘模糊化
	for (i=0;i<2*_width;i++)
		_fp[i*4+3]=255;
	for (i=0;i<2*_width;i++)
		_fp[(_width*2*(2*_height-1)+i)*4+3]=255;
	for (i=0;i<2*_height;i++)
		_fp[(_width*2*i)*4+3]=255;
	for (i=0;i<2*_height;i++)
		_fp[(_width*2*(i+1)-1)*4+3]=255;
	
	for (iy=new_height;iy>-(int)new_height;iy--){
		for (ix=-new_width;ix<(int)new_width;ix++){
			//反变换
			xx=(-jy*ix+jx*iy)/Det;
			yy=(+ky*ix-kx*iy)/Det;
			//整数化
			nx=floor(xx);
			ny=floor(yy);
			//Initialize
			out=false;
			u=xx-nx;v=yy-ny;
			buff[0]=buff[1]=buff[2]=buff[3]=0;
			//
			if (nx<-_width-1){//外侧
				out=true;
			}
			else if(nx<-_width){//左侧
				if(ny<-_height){//外侧
					out=true;
				}
				else if(ny<-_height+1){//底部
					for (i=0;i<4;i++){
						buff[i]+=_fp[Index(-_width,-_height+1,i)];//右上
					}
				}
				else if(ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-v)*_fp[Index(-_width,ny,i)];//右下
						buff[i]+=v*_fp[Index(-_width,ny+1,i)];//右上
					}
				}
				else if(ny<_height+1){//上部
					for(i=0;i<4;i++){
						buff[i]+=_fp[Index(-_width,_height,i)];//右下
					}
				}
				else{//外侧
					out=true;
				}			
			}
			else if(nx<_width-1){//中间
				if(ny<-_height){//外侧
					out=true;
				}
				else if (ny<-_height+1){//底部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*_fp[Index(nx,-_height+1,i)];//左上
						buff[i]+=u*_fp[Index(nx+1,-_height+1,i)];//右上
					}
				}
				else if (ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*(1-v)*_fp[Index(nx,ny,i)];//左下
						buff[i]+=u*(1-v)*_fp[Index(nx+1,ny,i)];//右下
						buff[i]+=(1-u)*v*_fp[Index(nx,ny+1,i)];//左上
						buff[i]+=u*v*_fp[Index(nx+1,ny+1,i)];//右上
					}
				}
				else if (ny<_height+1){//上部
					for (i=0;i<4;i++){
						buff[i]+=(1-u)*_fp[Index(nx,_height,i)];//左下
						buff[i]+=u*_fp[Index(nx+1,_height,i)];//右下
					}
				}
				else{
					out=true;
				}
			}
			else if(nx<_width){//右侧
				if(ny<-_height){//外侧
					out=true;
				}
				else if (ny<-_height+1){//底部
					for(i=0;i<4;i++){
						buff[i]+=_fp[Index(_width-1,-_height+1,i)];//左上
					}
				}
				else if (ny<_height){//中部
					for (i=0;i<4;i++){
						buff[i]+=(1-v)*_fp[Index(_width-1,ny,i)];//左下
						buff[i]+=v*_fp[Index(_width-1,ny+1,i)];//左上
					}
				}
				else if (ny<_height+1){//上部
					for (i=0;i<4;i++){
						buff[i]+=_fp[Index(_width-1,_height,i)];//左下
					}
				}
				else{
					out=true;
				}			
			}
			else{//外侧
				out=true;
			}
			//--------------------
			if(out){//外侧
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			else{
				for (i=0;i<4;i++)//赋值
					mem[index_a+i]=(unsigned char)(buff[i]+0.5);			
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=new_width;
	this->_height=new_height;
}
void PicMat::Affine_U(float kx,float ky,float jx,float jy,int W,int H,unsigned char * fp){
	
	float xx,yy;//坐标变换后的浮点坐标
	int nx,ny;//取整之后结果
	int ix,iy;//移动的变量
	unsigned int index_a;//坐标对应点
	int i;
	int _width,_height;
	bool out;
	float Det;

	
	_width=this->_width;
	_height=this->_height;
	Det=jx*ky-jy*kx;

	index_a=0;
	for (iy=H;iy>-H;iy--){
		for (ix=-W;ix<W;ix++){
			//反变换
			xx=(-jy*ix+jx*iy)/Det;
			yy=(+ky*ix-kx*iy)/Det;
			//整数化
			nx=floor(xx+0.5);
			ny=floor(yy+0.5);
			//Initialize
			out=false;
			//
			if (nx>=-_width && nx<_width){
				if(ny<=_height && ny>-_height){
					out=true;
					fp[index_a]=_fp[Index(nx,ny,0)];
					fp[index_a+1]=_fp[Index(nx,ny,1)];
					fp[index_a+2]=_fp[Index(nx,ny,2)];
					fp[index_a+3]=_fp[Index(nx,ny,3)];
				}
			}
			//--------------------
			if(!out){//外侧
				fp[index_a]=255;
				fp[index_a+1]=255;
				fp[index_a+2]=255;
				fp[index_a+3]=255;//设置透明度 白色
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=fp;
	this->_width=(unsigned int)W;
	this->_height=(unsigned int)H;
}
//解一元二次方程
void PicMat::Quad(float a,float b,float c,float * out,int &n){
	double delta;
	if(a==0){
		if(b==0){
			if(c==0)
				n=-1;//恒成立
			else
				n=0;//无解
		}
		else
		{
			out[0]=-c/b;
			n=1;
		}
	}
	else{
		delta=b*b-4*a*c;
		if(delta<0){
			n=0;//无解
		}
		else{
			delta=sqrt(delta);
			out[0]=(-b+delta)/(2*a);
			out[1]=(-b-delta)/(2*a);
			n=2;//有解
		}
	}
}
void PicMat::Perspective(CPoint left_top,CPoint left_bottom,CPoint right_top,CPoint right_bottom,bool inter){
	if(zero) return;
	if (inter)
		Perspective_A(left_top,left_bottom,right_top,right_bottom);
	else
		Perspective_U(left_top,left_bottom,right_top,right_bottom);
	return;
}
void PicMat::Perspective_A(CPoint left_top,CPoint left_bottom,CPoint right_top,CPoint right_bottom){

//  100 50
//  从50画到149号点
	
	unsigned char * mem;
	unsigned int new_width,new_height;
	float xx,yy;//坐标变换后的浮点坐标
	int nx,ny;//取整之后结果
	int ix,iy;//移动的变量
	unsigned int index_a;//坐标对应点
	float u,v;int i;
	int _width,_height;
	bool out;
	float buff;
	float ans[2],ans2[2];
	int n;//需要解
	int x1,x2,y1,y2;
	int vector_x,vector_y;
	float a,b,c;
	
	//矢量定义
	float alpha_x,alpha_y;
	float belta1_x,belta1_y;
	float belta2_x,belta2_y;
	float _alpha_x,_alpha_y;

	_width=this->_width;
	_height=this->_height;
	
	//获得画布大小
	x1=x2=left_top.x;
	y1=y2=left_top.y;
	//1
	if(left_bottom.x<x1) x1=left_bottom.x;
	else if(left_bottom.x>x2) x2=left_bottom.x;
	if(left_bottom.y<y1) y1=left_bottom.y;
	else if(left_bottom.y>y2) y2=left_bottom.y;
	//2
	if(right_top.x<x1) x1=right_top.x;
	else if(right_top.x>x2) x2=right_top.x;
	if(right_top.y<y1) y1=right_top.y;
	else if(right_top.y>y2) y2=right_top.y;
	//3
	if(right_bottom.x<x1) x1=right_bottom.x;
	else if(right_bottom.x>x2) x2=right_bottom.x;
	if(right_bottom.y<y1) y1=right_bottom.y;
	else if(right_bottom.y>y2) y2=right_bottom.y;
	
	//新坐标和变换后的位移
	new_width=(x2-x1)/2+(x2-x1)%2;
	new_height=(y2-y1)/2+(y2-y1)%2;
	vector_x=(x2+x1)/2+(x2+x1)%2;
	vector_y=(y2+y1)/2+(y2+y1)%2;
	
	alpha_x=left_top.x-left_bottom.x;alpha_y=left_top.y-left_bottom.y;
	belta1_x=right_top.x-left_top.x;belta1_y=right_top.y-left_top.y;
	belta2_x=right_bottom.x-left_bottom.x;belta2_y=right_bottom.y-left_bottom.y;
	
	a=(belta1_x-belta2_x)*alpha_y-(belta1_y-belta2_y)*alpha_x;
	//Next
	index_a=0;
	mem=new unsigned char[new_width*new_height*4*4];
	//边缘模糊化
	for (i=0;i<2*_width;i++)
		_fp[i*4+3]=255;
	for (i=0;i<2*_width;i++)
		_fp[(_width*2*(2*_height-1)+i)*4+3]=255;
	for (i=0;i<2*_height;i++)
		_fp[(_width*2*i)*4+3]=255;
	for (i=0;i<2*_height;i++)
		_fp[(_width*2*(i+1)-1)*4+3]=255;
	
	for (iy=new_height;iy>-(int)new_height;iy--){
		for (ix=-new_width;ix<(int)new_width;ix++){
			//
			_alpha_x=ix+(vector_x-left_bottom.x);
			_alpha_y=iy+(vector_y-left_bottom.y);
			b=_alpha_x*(belta1_y-belta2_y)-_alpha_y*(belta1_x-belta2_x)+(alpha_y*belta2_x-alpha_x*belta2_y);
			c=belta2_y*_alpha_x-belta2_x*_alpha_y;
			Quad(a,b,c,ans,n);
			for(i=0;i<n;i++){
				if(ans[i]>0 && ans[i]<1){//顶部底部都不能取到
					ans2[i]=(_alpha_x-ans[i]*alpha_x)/(ans[i]*belta1_x+(1-ans[i])*belta2_x);
					if(ans2[i]>=0 && ans2[i]<1)//左侧能取到 右侧不能取到
						break;
				}
			}
			out=false;
			if(i<n){//成功跳出
				xx=ans2[i]*2*_width;
				yy=ans[i]*2*_height;
				nx=floor(xx);
				ny=floor(yy);
				u=xx-nx;v=yy-ny;
				nx=nx-_width;ny=ny-_height;
			}
			else
				out=true;
			buff=0;
			//
			if (nx==_width){//外侧
				out=true;
			}
			else if (ny==-_height){
				out=true;
			}
			//定界判定完成
			if(out){
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			else{
				for (i=0;i<4;i++){
					buff=0;
					buff+=(1-u)*(1-v)*_fp[Index(nx,ny,i)];//左下
					buff+=u*(1-v)*_fp[Index(nx+1,ny,i)];//右下
					buff+=(1-u)*v*_fp[Index(nx,ny+1,i)];//左上
					buff+=u*v*_fp[Index(nx+1,ny+1,i)];//右上
					mem[index_a+i]=(unsigned char)(buff+0.5);
				}
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=new_width;
	this->_height=new_height;
	this->Move(CPoint(vector_x,-vector_y));
}
void PicMat::Perspective_U(CPoint left_top,CPoint left_bottom,CPoint right_top,CPoint right_bottom){

//  100 50
//  从50画到149号点
	
	unsigned char * mem;
	unsigned int new_width,new_height;
	float xx,yy;//坐标变换后的浮点坐标
	int nx,ny;//取整之后结果
	int ix,iy;//移动的变量
	unsigned int index_a;//坐标对应点
	int i;
	int _width,_height;
	bool out;
	float ans[2],ans2[2];
	int n;//需要解
	int x1,x2,y1,y2;
	int vector_x,vector_y;
	float a,b,c;
	
	//矢量定义
	float alpha_x,alpha_y;
	float belta1_x,belta1_y;
	float belta2_x,belta2_y;
	float _alpha_x,_alpha_y;

	_width=this->_width;
	_height=this->_height;
	
	//获得画布大小
	x1=x2=left_top.x;
	y1=y2=left_top.y;
	//1
	if(left_bottom.x<x1) x1=left_bottom.x;
	else if(left_bottom.x>x2) x2=left_bottom.x;
	if(left_bottom.y<y1) y1=left_bottom.y;
	else if(left_bottom.y>y2) y2=left_bottom.y;
	//2
	if(right_top.x<x1) x1=right_top.x;
	else if(right_top.x>x2) x2=right_top.x;
	if(right_top.y<y1) y1=right_top.y;
	else if(right_top.y>y2) y2=right_top.y;
	//3
	if(right_bottom.x<x1) x1=right_bottom.x;
	else if(right_bottom.x>x2) x2=right_bottom.x;
	if(right_bottom.y<y1) y1=right_bottom.y;
	else if(right_bottom.y>y2) y2=right_bottom.y;
	
	//新坐标和变换后的位移
	new_width=(x2-x1)/2+(x2-x1)%2;
	new_height=(y2-y1)/2+(y2-y1)%2;
	vector_x=(x2+x1)/2+(x2+x1)%2;
	vector_y=(y2+y1)/2+(y2+y1)%2;
	
	alpha_x=left_top.x-left_bottom.x;alpha_y=left_top.y-left_bottom.y;
	belta1_x=right_top.x-left_top.x;belta1_y=right_top.y-left_top.y;
	belta2_x=right_bottom.x-left_bottom.x;belta2_y=right_bottom.y-left_bottom.y;
	
	a=(belta1_x-belta2_x)*alpha_y-(belta1_y-belta2_y)*alpha_x;
	//Next
	index_a=0;
	mem=new unsigned char[new_width*new_height*4*4];
	//不进行边缘模糊化
	for (iy=new_height;iy>-(int)new_height;iy--){
		for (ix=-new_width;ix<(int)new_width;ix++){
			//
			_alpha_x=ix+(vector_x-left_bottom.x);
			_alpha_y=iy+(vector_y-left_bottom.y);
			b=_alpha_x*(belta1_y-belta2_y)-_alpha_y*(belta1_x-belta2_x)+(alpha_y*belta2_x-alpha_x*belta2_y);
			c=belta2_y*_alpha_x-belta2_x*_alpha_y;
			Quad(a,b,c,ans,n);
			for(i=0;i<n;i++){
				if(ans[i]>0 && ans[i]<=1){//顶部能取到，底部不能取到
					ans2[i]=(_alpha_x-ans[i]*alpha_x)/(ans[i]*belta1_x+(1-ans[i])*belta2_x);
					if(ans2[i]>=0 && ans2[i]<1)//左侧能取到，右侧不能取到
						break;
				}
			}
			out=false;
			if(i<n){//成功跳出
				xx=ans2[i]*2*_width;
				yy=ans[i]*2*_height;
				nx=floor(xx+0.5);
				ny=floor(yy+0.5);
				nx=nx-_width;ny=ny-_height;
			}
			else
				out=true;
			//
			if (nx==_width){//外侧
				out=true;
			}
			else if (ny==-_height){
				out=true;
			}
			//定界判定完成
			if(out){
				mem[index_a]=255;
				mem[index_a+1]=255;
				mem[index_a+2]=255;
				mem[index_a+3]=255;//设置透明度 白色
			}
			else{
				for (i=0;i<4;i++){
					mem[index_a+i]=_fp[Index(nx,ny,i)];
				}
			}
			index_a+=4;//进位
		}
	}
	delete [] _fp;
	_fp=mem;
	this->_width=new_width;
	this->_height=new_height;
	this->Move(CPoint(vector_x,-vector_y));
}

