#pragma once

#include <iostream.h>
#include <iomanip.h>
#include <typeinfo.h>


//矩阵 CLASS

template <class Type>
class Matrix{
public:    //变量
	/* 整体写入  */
	enum Method{M_Line,M_List};//行优先；列优先
	enum Sequence{Geometric,Arismetic};//等比方法；等差方法
	/* End 整体写入 */

	int line; //行数
	int list; //列数
	Type * _begin;
	bool Est;
	bool String;
	      //成员函数
	Matrix(){
		line=0;
		list=0;
		Est=0;
		String=0;
	    if(strcmp(typeid(Type).name(),"char *")==0)
			String=1;

		_begin=NULL;
	}

	
	void CleM(){
		if (Est==1){
			Est=0;
			delete[] this->_begin;
								
		}
		return ;
		
	}
	int NewM(int x,int y,Type c=0){ //返还1 表示正确新建//error
		int i,j;

		if (Est==1)
			CleM();
		if (x>0 && y>0 ){
			
			line=x;
			list=y;
			_begin=new Type[line*list];

			/*初始化*/
			for (i=0;i<line;i++)
				for (j=0;j<list;j++)
					_begin[list*i+j]=c;	//error
				
			Est=1;
			return 1;
						
			
		}
		else 
			return 0; 
		
	}
    
    Type Value(int x,int y){ //返还行列式中某元素
		

		if (Est==1){
			if (x>0 && x<=line)
				if (y>0 && y<=list){
					return _begin[list*(x-1)+y-1];
					
				}
		}
		return (Type) 0;

		
		
	}
	/* 整体写入 */
	

	int Write_All(Type Beg=0,Method method=M_Line,Sequence line_sequence=Arismetic,Type line_step=0,Sequence list_sequence=Arismetic,Type list_step=0){
		//起始值；行优先/列优先；行方法；行距；列方法；列距离
		// 1 正确返还
		/* (x,Matrix<T>::M_Line,Matrix<T>::Arismetic,(T)C.list,Matrix<T>::Arismetic,(T)1) 
		       | 1  2  3  4 |
			   | 5  6  7  8 |
			   | 9 10 11 12 |
		                                                    */
		int i,j;
		

		if (Est==1){
			_begin[0]=Beg;


			if (method==M_Line){
				
				for (i=1;i<line;i++){
				
					if (line_sequence==Arismetic)
						_begin[i*list]=_begin[(i-1)*list]+line_step;
					else
						_begin[i*list]=_begin[(i-1)*list]*line_step;
						
				}
				for (j=1;j<list;j++)
					for (i=0;i<line;i++){
						if(list_sequence==Arismetic)
							_begin[i*list+j]=_begin[i*list+j-1]+list_step;
						else
							_begin[i*list+j]=_begin[i*list+j-1]*list_step;
					}
			}
			else if(method==M_List){

				for (i=1;i<list;i++){
					if (list_sequence==Arismetic)
						_begin[i]=_begin[i-1]+list_step;
					else
						_begin[i]=_begin[i-1]*list_step;
				}
				for (j=1;j<line;j++)
					for (i=0;i<list;i++){
						if (line_sequence==Arismetic)
							_begin[j*list+i]=_begin[(j-1)*list+i]+line_step;
						else
							_begin[j*list+i]=_begin[(j-1)*list+i]*line_step;
					}
			}
			return 1;

		
		}	
		return 0;
	}
	/* End 整体写入 */
	
	int Write_Array(Type * & con,int num){//数组写入 返还1表示正确写入
		int i;
		if (Est==1){
			num> line*list ? num=line*list : num=num ;
			for (i=0;i<num;i++)
				_begin[i]=con[i];
			return 1;
		}
		return 0;
	
	
	}

	int Write_In(int x,int y,Type content){  //单个 写入 返还1表示正确写入
		if (Est==1){
			if (x>0 && x<=line)
				if (y>0 && y<=list){
					_begin[list*(x-1)+y-1]=content;
					return 1;
									
				}
		}
		return 0;
	}


