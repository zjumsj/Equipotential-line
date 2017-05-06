#include "kruskal.h"
#include <iostream.h>

double Rosenstiehl(Matrix<double> & st,char * & ans){
	int i,j,k,l;

	ans=new char[2];
	*ans='\0';

	if (st.Est==0){
		cout<<endl;
		cout<<"请新建矩阵"<<endl;
		return 0;
	}
	if(st.line!=st.list){
		cout<<endl;
		cout<<"关联矩阵是一个n×n的矩阵"<<endl;
		return 0;
	}
	else{
		char * Huan=new char[st.line*(st.line-1)/2];
		int Position;
		int edge;
		
		E * begin;
		E * current;
		E * next;

		begin=new E;
		begin->np=NULL;
		current=begin;

		edge=0;//边的总数


		for (i=0;i<st.line;i++)
			for (j=i+1;j<st.line;j++){
				if (st.Value(i+1,j+1)!=st.Value(j+1,i+1)){
					cout<<endl;
					cout<<"关联矩阵是对称矩阵"<<endl;
					
					//释放已申请空间
					current=begin;
					while (1){
						next=current->np;
						delete current;
						if (next==NULL) break;
						current=next;
					}
					delete [] Huan;
					//
					return 0;				
				}
				Position=-1+j-i+(2*st.line-i-1)*i/2;

				if (st.Value(i+1,j+1)>0){
					Huan[Position]=1;
					//边的数据采集
					current->w=st.Value(i+1,j+1);
					current->u=i;
					current->v=j;
					current->np=new E;
					current=current->np;
					current->np=NULL;
					edge++;
				}
				else
					Huan[Position]=0;	
				//Huan 是否连通判断
			}

		if (edge<st.line-1){
			cout<<endl;
			cout<<"该图不连通"<<endl;

			//释放已申请空间
			current=begin;
			while (1){
				next=current->np;
				delete current;
				if (next==NULL) break;
				current=next;
			}
			delete [] Huan;
			//
			return 0;		
		}
		
		//边数据的排序 从大到小 冒泡排序
		E * * p_current;
		
		for (i=edge-1;i>0;i--){
			p_current=&begin;
			for (j=0;j<i;j++){				
				if ((*p_current)->w < (*p_current)->np->w)
					//调换两者的位置
				{
					next=*p_current;
					*p_current=(*p_current)->np;
					next->np=(*p_current)->np;
					(*p_current)->np=next;
				}
				p_current=&((*p_current)->np);
			}
		}
		//

		//获得环图
		cut_circle(Huan,st.line);

		E * * answer=new  E*[edge-st.line+1];//answer是一个指针数组answer[i]表示 * E
		i=0;//已经取到了i个边

		current=begin;
		while(1){
			j=current->u;
			k=current->v;
			if (j<k){//j>k
				l=j;
				j=k;
				k=l;
			}
			Position=-1+(2*st.line-k-1)*k/2+j-k;
			if (Huan[Position]!=0){
				Huan[Position]=0;

				//重新判断成环
				cut_circle(Huan,st.line);
				
				answer[i]=current;
				i++;
			}
			if (edge-i==st.line-1) break;

			current=current->np;
			//步长		
		}
		
		
		//获得结果的输出
		delete [] ans;
		//重新获得
		ans=new char[7*st.line];
		char * Ccu=ans;
		double sum=0;
		*Ccu=-72;
		Ccu++;
		*Ccu=-18;
		Ccu++;
		*Ccu=-79;
		Ccu++;
		*Ccu=-33;
		Ccu++;
		*Ccu=-93;
		Ccu++;
		*Ccu=-70;
		Ccu++;
		for (i=0;i<edge-st.line+1;i++){
			sum+=answer[i]->w;//返还权数
			*Ccu='(';
			Ccu++;
			Ccu=write_char(Ccu,answer[i]->u+1);
			*Ccu=',';
			Ccu++;
			Ccu=write_char(Ccu,answer[i]->v+1);
			*Ccu=')';
			Ccu++;
		}
		*Ccu='\0';
		
		//释放已申请空间
		current=begin;
		while (1){
			next=current->np;
			delete current;
			if (next==NULL) break;
			current=next;
		}
		delete [] Huan;
		delete [] answer;
		//
		return sum;


	}


}
double Prim(Matrix<double> & st,char * &ans){
	ans=new char[2];
	*ans='\0';

	if (st.Est==0){
		cout<<endl;
		cout<<"请新建矩阵"<<endl;
		return 0;
	}
	if(st.line!=st.list){
		cout<<endl;
		cout<<"关联矩阵是一个n×n的矩阵"<<endl;
		return 0;
	
	
	}
	else{
		//取边

		int i,j;
		int edge;//边数之和
		bool * p=new bool[st.line];//该点是否在已选集合中

		E * begin;
		E * current;
		E * next;

		begin=new E;
		begin->np=NULL;
		current=begin;

		edge=0;//边的总数
		for (i=0;i<st.line;i++){
			for (j=i+1;j<st.line;j++){
				if (st.Value(i+1,j+1)!=st.Value(j+1,i+1)){
					cout<<endl;
					cout<<"关联矩阵是对称矩阵"<<endl;
					//释放已申请空间
					current=begin;
					while (1){
						next=current->np;
						delete current;
						if (next==NULL) break;
						current=next;
					}
					delete [] p;
					//
					return 0;		
				}
				if (st.Value(i+1,j+1)>0){//边数据的采集o（n2）
					current->w=st.Value(i+1,j+1);
					current->u=i;
					current->v=j;
					current->np=new E;
					current=current->np;
					current->np=NULL;
					edge++;
				}
			}
		}
		if (edge<st.line-1){
			cout<<endl;
			cout<<"该图不连通"<<endl;

			//释放已申请空间
			current=begin;
			while (1){
				next=current->np;
				delete current;
				if (next==NULL) break;
				current=next;
			}
			delete [] p;
			//
			return 0;		
		}
		
		//重新分配空间
		char * Ccs;
		delete [] ans;
		ans=new char[7*st.line-6];
		Ccs=ans;

		for (i=0;i<st.line;i++)
			p[i]=false;

		
		int min_index;
		double min,sum;
		
		sum=0;
		
		//起始点

		p[0]=true;
		j=0;
		while(1){
			current=begin;
			min=-1;
			min_index=-1;
			for (i=0;i<edge;i++){
				if (p[current->u]^p[current->v] ){
					if (min<0 ){
						min=current->w;
						min_index=i;
					}
					else if (min>current->w){
						min=current->w;
						min_index=i;
					}
				}
				current=current->np;
			}
			//找到链表的位置
			current=begin;
			for (i=0;i<min_index;i++)
				current=current->np;
			//将找到的点的位置置true
			if (p[current->u]==true)
				p[current->v]=true;
			else
				p[current->u]=true;
			//
			sum+=min;
			j++;
			*Ccs='(';
			Ccs++;
			Ccs=write_char(Ccs,current->u+1);
			*Ccs=',';
			Ccs++;
			Ccs=write_char(Ccs,current->v+1);
			*Ccs=')';
			Ccs++;			
			if (j==st.line-1) break;		
		}
		*Ccs='\0';
		//释放已申请空间
		current=begin;
		while (1){
			next=current->np;
			delete current;
			if (next==NULL) break;
			current=next;
		}
		delete [] p;
		//
		return sum;		
	}

}

