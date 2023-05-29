#include "CLinkList.h"
#include <iostream>
using namespace std;
template <typename Type> CLinkList<Type>::CLinkList() {
	this->pHead = new LinkNode<Type>;
	this->pHead->pNext = NULL;
	cout << "�����๹��ɹ�" << endl;
}
template <typename Type> CLinkList<Type>::CLinkList(CLinkList& nLinkList) {
	this->pHead = new LinkNode<Type>;
	this->pHead->pNext = NULL;
	for (int i = 1; i <= nLinkList.Length(); i++) {
		this->Lengthen(nLinkList.GetElem(i));
	}
	cout << "�����࿽������ɹ�" << endl;
}
template <typename Type> CLinkList<Type>::~CLinkList() {
	if (this->pHead != NULL) {
		LinkNode<Type>* p = this->pHead;
		LinkNode<Type>* q = this->pHead->pNext;
		while (p->pNext != NULL) {
			delete p;
			p = q;
			q = q->pNext;
		}
		delete p;
	}
	cout << "�����������ɹ�" << endl;
}
template <typename Type> void CLinkList<Type>::Lengthen(Type nElem) {
	LinkNode<Type>* p = this->pHead;
	while (p->pNext != NULL)p = p->pNext;
	p->pNext = new LinkNode<Type>;
	p->pNext->Elem = nElem;
	p->pNext->pNext = NULL;
}
template <typename Type> void CLinkList<Type>::Shorten() {
	try {
		if (this->pHead->pNext == NULL) {
			cout << "����Ϊ����������ʧ��" << endl;
			throw "����Ϊ������";
		}
	}
	catch (...) {
		return;
	}
	LinkNode<Type>* p = this->pHead;
	while (p->pNext->pNext != NULL)p = p->pNext;
	LinkNode<Type>* q = p->pNext;
	delete q;
	p->pNext = NULL;
}
template <typename Type> Type CLinkList<Type>::Pop() {
	try {
		if (this->pHead->pNext == NULL) {
			cout << "����Ϊ����������ʧ��" << endl;
			throw "����Ϊ������";
		}
	}
	catch (...) {
		return EOF;
	}
	Type Ans = this->GetElem(this->Length());
	this->Shorten();
	return Ans;
}
template <typename Type> int CLinkList<Type>::Length() {
	int nLen = 0;
	LinkNode<Type>* p = this->pHead;
	while (p->pNext != NULL) {
		nLen++;
		p = p->pNext;
	}
	return nLen;
}
template <typename Type> Type CLinkList<Type>::GetElem(int nPosition) {
	try {
		if (nPosition <= 0 || nPosition > this->Length()) {
			cout << "���ݲ��Ϸ�������ʧ��" << endl;
			throw "���ݲ��Ϸ�";
		}
	}
	catch (...) {
		return EOF;
	}
	int nCount = 0;
	LinkNode<Type>* p = this->pHead;
	while (nCount < nPosition) {
		p = p->pNext;
		nCount++;
	}
	return p->Elem;
}
template <typename Type> void CLinkList<Type>::SetElem(int nPosition, Type nElem) {
	try {
		if (nPosition <= 0 || nPosition > this->Length()) {
			cout << "���ݲ��Ϸ����޸�ʧ��" << endl;
			throw "���ݲ��Ϸ�";
		}
	}
	catch (...) {
		return;
	}
	int nCount = 0;
	LinkNode<Type>* p = this->pHead;
	while (nCount < nPosition) {
		p = p->pNext;
		nCount++;
	}
	p->Elem = nElem;
}
template <typename Type> void CLinkList<Type>::InsertElem(int nPosition, Type nElem) {
	try {
		if (nPosition <= 0 || nPosition > this->Length() + 1) {
			cout << "���ݲ��Ϸ�������ʧ��" << endl;
			throw "���ݲ��Ϸ�";
		}
	}
	catch (...) {
		return;
	}
	int nCount = 0;
	LinkNode<Type>* p = this->pHead;
	while (nCount < nPosition - 1) { 
		p = p->pNext;
		nCount++;
	}
	LinkNode<Type>* Insert = new LinkNode<Type>;
	Insert->Elem = nElem;
	Insert->pNext = p->pNext;
	p->pNext = Insert;
}
template <typename Type> void CLinkList<Type>::DeleteElem(int nPosition) {
	try {
		if (nPosition <= 0 || nPosition > this->Length()) {
			cout << "���ݲ��Ϸ���ɾ��ʧ��" << endl;
			throw "���ݲ��Ϸ�";
		}
	}
	catch (...) {
		return;
	}
	if (nPosition == this->Length())this->Shorten();
	else {
		int nCount = 0;
		LinkNode<Type>* p = this->pHead;
		while (nCount < nPosition - 1) {
			p = p->pNext;
			nCount++;
		}
		LinkNode<Type>* q = p->pNext;
		p->pNext = p->pNext->pNext;
		delete q;
	}
}
template <typename Type> void CLinkList<Type>::Print() {
	if (this->Length() == 0) {
		cout << "������Ϊ������" << endl;
		return;
	}
	for (int i = 1; i <= this->Length(); i++)cout << GetElem(i) << " ";
	cout << endl;
}
template <typename Type> void CLinkList<Type>::Invert() {
	int nLen = this->Length();
	Type* pTemp = new Type[nLen];
	for (int i = 0; i < nLen; i++)pTemp[i] = this->GetElem(nLen - i);
	for (int i = 0; i < nLen; i++)this->SetElem(i + 1, pTemp[i]);
	delete[]pTemp;
}
template <typename Type> void CLinkList<Type>::ConnectLinkList(CLinkList& nCLinkList) {
	int nLen = nCLinkList.Length();
	if (nLen != 0) {
		for (int i = 1; i <= nLen; i++) {
			this->Lengthen(nCLinkList.GetElem(i));
		}
	}
}
template <typename Type> void CLinkList<Type>::SortSmallToBig() {
	int i, j, nLen = this->Length();
	for (i = 1; i <= nLen; i++) {
		for (j = 1; j <= nLen - 1; j++) {
			if (this->GetElem(j) > this->GetElem(j + 1)) {
				Type temp = this->GetElem(j);
				this->SetElem(j, this->GetElem(j + 1));
				this->SetElem(j + 1, temp);
			}
		}
	}
}
template <typename Type> void CLinkList<Type>::SortBigToSmall() {
	int i, j, nLen = this->Length();
	for (i = 1; i <= nLen; i++) {
		for (j = 1; j <= nLen - 1; j++) {
			if (this->GetElem(j) < this->GetElem(j + 1)) {
				Type temp = this->GetElem(j);
				this->SetElem(j, this->GetElem(j + 1));
				this->SetElem(j + 1, temp);
			}
		}
	}
}
template <typename Type> void CLinkList<Type>::Swap(int nPosition1, int nPosition2) {
	try {
		if ((nPosition1 <= 0 || nPosition1 > this->Length()) || (nPosition2 <= 0 || nPosition2 > this->Length())){
			cout << "���ݲ��Ϸ�������ʧ��" << endl;
			throw "���ݲ��Ϸ�";
		}
	}
	catch (...) {
		return;
	}
	if (nPosition1 == nPosition2)return;
	Type temp = this->GetElem(nPosition1);
	this->SetElem(nPosition1, this->GetElem(nPosition2));
	this->SetElem(nPosition2, temp);
}
template <typename Type> bool CLinkList<Type>::IsEmpty() {
	if (this->pHead->pNext == NULL)return true;
	else return false;
}
template <typename Type> void CLinkList<Type>::ScanLengthen() {
	Type newElem;
	cin >> newElem;
	this->Lengthen(newElem);
}
template <typename Type> void CLinkList<Type>::ScanLengthen(int nLen) {
	int i = 0;
	Type newElem;
	cout << "������Ҫ���������" << nLen << "��Ԫ�أ�" << endl;
	for (i = 0; i < nLen; i++) {
		cin >> newElem;
		this->Lengthen(newElem);
	}
}
template <typename Type> Type CLinkList<Type>::operator [] (int n) {
	return GetElem(n);
}