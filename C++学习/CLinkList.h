#pragma once
template <typename Type> struct LinkNode {
	Type Elem;
	LinkNode* pNext;
};
template <typename Type> class CLinkList {
protected:
	LinkNode<Type>* pHead;
public:
	CLinkList();
    CLinkList(CLinkList& nLinkList);
	~CLinkList();
	void Lengthen(Type nElem);
	void Shorten();
	Type Pop();
	int Length();
	Type GetElem(int nPosition);
	void SetElem(int nPosition, Type nElem);
	void InsertElem(int nPosition, Type nElem);
	void DeleteElem(int nPosition);
	void Print();
	void Invert();
	void ConnectLinkList(CLinkList& nLinkList);
	void SortSmallToBig();
	void SortBigToSmall();
	void Swap(int nPosition1, int nPosition2);
	bool IsEmpty();
	void ScanLengthen();
	void ScanLengthen(int nLen);
	Type operator [] (int n);
};