	int Transposition(void){  //矩阵转置 返还1 转置成功
		Type *_kn;

		
		int i,j;
		int exchange;

		if (Est==1){
			_kn=new Type[list*line];
				
				for (i=0;i<line;i++)
					for (j=0;j<list;j++)
						_kn[j*line+i]=_begin[i*list+j];

				delete [] _begin;
				
				_begin=_kn;

				exchange=line;
				line=list;
				list=exchange;
				return 1;


				
		
			
		}

		return 0;
	}
	
	
	int Print(int digit=5){//返回1 表示正确输出 |用于C++控制台
		int i,j;
		
	
		
		if (Est==1){
			cout<<"\n";

			for (i=0;i<line;i++){
				for (j=0;j<list;j++)
					cout<<setw(digit)<<_begin[i*list+j];
				cout<<"\n";
			}
			return 1;
		}
		return 0;
	}

	int Equal_Fac_Normal(Type st,int *  &Dir){// 寻找相同的值并返还行列数
		int * dr=new int[2*line*list];
		int i,j;
		int sp=0;
		
		
		if (Est==1){


			
		for (i=0;i<line;i++)
			for (j=0;j<list;j++)
				if (_begin[i*list+j]==st){
					dr[sp++]=i;
					dr[sp++]=j;
						
				}
			
		
		Dir=new int[sp];
		for (i=0;i<sp;i++)
			Dir[i]=dr[i]+1; //加1后输出方是数学上的行列数
		delete[] dr;
		return sp/2;

		}



	    return 0;
	}
	/* char * 类型的查找函数 */
	int Equal_Fac_String(Type st,int * &Dir){
		int * dr=new int[2*line*list];
		int i,j;
		int sp=0;
		
		
		if (Est==1){


			
		for (i=0;i<line;i++)
			for (j=0;j<list;j++)
				if (strcmp(_begin[i*list+j],st)==0){
					dr[sp++]=i;
					dr[sp++]=j;
						
				}
			
		
		Dir=new int[sp];
		for (i=0;i<sp;i++)
			Dir[i]=dr[i]+1; //加1后输出方是数学上的行列数
		delete[] dr;
		return sp/2;
		}



	    return 0;
	}
	/* End char * */

	int Se_Max_Min(int * &Dir,bool i=0){//0 找最大值；!0 找最小值
		int num=0;
		int j;

		if (Est==1){
			if (!i){//最大
				for (j=1 ;j<line*list;j++)
					_begin[num]<_begin[j] ? num=j :num=num ;		
			}
			else
			{
				for (j=1;j<line*list;j++)
					_begin[num]>_begin[j] ? num=j: num=num   ;
		
			}
			return Equal_Fac_Normal(_begin[num],Dir);
		}
		return 0;	
	
	}


    Type Sum_Line(int li){ //求行和
		int i;
		Type sum=(Type) 0;

		if (Est==1){
			if (li>0 && li<=line){
				for (i=0;i<list;i++)
					sum+=_begin[(li-1)*list+i];
				return sum;
			}
		}
		return (Type) 0;
	}

	Type Sum_List(int li){ //求列和
		int i;
		Type sum=(Type) 0;

		if (Est==1){
			if (li>0 && li<=list){
				for (i=0;i<line;i++)
					sum+=_begin[i*list+li-1];
				return sum;
			}
		}
		return (Type) 0;
	}

	Type Sum_All(void){  //求全部加和
		int i,j;
		Type sum=(Type) 0;

		if (Est==1){
			for (i=0;i<line;i++)
				for (j=0;j<list;j++)
					sum+=_begin[i*list+j];
			return sum;
		}
		return (Type ) 0;
	}
	/*    重整 operator     */
	
	void operator =(Matrix<Type> &ma ){//A=B
		if (&ma==this) return;
		int i;
		
		if (ma.Est==1){
			this->NewM(ma.line,ma.list);
			for (i=0;i<ma.line*ma.list;i++)
				this->_begin[i]=ma._begin[i];
		}
		else
			this->CleM();

		return ;	
	}

