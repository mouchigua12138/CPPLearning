#pragma once
#include "CX.h"
class CA {
private:
	int _A;
	const int _CA;
	static int _staticVal;
	CX _CX;
public:
	CA();
	CA(int a, int ca);
	CA(CA const& ca);
	~CA();
	static void StaticFun();
	void FunConst() const;
};