#include "CTest.h"
#include <iostream>
using namespace std;
CTest::CTest():_dPi(3.14159265358){
	this->_nLength = 0;
	this->_nArray = NULL;
	cout << "CTest构造成功" << endl;
}
CTest::CTest(int _nLength):_dPi(3.14159265358) {
	this->_nLength = _nLength;
	this->_nArray = new int[_nLength];
	cout << "CTest构造成功" << endl;
}
CTest::CTest(const CTest& Copy):_dPi(3.14159265358) {
	this->_nLength = Copy._nLength;
	this->_nArray = new int[this->_nLength];
	for (int i = 0; i < this->_nLength; i++) {
		this->_nArray[i] = Copy._nArray[i];
	}
	cout << "CTest构造成功" << endl;
}
int CTest::GetLength() {
	return this->_nLength;
}
void CTest::SetElem(int Elem, int nPosition) {
	if (nPosition < 0 || nPosition >= this->_nLength) {
		cout << "数据不合法,输入失败" << endl;
		return;
	}
	this->_nArray[nPosition] = Elem;
}
void CTest::ScanElem(int nPosition) {
	if (nPosition < 0 || nPosition >= this->_nLength) {
		cout << "数据不合法,输入失败" << endl;
		return;
	}
	cin >> this->_nArray[nPosition];
}
void CTest::ScanArray() {
	int i = 0;
	cout << "请输入长度为" << this->_nLength << "的数组\n";
	for (i = 0; i < this->_nLength; i++) {
		cin >> this->_nArray[i];
	}
}
void CTest::Lengthen(int Elem) {
	int* nArray = new int[this->_nLength + 1];
	for (int i = 0; i < _nLength; i++) {
		nArray[i] = this->_nArray[i];
	}
	nArray[this->_nLength] = Elem;
	delete[] this->_nArray;
	this->_nArray = nArray;
	this->_nLength++;
}
void CTest::Shorten() {
	if (_nLength == 0) {
		cout << "无法对空数组进行该操作" << endl;
		return;
	}
	int* nArray = new int[this->_nLength - 1];
	for (int i = 0; i < this->_nLength - 1; i++) {
		nArray[i] = this->_nArray[i];
	}
	delete[] this->_nArray;
	this->_nArray = nArray;
	_nLength--;
}
void CTest::PrintElem(int nPosition) {
	if (nPosition < 0 || nPosition >= this->_nLength) {
		cout << "数据不合法,输出失败" << endl;
		return;
	}
	cout << this->_nArray[nPosition];
}
void CTest::PrintArray() {
	int i = 0;
	for (i = 0; i < this->_nLength; i++) {
		cout << this->_nArray[i] << " ";
	}
	cout << endl;
}
int CTest::GetElem(int nPosition) {
	if (nPosition < 0 || nPosition >= this->_nLength) {
		cout << "数据不合法,输出失败" << endl;
		exit(0);
	}
	return this->_nArray[nPosition];
}
CTest::~CTest() {
	if(_nArray != NULL)delete[] _nArray;
	cout << "CTest析构成功" << endl;
}
int GetLengthCTest(CTest CT) {
	return CT.GetLength();
}