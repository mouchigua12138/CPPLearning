#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "C++.h"
#include "CMyString.h"
using namespace std;
using namespace Template;
int main()
{
	CMyString c1, c2;
	c1 = "1234560";
	c2 = "fergtrehtrhtrh";
	CMyString c3 = c1 + c2;
	bool m = c3 == c1 + c2;
	c3.print();
	cout << endl;
	CMyString c4 = c3 + "121355435";
	c4.print();
	CMyString c5(c1);
	cout << endl << c1[3] << endl;
	c5.print();
	CMyString c6("vrtbrbrtybhtry");
	cout << endl;
	c6.print();
	decltype(make_tuple("abc", 3, 5.26)) m0;
	cout << endl <<typeid(m0).name();
}