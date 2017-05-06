#include "stdafx.h"

class PicMat;

class Layer{
private:
	CDC _DC;//只有当绘制时才使用 平时没用
	CBitmap layerbk, * _fall;
	bool zero;//背景有没有被载入？
	bool tzero;//内置CBitmap是否正常工作

	unsigned int _width;//画布大小
	unsigned int _height;//画布大小

	unsigned char * _fp;//只有当绘制时才使用 平时没用 不需要释放内存
	
	int cursor;//当前所在画布
	
	struct layer_unit{
		layer_unit * _former;
		layer_unit * _latter;
		bool _visible;
		char  name[180];
		PicMat * _con;
	};

	layer_unit * _fin;//首位置
	layer_unit * _fcur;//当前位置
	

public:
	Layer();
	~Layer();
	//独立的成员函数
	bool Load_Pic(char * apath,CBitmap * cbitmap, UINT ut=IMAGE_BITMAP);//读取图片 且以CBitmap作为格式
	//创建画布
	//void Match(void);//将DC和bitmap匹配 没有必要匹配，CBitmap只是作为一张背景而放置的
	//设置背景图层
	bool LoadBackGround(char * apath, UINT ut=IMAGE_BITMAP);//读取图片 且以CBitmap作为格式
	void CreateBackGround(unsigned int width,unsigned int height,COLORREF color=0);
	//创建新图层
	void Newlayer(char * c);//bool?
	void Copylayer(char * c);//复制当前图层到顶层
	//获得当前的图层指针
	PicMat * Current(void);
	//改变图层位置
	void Top(void);
	void Bottom(void);
	bool Find(char * c);
	void Visible(bool real);//改变可视性

	//产生所需要的画布并且复制到CPaintDC上
	void Draw(CPaintDC * dc,CDialog * dia);
	void Draw(CDC * pDC,CView *  cv);
	

};

class PicMat{
	friend class Layer;
private:
	CPoint _bias;
	unsigned int _width;//图形区域半宽
	unsigned int _height;//图形区域半高
	unsigned char * _fp;//四个一组为一个单位储存数据
	bool zero;

public:
	CPoint Bias(void);
	unsigned int Width(void);
	unsigned int Height(void);
	//
	PicMat(CPoint cp,unsigned int width,unsigned int height);
	PicMat();
	~PicMat();
	void operator=(const PicMat & one);
	void NewMat(CPoint cp=CPoint(50,50),unsigned int width=50,unsigned int height=50,COLORREF color=0);
	void Moveto(CPoint cp);//移动到某位置
	void Move(CPoint cp);//移动向量
	bool LoadPic(CPoint cp,char * apath,UINT ut=IMAGE_BITMAP);//读入Bitmap 尝试读入错误路径？
	void Transparent(COLORREF color=0);//把特定颜色转化成透明
	void SetTransparent(unsigned char alpha,bool force=false);//透明度0 - 255 不透明 - 完全透明 force 强制改变完全透明像素

	//Function 功能
	void Inverse();//反色
	void Brightness(float rate=1);//亮度
	void Saturation(float rate=1);//饱和度
	void Phase(float alpha=0);//颜色相位
	void Rotate(float alpha,bool inter=true);//旋转变换,inter=true 执行推荐的双插值变换
	void Stretch(unsigned int x,unsigned int y,bool inter=true);//伸缩变换,inter=true 执行推荐的双插值变换
	void Stretch(double ratex,double ratey,bool inter=true);//伸缩变换，inter=true 执行推荐的双插值变换
	void Mirror(bool x,bool y);//镜面反射 对于x轴镜面反射 对于y轴镜面反射
	void Affine(CPoint right_top,CPoint right_bottom,bool inter=true);//仿射变换，inter=true 执行推荐的双插值变换
	void Perspective(CPoint left_top,CPoint left_bottom,CPoint right_top,CPoint right_bottom,bool inter=true);
	//透视变换 给定四周的四个点坐标 inter=true 执行推荐的双插值变换
	void Cut(CPoint center,unsigned int width,unsigned int height);//裁剪
	
private:
	void RGB2HSI(unsigned char r,unsigned char g,unsigned char b,float &h,float &s,float &i);
	void HSI2RGB(float h,float s,float i,unsigned char &r,unsigned char &g,unsigned char &b);
	unsigned int Index(int x,int y,int i);//寻址函数
	void Rotate_U(float alpha);//非双插值的旋转算法
	void Stretch_U(unsigned int x,unsigned int y);//非双插值的伸缩变换
	void Affine_U(float kx,float ky,float jx,float jy,int W,int H,unsigned char * fp);//仿射变换，inter=true 执行推荐的双插值变换
	void Quad(float a,float b,float c,float * out,int &n);//解一元二次方程
	void Perspective_A(CPoint left_top,CPoint left_bottom,CPoint right_top,CPoint right_bottom);
	void Perspective_U(CPoint left_top,CPoint left_bottom,CPoint right_top,CPoint right_bottom);








};
//cb.CreateBitmap(10,10,1,32,ssss); 1 位平面 32位
//0 表示不透明更合适