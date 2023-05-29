#pragma once
#define Status int
#define SolarMonth 2
#define LunarMonth 1
#define LeapMonth 0
#include "CTest.h"
#include <iostream>
using namespace std;
namespace Template {
	template <typename Type> double RootMeanSquare(Type tA, Type tB) {
		return sqrt(tA * tA + tB * tB);
	}
	template <typename Type> void MySwap(Type* t1, Type* t2) {
		Type temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
	template <typename Type> void Sort_Big_To_Little(Type array[], int num) {
		int i, j;
		for (i = 0; i < num; i++) {
			for (j = 0; j < num - 1; j++) {
				if (array[j] < array[j + 1]) {
					MySwap<Type>(&array[j], &array[j + 1]);
				}
			}
		}
	}
	template <typename Type> struct LinkList {
		Type num;
		LinkList<Type>* next;
	};
	template <typename Type> void CreateLinkList(LinkList<Type>*& Head) {
		Head = new LinkList<Type>;
		if (!Head) {
			cout << "链表创建失败";
			return;
		}
		Head->next = NULL;
	}
	template <typename Type> void DestoryLinkList(LinkList<Type>* Head) {
		LinkList<Type>* p, * q;
		p = Head; q = Head->next;
		while (q->next != NULL) {
			delete p;
			p = q;
			q = q->next;
		}
		delete q;
	}
	template <typename Type> void LengthenLinkList(LinkList<Type>* Head, Type Elem) {
		LinkList<Type>* p = Head;
		while (p->next != NULL)p = p->next;
		p->next = new LinkList<Type>;
		p = p->next;
		p->num = Elem;
		p->next = NULL;
	}
	template <typename Type> void ShortenLinkList(LinkList<Type>* Head) {
		LinkList<Type>* p = Head;
		if (p->next == NULL) {
			cout << "无法对空链表进行该操作";
			return;
		}
		while (p->next->next != NULL)p = p->next;
		LinkList<Type>* q = p->next;
		delete q;
		p->next = NULL;
	}
	template <typename Type> int LengthLinkList(LinkList<Type>* Head) {
		int i = 0;
		LinkList<Type>* p = Head;
		while (p != NULL) {
			p = p->next;
			i++;
		}
		return i - 1;
	}
	template <typename Type> void ScanLinkList(LinkList<Type>* Head) {
		int i, nLen;
		cout << "请输入链表长度：";
		cin >> nLen;
		for (i = 1; i <= nLen; i++) {
			Type Elem;
			cin >> Elem;
			LengthenLinkList<int>(Head, Elem);
		}
	}
	template <typename Type> void PrintLinkList(LinkList<Type>* Head) {
		if (Head->next == NULL) {
			cout << "该链表为空表";
			return;
		}
		LinkList<Type>* p = Head->next;
		while (p->next != NULL) {
			cout << p->num << " ";
			p = p->next;
		}
		cout << p->num;
	}
	template <typename Type> void SwapLinkList(LinkList<Type>* Head, int nLocation) {
		if (nLocation <= 0 || nLocation > LengthLinkList<Type>(Head) - 1) {
			cout << "交换节点位置不合法";
			return;
		}
		LinkList<Type>* p = Head;
		int nCount = 0;
		while (nCount < nLocation - 1) {
			p = p->next;
			nCount++;
		}
		LinkList<Type>* temp1 = p->next, * temp2 = p->next->next, * temp3 = p->next->next->next;
		p->next->next->next = temp1;
		p->next->next = temp3;
		p->next = temp2;
		return;
	}
	template <typename Type> void SortSmallToBigLinkList(LinkList<Type>*& Head) {
		int i, j, nLen = LengthLinkList<Type>(Head);
		if (nLen == 0) {
			cout << "链表为空，无法完成该操作";
			return;
		}
		if (nLen == 0)return;
		LinkList<Type>* p = Head;
		for (i = 0, p = Head; i < nLen + 1; i++, p = Head) {
			for (j = 1; j < nLen; j++, p = p->next) {
				if (p->next->num > p->next->next->num) {
					LinkList<Type>* q1 = p->next, * q2 = p->next->next;
					q1->next = q2->next;
					p->next = q2;
					q2->next = q1;
				}
			}
		}
	}
	template <typename Type> void DeleteElem(LinkList<Type>* Head, int n) {
		if (n <= 0 || n > LengthLinkList<Type>(Head)) {
			cout << "删除节点位置不合法";
			return;
		}
		int nCount = 0;
		LinkList<Type>* p = Head;
		for (; nCount < n - 1; nCount++, p = p->next);
		LinkList<Type>* q = p->next;
		p->next = q->next;
		delete q;
	}
	template <typename Type> void InsertElem(LinkList<Type>* Head, int n, Type Elem) {
		if (n <= 0 || n > LengthLinkList<Type>(Head) + 1) {
			cout << "插入节点位置不合法";
			return;
		}
		int nCount = 0;
		LinkList<Type>* p = Head;
		for (; nCount < n - 1; nCount++) p = p->next;
		LinkList<Type>* q = p->next;
		p->next = new LinkList<Type>;
		p = p->next;
		p->num = Elem;
		p->next = q;
	}
	template <typename Type> void ChangeElem(LinkList<Type>* Head, int n, Type Elem) {
		if (n <= 0 || n > LengthLinkList<Type>(Head)) {
			cout << "更改节点位置不合法";
			return;
		}
		DeleteElem<Type>(Head, n);
		InsertElem<Type>(Head, n, Elem);
	}
	template <typename Type>Type GetElem(LinkList<Type>* Head, int n) {
		if (n <= 0 || n > LengthLinkList<Type>(Head)) {
			cout << "节点不存在";
			exit(0);
		}
		int nCount = 0;
		LinkList<Type>* p = Head;
		for (; nCount < n - 1; nCount++) p = p->next;
		return p->next->num;
	}
	template <typename Type> void InvertLinker(LinkList<Type>* Head) {
		int nLen = LengthLinkList<Type>(Head);
		Type* temp = new Type[nLen];
		for (int i = 0; i < nLen; i++)temp[i] = GetElem<Type>(Head, i + 1);
		for (int i = 0; i < nLen; i++)ChangeElem<Type>(Head, i + 1, temp[9 - i]);
		delete[]temp;
	}
	template <typename Type> void SwapFirstToLastLinkList(LinkList<Type>* Head) {
		if (Head == NULL) {
			cout << "链表为空，无法完成该操作";
			return;
		}
		LinkList<Type>* p = Head;
		while (p->next->next != NULL)p = p->next;
		LinkList<Type>* q = Head->next;
		Head->next = p->next;
		p->next->next = q->next;
		p->next = q;
		q->next = NULL;
	}
	template <typename Type> void SortInsertSmallToBig(LinkList<Type>* Head) {
		LinkList<Type>* AnsHead;
		CreateLinkList<Type>(AnsHead);
		InsertElem<Type>(AnsHead, 1, GetElem<Type>(Head, 1));
		int nLen = LengthLinkList<Type>(Head);
		int nPosition = 1;
		for (int i = 2; i <= nLen; i++) {
			for (int j = 1;  j < i ; j++) {
				if (GetElem<Type>(AnsHead, j) < GetElem<Type>(Head, i))nPosition = j;
			}
			InsertElem<Type>(AnsHead, nPosition, GetElem<Type>(Head, i));
			nPosition = 1;
		}
		for (int i = 1; i <= LengthLinkList<Type>(Head); i++)ChangeElem(Head, i, GetElem(AnsHead, i));
		DestoryLinkList<Type>(AnsHead);
	}//插入排序算法
	template <typename Type> LinkList<Type>* CopyLinkList(LinkList<Type>* Head) {
		LinkList<Type>* AnsHead;
		CreateLinkList<Type>(AnsHead);
		for (int i = 1; i <= LengthLinkList<Type>(Head); i++) {
			LengthenLinkList<Type>(AnsHead, GetElem(Head, i));
		}
		return AnsHead;
	}
};
using namespace Template;
struct BookInfo {
	string strTitle;
	string strAuthor;
	int type;
	float price;
};
struct Student {
	char ID[20];
	string Name;
	float score[5];
};
struct Point {
	double x, y;
};
int Max_3(int a, int b, int c);
int Min_3(int a, int b, int c);
int Middle_3(int a, int b, int c);
void SortABC(int* pa, int* pb, int* pc);
double Sum1(unsigned int n);
double Fibonacci(unsigned int n);
double Sum2(int n);
void Search(unsigned int n);
int Change0xPlace(int x);
void strCat(char* str1, const char* str2);
void WeekCheck(int nTime);
int Sum3(int n);
int Sum4(int n);
int Sum5(int n);
void RunTimeCount();
void Double2CharBit(double dTest, char strBit[65]);
void Float2CharBit(float fTest, char strBit[33]);
void Int2CharBit(int nTest, char strBit[33]);
void Short2CharBit(short sTest, char strBit[17]);
void Char2CharBit(char cTest, char strBit[9]);
bool IsLeapYear(int nYear);
int MonthType(int nMonth);
long CaculateDayFrom0(int nYear, int nMonth);
void PrintCalendarMonth(int nYear, int nMonth);
void PrintCalendarYear(int nYear);
void PrintTri(int N);
void Sort(int A[], int nCount);
int Sum6(int m);
void ChangeStr(char* str);
void shpPrintFileHead(const char* strFILE);
int shpLength(const char* strFile);
Point shpReadPoint(const char* strFile, int nPosition);