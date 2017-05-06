
#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#endif

typedef  double  ElementType;

struct Linked_list{
	ElementType data;
	Linked_list * Left;
	Linked_list * Right;
};

class Heap_H{	

private:
	int Capacity;
	int Pos;
	Linked_list  * * fp;
public:
	Heap_H(int size);
	~Heap_H();
	bool Is_Full(void);
	bool Is_Empty(void);
	bool Insert(Linked_list * a);
	Linked_list * Read_Delete(void);

};

Linked_list * Huffman(ElementType * fp,int num);//首地址指针，元素个数
void Print_leaves(Linked_list *list,int num);	//打印树叶
void Delete_Linked_list(Linked_list * list);	//删除链表
	