	Matrix<Type> operator~(void){// A^T 转置
		Matrix<Type> mAdd;
		mAdd=*this;
		mAdd.Transposition();
		return mAdd;
	}
	Matrix<Type> operator-(void){//-A
		Matrix<Type> mAdd;
		int i;

		if (Est==1){
			mAdd.NewM(line,list);
			for (i=0;i<line*list;i++){
				mAdd._begin[i]=-this->_begin[i];
			}
		}
		return mAdd;	
	}
	Matrix<Type> operator*(Type ma){// A*b
		Matrix<Type> mAdd;
		int i;

		if (Est==1){
			mAdd.NewM(line,list);
			for (i=0;i<line*list;i++)
				mAdd._begin[i]=this->_begin[i]*ma;
		}

		return mAdd;
	}
	Matrix<Type> operator*(Matrix<Type> &ma){// A*B
		Matrix<Type> mAdd;
		int i,j;

		if ((Est & ma.Est)==1){
			if (list==ma.line){
				mAdd.NewM(line,ma.list);
				for (i=0;i<line;i++)
					for (j=0;j<ma.list;j++)
						mAdd._begin[i*ma.list+j]=Matrix_Mul(*this,ma,list,ma.list,i,j);
			}
		}

		return mAdd;
	}
	Matrix<Type> operator-(Type ma){//A-b
		Matrix<Type> mAdd;
		int i;

		if (Est==1){
			mAdd.NewM(line,list);
			for (i=0;i<line*list;i++)
				mAdd._begin[i]=this->_begin[i]-ma;
		}
		return mAdd;
	}
	Matrix<Type> operator-(Matrix<Type> &ma){//A-B
		Matrix<Type> mAdd;
		int i,j;

		if (Est==1){
			if (ma.Est==1){
				if (line==ma.line && list==ma.list){
					mAdd.NewM(line,list);
					for (i=0;i<line*list;i++)
						mAdd._begin[i]=this->_begin[i]-ma._begin[i];
					return mAdd;
				}
			}
			mAdd=*this;
		}
		else if (ma.Est==1)
			mAdd=ma;

		return mAdd;	
	
	}
	Matrix<Type> operator/(Type ma){// A/b
		Matrix<Type> mAdd;
		int i;

        if (Est==1){
			mAdd.NewM(line,list);
			if (ma==(Type)0)
				mAdd=*this;
			else
				for (i=0;i<line*list;i++)
					mAdd._begin[i]=this->_begin[i]/ma;
		}
		return mAdd;
	}
	Matrix<Type> operator+(Type ma){//A+b
		Matrix<Type> mAdd;
		int i;
		
		if (Est==1){
			mAdd.NewM(line,list);
			for (i=0;i<line*list;i++)
				mAdd._begin[i]=this->_begin[i]+ma;
		}
		return mAdd;
	}

	Matrix<Type> operator+(Matrix<Type> &ma){ //A+B
		Matrix<Type> mAdd;
		int i,j;

		if (Est==1){
			if (ma.Est==1){
				if (line==ma.line && list==ma.list){
					mAdd.NewM(line,list);
					for (i=0;i<line*list;i++)
						mAdd._begin[i]=this->_begin[i]+ma._begin[i];
					return mAdd;
				}
			}
			mAdd=*this;
		}
		else if (ma.Est==1)
			mAdd=ma;

		return mAdd;	
	}
	/* End 重整 operator  */



	//行列式部分功能 
	
	Type Trace(void){ //求迹
		int i;
		Type sum=(Type) 0;

		if (Est==1){
			if (line==list){
				for(i=0;i<line;i++)
					sum+=_begin[i*list+i];
				return sum;
								
			}
		}
		return (Type) 0;
	}
	double Determinant_Value(void){//double 类型 |求行列式的值
		double sum=(Type) 0;
		
		
		if (Est==1){
			if (line==list){
				int *i=new int[line];
				int j;
				for (j=0;j<line;j++)
					i[j]=j;
				sum=Seq(i,0);
				delete[] i;
				return sum;
				
			}
		}
		return -404;//报错
	}

	//矩阵部分功能
    
	int E_Exchange(int i,int j,Method met=M_Line){//行列互换 返还1成功
		int k;
		Type exc;

		i--;
		j--;

		if (Est==1){
			if (met==M_Line){
				if (i>=0 && i<line)
					if(j>=0 && j<line){
						for (k=0;k<list;k++){
							exc=_begin[i*list+k];
							_begin[i*list+k]=_begin[j*list+k];
							_begin[j*list+k]=exc;
						}
						return 1;
					}
			}
			else if (met==M_List){
				if (i>=0 && i<list)
					if(j>=0 && j<list){
						for (k=0;k<line;k++){
							exc=_begin[k*list+i];
							_begin[k*list+i]=_begin[k*list+j];
							_begin[k*list+j]=exc;
						}
						return 1;
					}
			}
		}
		return 0;	
	}

