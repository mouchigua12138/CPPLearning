#include <iostream>
#include "CX.h"
using namespace std;
CX::CX(int _nVal) {
	this->_nVal = _nVal;
	cout << "CX�๹��ɹ�" << endl;
}
CX::~CX() {
	cout << "CX�������ɹ�" << endl;
}