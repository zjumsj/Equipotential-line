#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "complex.h"

int main(void){
/*mode
	0 xy 
	1 rad
	2 deg
*/

	char s[100];
	Complex ans[4];
	Complex suan1;
	Complex suan2;

	char suan;
	double u,v;
	char mode=0;

	int i;
	for (i=0;i<4;i++)
		ans[i].v=ans[i].u=0;

	printf("欢迎使用复数计算工具\n");
	while (1){
H1:		
		printf("\n现在做什么?\nhelp帮助\nexit退出\n");
		scanf("%s",s);

		if (strcmp(s,"help")==0){
			printf("\n");
			printf("输入格式由前缀和数据组成：\n\ndeg，rad，xy为前缀，分别表示角度制弧度制和直角坐标表示,前缀可以省略\n\n");
			printf("数据为两个double，表示模和角度或实部和虚部\n也可输入ans，ans1，ans2，ans3代替，分别表示引用上一个算式结果，上上个算式结果，以此类推\n\n");
			printf("//**  **  **  **  **  **  **// \n输入举例：\n\ndeg 10 30  (模长10 夹角30度)\nnext\nans        (引用上个算式的结果)\n运算类型？\n+          (做加运算)\n\n如还有不明白直接询问程序猿orz\n");//弹出帮助file
			goto H1;
		}
		else if (strcmp(s,"exit")==0){
			return 0;
		}
		else if (strcmp(s,"deg")==0){
			mode=2;
			scanf("%lf",&u);
			scanf("%lf",&v);
			suan1.in_degree(u,v);
		}
		else if (strcmp(s,"rad")==0){
			mode=1;
			scanf("%lf",&u);
			scanf("%lf",&v);
			suan1.in_radian(u,v);
		}
		else if (strcmp(s,"xy")==0){
			mode=0;
			scanf("%lf",&u);
			scanf("%lf",&v);
			suan1.in_xy(u,v);
		}
		else if (strcmp(s,"ans")==0 || strcmp(s,"ans0")==0){
			suan1=ans[0];
		}
		else if (strcmp(s,"ans1")==0){
			suan1=ans[1];
		}
		else if (strcmp(s,"ans2")==0){
			suan1=ans[2];
		}
		else if (strcmp(s,"ans3")==0){
			suan1=ans[3];
		}
		else{
			u=atof(s);
			scanf("%lf",&v);
			switch (mode){
			case 0:suan1.in_xy(u,v);break;
			case 1:suan1.in_radian(u,v);break;
			case 2:suan1.in_degree(u,v);break;		
			};
		}
		printf("next\n");

		scanf("%s",s);
		if (strcmp(s,"exit")==0){
			return 0;
		}
		else if (strcmp(s,"deg")==0){
			mode=2;
			scanf("%lf",&u);
			scanf("%lf",&v);
			suan2.in_degree(u,v);
		}
		else if (strcmp(s,"rad")==0){
			mode=1;
			scanf("%lf",&u);
			scanf("%lf",&v);
			suan2.in_radian(u,v);
		}
		else if (strcmp(s,"xy")==0){
			mode=0;
			scanf("%lf",&u);
			scanf("%lf",&v);
			suan2.in_xy(u,v);
		}
		else if (strcmp(s,"ans")==0 || strcmp(s,"ans0")==0){
			suan2=ans[0];
		}
		else if (strcmp(s,"ans1")==0){
			suan2=ans[1];
		}
		else if (strcmp(s,"ans2")==0){
			suan2=ans[2];
		}
		else if (strcmp(s,"ans3")==0){
			suan2=ans[3];
		}
		else{
			u=atof(s);
			scanf("%lf",&v);
			switch (mode){
			case 0:suan2.in_xy(u,v);break;
			case 1:suan2.in_radian(u,v);break;
			case 2:suan2.in_degree(u,v);break;		
			};
		}
		/*
	suan 0 +
	suan 1 -
	suan 2 *
	suan 3 /
	*/


		while(1){

			printf("运算类型？\n");
			scanf("%s",s);
			if (s[0]=='+'){
				suan=0;
				break;
			}
			else if (s[0]=='-'){
				suan=1;
				break;
			}
			else if (s[0]=='*'){
				suan=2;
				break;
			}
			else if (s[0]=='/'){
				suan=3;
				break;
			}
			else
				continue;
		}
		for (i=2;i>=0;i--){
			ans[i+1]=ans[i];
		}

		switch (suan){
		case 0:
			ans[0]=suan1+suan2;
			break;
		case 1:
			ans[0]=suan1-suan2;
			break;
		case 2:
			ans[0]=suan1*suan2;
			break;
		case 3:
			ans[0]=suan1/suan2;
			break;
		}
		
		printf("%lf+i%lf\n",ans[0].u,ans[0].v);
		ans[0].out_degree(u,v);
		printf("角度制: %lf∠%lf°\n",u,v);
		ans[0].out_radian(u,v);
		printf("弧度制: %lf∠%lf\n",u,v);

	


		
	
	
	
	}
	


}