	int E_Multiply(int i,Type fac,Method met=M_Line){//行乘 返还1成功
		int k;

		i--;
		if (Est==1){
			if(met==M_Line){
				if (i>=0 && i<line){
					for (k=0;k<list;k++)
						_begin[i*line+k]*=fac;
					return 1;
				}
			}
			else if (met==M_List){
				if (i>=0 && i<list){
					for (k=0;k<line;k++)
						_begin[k*line+i]*=fac;
					return 1;				
				}			
			}
		}
		return 0;	
	}

	int E_Divide(int i,Type fac,Method met=M_Line){//行除 返还1成功
	    i--;

		if (fac==(Type)0) return 0;//防止除0

		if (Est==1){
			if(met==M_Line){
				if (i>=0 && i<line){
					for (k=0;k<list;k++)
						_begin[i*line+k]/=fac;
					return 1;
				}
			}
			else if (met==M_List){
				if (i>=0 && i<list){
					for (k=0;k<line;k++)
						_begin[k*line+i]/=fac;
					return 1;				
				}			
			}
		}
		return 0;	
	}

	int E_Add_Mul(int i,int j,Type fac=1,Method met=M_Line){// i=i+j*fac 返还1成功
        int k;
	
		i--;
		j--;

		if (Est==1){
			if (met==M_Line){
				if (i>=0 && i<line)
					if(j>=0 && j<line){
						for (k=0;k<list;k++)
							_begin[i*list+k]+=_begin[j*list+k]*fac;
						return 1;
					}
			}
			else if (met==M_List){
				if (i>=0 && i<list)
					if(j>=0 && j<list){
						for (k=0;k<line;k++)
							_begin[k*list+i]+=_begin[k*list+j]*fac;
						return 1;
					}
			}
		}
		return 0;
	}
	int E_Add_Div(int i,int j,Type fac=1,Method met=M_Line){// i=i+j/fac 返还1成功
        int k;
	
		i--;
		j--;

		if (fac==(Type)0) return 0 //除法 防0 保护

		if (Est==1){
			if (met==M_Line){
				if (i>=0 && i<line)
					if(j>=0 && j<line){
						for (k=0;k<list;k++)
							_begin[i*list+k]+=_begin[j*list+k]/fac;
						return 1;
					}
			}
			else if (met==M_List){
				if (i>=0 && i<list)
					if(j>=0 && j<list){
						for (k=0;k<line;k++)
							_begin[k*list+i]+=_begin[k*list+j]/fac;
						return 1;
					}
			}
		}
		return 0;
	}
	Matrix<double>  Echelon_M(char step=0){//化成阶梯矩阵 返还一个double型矩阵
		Matrix<double> mAdd;
		int i;

		if(Est==1){
			mAdd.NewM(line,list);
			for (i=0;i<line*list;i++)
				mAdd._begin[i]=(double)this->_begin[i];
			H(mAdd);
			if (step==0) return mAdd;
			H1(mAdd);
			if (step==1) return mAdd;
			H2(mAdd);
		}
		return mAdd;
	}
	int Rank_M(void){ //求秩
		Matrix<double> C;
		bool sum;
		int i,j;

		C=this->Echelon_M();
		i=0;
		while (sum!=0){
			if (i==line) {i++;break;}
			sum=0;
			for (j=0;j<list;j++)
				if(C._begin[i*list+j]!=0)
					sum=1;
			i++;
		}
		return i-1;
	}
private:
	/* 矩阵阶梯化 */