double Kruskal(Matrix<double> & st,char * &ans){
	ans=new char[2];
	*ans='\0';

	if (st.Est==0){
		cout<<endl;
		cout<<"请新建矩阵"<<endl;
		return 0;
	}
	if(st.line!=st.list){
		cout<<endl;
		cout<<"关联矩阵是一个n×n的矩阵"<<endl;
		return 0;
	
	
	}
	else{
		//取边

		int i,j;
		int edge;//边数之和
		int * p=new int[st.line];//get parent node

		E * begin;
		E * current;
		E * next;

		begin=new E;
		begin->np=NULL;
		current=begin;

		edge=0;//边的总数
		for (i=0;i<st.line;i++){
			for (j=i+1;j<st.line;j++){
				if (st.Value(i+1,j+1)!=st.Value(j+1,i+1)){
					cout<<endl;
					cout<<"关联矩阵是对称矩阵"<<endl;
					//释放已申请空间
					current=begin;
					while (1){
						next=current->np;
						delete current;
						if (next==NULL) break;
						current=next;
					}
					delete [] p;
					//
					return 0;		
				}
				if (st.Value(i+1,j+1)>0){//边数据的采集o（n2）
					current->w=st.Value(i+1,j+1);
					current->u=i;
					current->v=j;
					current->np=new E;
					current=current->np;
					current->np=NULL;
					edge++;
				}
			}
		}
		if (edge<st.line-1){
			cout<<endl;
			cout<<"该图不连通"<<endl;

			//释放已申请空间
			current=begin;
			while (1){
				next=current->np;
				delete current;
				if (next==NULL) break;
				current=next;
			}
			delete [] p;
			//
			return 0;		
		}

		for (i=0;i<st.line;i++)
			p[i]=i;

		//把父节点设为自己


		//边数据的排序 从小到大 冒泡排序
		E * * p_current;
		
		for (i=edge-1;i>0;i--){
			p_current=&begin;
			for (j=0;j<i;j++){				
				if ((*p_current)->w > (*p_current)->np->w)
					//调换两者的位置
				{
					next=*p_current;
					*p_current=(*p_current)->np;
					next->np=(*p_current)->np;
					(*p_current)->np=next;
				}
				p_current=&((*p_current)->np);
			}
		}
		//

		E * * answer=new  E*[st.line-1];//answer是一个指针数组answer[i]表示 * E
		i=0;//已经取到了i个边

		current=begin;
		while(1){
			if (find_root(current->u,p)!=find_root(current->v,p)){
				//拥有不同的父节点
				answer[i]=current;
				//将v加到u中去,两者拥有相同父节点
				p[find_root(current->v,p)]=find_root(current->u,p);
				i++;
			}
			//否则成环			
			
			if (i==st.line-1) break;
			
			//步进
			current=current->np;
		}

		//获得结果的输出
		delete [] ans;
		//重新获得
		ans=new char[7*st.line-6];
		char * Ccu=ans;
		double sum=0;
		for (i=0;i<st.line-1;i++){
			sum+=answer[i]->w;//返还权数
			*Ccu='(';
			Ccu++;
			Ccu=write_char(Ccu,answer[i]->u+1);
			*Ccu=',';
			Ccu++;
			Ccu=write_char(Ccu,answer[i]->v+1);
			*Ccu=')';
			Ccu++;
		}
		*Ccu='\0';
		
		//释放已申请空间
		current=begin;
		while (1){
			next=current->np;
			delete current;
			if (next==NULL) break;
			current=next;
		}
		delete [] p;
		delete [] answer;
		//
		return sum;


	}

}
static void cut_circle(char * Ins,int n){//n为矩阵阶数
	int signal;
	int i,j;
	int sum;
	int index;
	int position;

	signal=0;
	i=0;//点数

	while(1){
		sum=0;
		index=-1;

		//求某点的度
		for (j=0;j<i;j++){
			position=-1+(2*n-1-j)*j/2+i-j;
			sum+=(int)Ins[position];
			if (Ins[position])
				index=j;
		}
		for (j=i+1;j<n;j++){
			position=-1+(2*n-i-1)*i/2+j-i;
			sum+=(int)Ins[position];
			if (Ins[position])
				index=j;
		}
		//

		//拆除悬挂点
		if (sum==1){
			if (index<i)
				position=-1+(2*n-1-index)*index/2+i-index;
			else
				position=-1+(2*n-1-i)*i/2+index-i;
			Ins[position]=0;
			signal=i;
		}
		//

		i++;
		if (i==n)
			i=0;
		if (signal==i)break;
	}
	return;
}
static int find_root(int ser,int * all){
	return ser==all[ser] ? ser : find_root(all[ser],all);
}
static char * write_char(char * inn,int num){
	int fl=1;
	int i=0;
	while (1){//不能输0
		if (num/fl==0) break;
		fl*=10;
		i++;	
	}

	
	i--;
	fl/=10;

	for (;i>=0;i--){
		*inn='0'+num/fl;
		inn++;
		num=num%fl;
		fl/=10;
	}

	return inn;
}
