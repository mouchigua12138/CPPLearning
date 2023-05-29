#include <iostream>
#include "CA.h"
using namespace std;
int CA::_staticVal = 100;
CA::CA() : _CA(100), _CX(100) {
	this->_A = 100;
	cout << "CA类构造成功" << endl;
}
CA::CA(int a, int ca) : _CA(ca), _CX(100) {
	this->_A = a;
	cout << "CA类构造成功" << endl;
}
CA::CA(CA const& ca) : _CA(ca._CA), _CX(ca._CX){
	this->_A = ca._A;
	cout << "CA类构造成功" << endl;
}
CA::~CA() {
	cout << "CA类析构成功" << endl;
}
void CA::StaticFun() {
	cout << _staticVal;
}
void CA::FunConst() const {
	cout << this->_A + this->_CA + _staticVal;
}