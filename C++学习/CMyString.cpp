#include <iostream>
#include "CMyString.h"
CMyString::CMyString() {
	this->_pBuffer = new char[5];
}
CMyString::CMyString(const char* str) {
	this->_pBuffer = new char[strlen(str) + 1];
	for (int i = 0; i <= strlen(str); i++) {
		this->_pBuffer[i] = str[i];
	}
}
CMyString::CMyString(CMyString const& c) {
	this->_pBuffer = new char[c.length() + 1];
	for (int i = 0; i <= this->length(); i++) {
		this->_pBuffer[i] = c._pBuffer[i];
	}
}
CMyString::~CMyString() {
	if (this->_pBuffer)delete[]this->_pBuffer;
}
int CMyString::length() const {
	int nCount = 0, i;
	for (i = 0; this->_pBuffer[i] != 0; i++) {
		nCount++;
	}
	return nCount;
}
void CMyString::print() const {
	std::cout << this->_pBuffer;
}
CMyString& CMyString::operator = (const char* str) {
	if (this->_pBuffer)delete[]this->_pBuffer;
	this->_pBuffer = new char[strlen(str) + 1];
	for (int i = 0; i <= this->length(); i++) {
		this->_pBuffer[i] = str[i];
	}
	return *this;
}
char CMyString::operator [] (int n) {
	if (n < 0 || n > this->length() + 1)exit(0);
	return this->_pBuffer[n];
}
CMyString operator + (CMyString const& c1, CMyString const& c2) {
	CMyString c3;
	if (c3._pBuffer)delete[]c3._pBuffer;
	c3._pBuffer = new char[c1.length() + c2.length() + 1];
	for (int i = 0; i < c1.length(); i++) {
		c3._pBuffer[i] = c1._pBuffer[i];
	}
	for (int i = c1.length(); i <= c1.length() + c2.length(); i++) {
		c3._pBuffer[i] = c2._pBuffer[i - c1.length()];
	}
	return c3;
}
CMyString operator + (CMyString const& c1, const char* str2) {
	CMyString c3;
	if (c3._pBuffer)delete[]c3._pBuffer;
	c3._pBuffer = new char[c1.length() + strlen(str2) + 1];
	for (int i = 0; i < c1.length(); i++) {
		c3._pBuffer[i] = c1._pBuffer[i];
	}
	for (int i = c1.length(); i <= c1.length() + strlen(str2); i++) {
		c3._pBuffer[i] = str2[i - c1.length()];
	}
	return c3;
}
bool operator == (CMyString const& c1, CMyString const& c2) {
	if (c1.length() != c2.length())return false;
	for (int i = 0; i < c1.length(); i++) {
		if (c1._pBuffer[i] != c2._pBuffer[i])return false;
	}
	return true;
}