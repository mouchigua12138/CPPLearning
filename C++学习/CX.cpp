#include <iostream>
#include "CX.h"
using namespace std;
CX::CX(int _nVal) {
	this->_nVal = _nVal;
	cout << "CX类构造成功" << endl;
}
CX::~CX() {
	cout << "CX类析构成功" << endl;
}