	void H(Matrix<double> & ma){//矩阵化阶梯形
		int i,j,k;

		double K;
		int min;
		int min_index;
		int step=0;//固定位置的个数

        while(1){
			i=step;
			j=0;
			while(j<ma.list  ){
				if(ma._begin[i*ma.list+j]!=0) break;
					j++;
			}
			min=j;
			min_index=i;
			for (i=step+1;i<ma.line;i++){
				j=0;
				while(j<ma.list){
					if(ma._begin[i*ma.list+j]!=0) break; 
					j++;
				}
				if (j<min){
					min=j;
					min_index=i;
				}
			}

			if (min==ma.list) break;

			ma.E_Exchange(step,min_index);//确定基准行
			for (i=step+1;i<ma.line;i++){
				K=ma._begin[i*ma.list+min]/ma._begin[step*ma.list+min]*(-1.0);
				//行加减变换
				for (k=0;k<ma.list;k++)
					ma._begin[i*ma.list+k]+=ma._begin[step*ma.list+k]*K;

				if (ma._begin[i*ma.list+min]!=0){
					cout<<"行乘精确度警告"<<endl;
					ma._begin[i*ma.list+min]=0;//因为精确度问题，需要手动归零
				}
			}
			step++;
			if (step==ma.line) break;
		}	
		return ;
	}
	void H1(Matrix<double> & ma){//矩阵化阶梯形 步骤二 化为单位一
		double K;
		int i,j;
		int step;//最末一行
		
		for (i=0;i<line;i++){
			for (j=i;j<list;j++){
				if (ma._begin[i*ma.list+j]!=0) break;
			}
			if (j==list) break;
			step=j;
			K=1.0/ma._begin[i*ma.list+step];
			for (j=step;j<list;j++){
				ma._begin[i*ma.list+j]*=K;
			}
			if (ma._begin[i*ma.list+step]!=1){
				cout<<"单位一划归精确度警告"<<endl;
				ma._begin[i*ma.list+step]=1;			
			}
			//理论上第一行应该是零
		}
		return ;
	}
	void H2(Matrix<double> & ma){//矩阵化阶梯形 步骤三 得到最简阶梯型
		double K;
		int i,j,k;
		int step;
		for (i=0;i<line ;i++){
			for (j=i;j<list;j++){
				if (ma._begin[i*ma.list+j]!=0) break;
			}
			if (j==list)
				break;
		}
		j=i-1;//返还最末位
		while(j>0){
			for (k=0;k<list;k++)
				if (ma._begin[j*ma.list+k]!=0){
					step=k;
					break;
				}
			for (i=0;i<j;i++){
				K=ma._begin[i*ma.list+step];
				for (k=step;k<list;k++)
					ma._begin[i*ma.list+k]-=K*ma._begin[j*ma.list+k];
				if (ma._begin[i*ma.list+step]!=0){//理论上该被化成零的地方应该被化成0
					cout<<"化成最简阶梯型精确度警告"<<endl;
					ma._begin[i*ma.list+step]=0;
				}
			}
			j--;
		}
		return ;
	}
/*  End 矩阵阶梯化  */
	Type Matrix_Mul(Matrix & A,Matrix & B,int step,int step_r,int a,int b){
		Type sum=(Type) 0;
		int i;
		for (i=0;i<step;i++){
			sum+=A._begin[a*step+i]*B._begin[i*step_r+b];
		}
		return sum;
	}
/* Determinant_Value     function */
	int S_Flag(int * &pu){//符号
		int sum=0,i,j;

		for(i=0;i<line-1;i++)
			for (j=i+1;j<line;j++)
				if (pu[i]>pu[j])
					sum++;
		if (sum%2==1)
			return -1;
		else
			return 1;
	}
	double S_Out(int * &pu){//Seq 的输出函数
		int i;
		double mul= 1;

		for (i=0;i<line;i++)
			mul*=_begin[i*list+pu[i]];
		mul*=S_Flag(pu);

		return mul;		
	}
		
	double Seq(int * &pu,int stat){
		int i;
		double sum= 0;
		
		int exc;

        //交换		
		for (i=stat;i<line;i++){
			exc=pu[stat];
			pu[stat]=pu[i];
			pu[i]=exc;

            if (stat==line-1){
				sum+=S_Out(pu);
				
			}
			else
				sum+=Seq(pu,stat+1);
			
			exc=pu[stat];
			pu[stat]=pu[i];
			pu[i]=exc;		
		
		}
		return sum;
	}
/* End  Determinant_Value     function */

/* strcmp    function     */
	int strcmp(const char * put1,char * put2){
		int i=0;
		while (put1[i]==put2[i]){
			if (put1[i]==0)
				return 0;
			i++;
		}
		return put1[i]-put2[i];
	
	
	
	}
	

	int strcmp(Type put1,Type put2){
		int i=0;
		while (put1[i]==put2[i]){
			if (put1[i]==0)
				return 0;
			i++;
		}
		return put1[i]-put2[i];
/* End strcmp     function */
	
	
	
	}
	

	

	


};