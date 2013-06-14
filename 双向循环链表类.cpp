// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<iostream>
#include<cassert>
using namespace std;

template<class Telem> class DList;
template<class Telem> class Dnode
{
	friend class DList<Telem>;
	Telem data;
	Dnode<Telem> *prior,*next;
public:
	Dnode(Dnode<Telem> *p = NULL,Telem d = 0,Dnode<Telem> *n = NULL)
	{
		prior = p;data = d;next = n;
	}
	Telem getdata() {return data;}
	void setdata(Telem &val) {data = val;}
	Dnode<Telem> *getnext() {return next;}
	void setnext(Dnode<Telem> *n) {next = n;}
	Dnode<Telem> *getprior() {return prior;}
	void setprior(Dnode<Telem> *p) {prior = p;}
};

//基类模板，可在此基础上实现顺序表，链表
template<class Telem>
class List
{
public:
	virtual void clear() = 0;                       //清空
	virtual int leng() = 0;						    //求长度
	virtual Telem gete(int loc) = 0;				//返回第 i 个元素
	virtual int loct(Telem &val) = 0;               //查找，若找到返回元素的序号，否则返回0
	virtual bool inst(int loc,Telem &val) = 0;      //将val插入到loc位置中
	virtual Telem dele(int loc) = 0;                //删除loc位置中的数据元素
	virtual bool full() = 0;                        //判断是否为满
	virtual bool empt() = 0;                        //判断是否为空
};

template<class Telem>
class DList :public List<Telem>
{
private:
	Dnode<Telem> * pHead;
	int size;
public:
	DList() {pHead = new Dnode<Telem>;pHead->prior = pHead->next = pHead;}
	DList(Telem a[],int n);
	~DList() {delete []pHead;}
	void clear() {delete []pHead; pHead = new Dnode<Telem>();size = 0;}
	Dnode<Telem> *index(int i);
	int leng() {return size;}
	Telem gete(int loc);
	int loct(Telem &val);
	bool inst(int loc,Telem& val);
	Telem dele(int loc);
	bool full() {return false;}
	bool empt() {return pHead->next == pHead;}
};

template<class Telem>
DList<Telem>::DList(Telem a[],int n)
{
	Dnode<Telem> *p;
	int i;
	pHead = new Dnode<Telem>;
	pHead->prior = pHead->next = pHead;
	for(i=n-1; i>=0; --i)
	{
		p = new Dnode<Telem>(pHead,a[i],pHead->next);
		pHead->next->setprior(p);
		pHead->setnext(p);
	}
	size = n;
}

template<class Telem>
Dnode<Telem> * DList<Telem>::index(int i)
{
	Dnode<Telem> *p;
	int j;
	if((i<0) || (i>size))
		p = NULL;
	else if(0 == i)
		p = pHead;
	else
	{
		p = pHead->next;
		j = 1;
		while((p != pHead) && (j<i))
		{
			p = p->next;
			++j;
		}
	}
	return p;
}

template<class Telem>
Telem DList<Telem>::gete(int i)
{
	if((i<1) || (i>size))
		return NULL;
	Dnode<Telem> *p = index(i);
	return p->getdata();
}

template<class Telem>
bool DList<Telem>::inst(int loc,Telem &val)
{
	if((loc<1) || (loc>size+1))
		return false;
	Dnode<Telem> *p = index(loc-1);
	Dnode<Telem> *s = new Dnode<Telem>(p,val,p->next);
	p->next->setprior(s);
	p->setnext(s);
	++size;
	return true;
}

template<class Telem>
int DList<Telem>::loct(Telem &val)
{
	Dnode<Telem> *p;
	int i = 1;
	p = pHead->next;
	while(p != NULL)
	{
		if(p->data == val)
			break;
		p = p->next;
		++i;
	}
	if(p == NULL)
		return 0;
	else
		return i;
}

template<class Telem>
Telem DList<Telem>::dele(int loc)
{
	if((loc>0) && (loc<=size))
	{
		Dnode<Telem> *p = index(loc-1);
		Telem val = p->next->getdata();
		p->setnext(p->next->next);
		p->next->setprior(p);
		--size;
		return val;
	}
	return NULL;
}
	
int main()
{
	char a[] = {'a','c','d','b'};
	char c = 'e';
	DList<char> dlist(a,4);
	dlist.inst(2,c);
	dlist.dele(5);
	for(int i=1; i<=dlist.leng(); ++i)
		cout << dlist.gete(i) << endl;
	return 0;
}