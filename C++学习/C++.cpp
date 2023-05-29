#define _CRT_SECURE_NO_WARNINGS
#include "C++.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace Template;
int Max_3(int a, int b, int c) {
	int nAns = a;
	if (b > nAns)nAns = b;
	if (c > nAns)nAns = c;
	return nAns;
}
int Min_3(int a, int b, int c) {
	int nAns = a;
	if (b < nAns)nAns = b;
	if (c < nAns)nAns = c;
	return nAns;
}
int Middle_3(int a, int b, int c) {
	int nMax = Max_3(a, b, c), nMin = Min_3(a, b, c);
	if (nMin<a && nMax>a)return a;
	if (nMin<b && nMax>b)return b;
	if (nMin<c && nMax>c)return c;
}
void SortABC(int* pa, int* pb, int* pc) {
	if (*pa == *pb || *pa == *pc || *pb == *pc) {
		cout << "请不要输入相同的数字,请重新输入" << endl;
		int a, b, c;
		cin >> a >> b >> c;
		SortABC(&a, &b, &c);
		*pa = a; *pb = b; *pc = c;
		return;
	}
	int nMax = Max_3(*pa, *pb, *pc), nMin = Min_3(*pa, *pb, *pc), nMid = Middle_3(*pa, *pb, *pc);
	*pb = nMax, * pa = nMid, * pc = nMin;
	return;
}
double Sum1(unsigned int n) {
	double dSum = 1;
	if (n == 0)return 0;
	if (n == 1)return 1;
	for (unsigned int i = 2; i <= n; i++) {
		dSum += pow(-1, i) / i;
	}
	return dSum;
}
double Fibonacci(unsigned int n) {
	if (n == 0)return 1;
	if (n == 1)return 1;
	if (n == 2)return 2;
	if (n >= 3)return Fibonacci(n - 1) + Fibonacci(n - 2);
}
double Sum2(int n) {
	double nSum = 0;
	int i;
	for (i = 1; i <= n; i++) {
		nSum += Fibonacci(2 * i - 1) / Fibonacci(2 * i);
	}
	return nSum;
}
void Search(unsigned int n) {
	unsigned int i, nCount = 0;
	for (i = 1; i < n; i++) {
		if (i % 5 == 0 && i % 9 == 0) {
			cout << i << " ";
			nCount++;
		}
	}
	if (nCount == 0)cout << "未发现所要求的数";
	return;
}
int Change0xPlace(int x) {
	return ((x >> 24) & 0x00000FF) + ((x >> 8) & 0x0000FF00) + ((x << 8) & 0x00FF0000) + ((x << 24) & 0xFF000000);
}
void strCat(char* str1, const char* str2) {
	while (*str1 != 0) {
		str1++;
	}
	while (*str2 != 0) {
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = 0;
}
void WeekCheck(int nTime) {
	switch (nTime) {
	case 0:
		cout << "星期日\n";
		break;
	case 1:
		cout << "星期一\n";
		break;
	case 2:
		cout << "星期二\n";
		break;
	case 3:
		cout << "星期三\n";
		break;
	case 4:
		cout << "星期四\n";
		break;
	case 5:
		cout << "星期五\n";
		break;
	case 6:
		cout << "星期六\n";
		break;
	default:
		cout << "请检查输入值是否合法,输入值应在0-6之间的整型数";
		break;
	}
	return;
}
int Sum3(int n) {
	int nSum = 0, i = 1;
	for (i = 1; i <= n; i++) {
		nSum += i;
	}
	return nSum;
}
int Sum4(int n) {
	int nSum = 0, i = 1;
	for (i = 1; i <= n; i++) {
		nSum += i;
		if (nSum > 1000)break;
	}
	return nSum;
}
int Sum5(int n) {
	int nSum = 0, i = 1;
	for (i = 1; i < n; i++) {
		if (i % 10 == 0)continue;
		nSum += i;
	}
	return nSum;
}
void RunTimeCount() {
	static int tm = 0;
	cout << "Run Time=" << tm++ << endl;
}
void Double2CharBit(double dTest, char strBit[65]){
	char* pcPosition = (char*)&dTest;
	char cTemplate = 000000001;
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 7; j >= 0; j--) {
			if ((*pcPosition & cTemplate) == 0) {
				strBit[8 * i + j] = '0';
			}
			else {
				strBit[8 * i + j] = '1';
			}
			cTemplate <<= 1;
		}
		cTemplate = 00000001;
		pcPosition++;
	}
	strBit[64] = 0;
}
void Float2CharBit(float fTest, char strBit[33]){
	char* pcPosition = (char*)&fTest;
	char cTemplate = 00000001;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 7; j >= 0; j--) {
			if ((*pcPosition & cTemplate) == 0) {
				strBit[8 * i + j] = '0';
			}
			else {
				strBit[8 * i + j] = '1';
			}
			cTemplate <<= 1;
		}
		cTemplate = 00000001;
		pcPosition++;
	}
	strBit[32] = 0;
}
void Int2CharBit(int nTest, char strBit[33]){
	char* pcPosition = (char*)&nTest;
	char cTemplate = 00000001;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 7; j >= 0; j--) {
			if ((*pcPosition & cTemplate) == 0) {
				strBit[8 * i + j] = '0';
			}
			else {
				strBit[8 * i + j] = '1';
			}
			cTemplate <<= 1;
		}
		cTemplate = 00000001;
		pcPosition++;
	}
	strBit[32] = 0;
}
void Short2CharBit(short sTest, char strBit[17]){
	char* pcPosition = (char*)&sTest;
	char cTemplate = 00000001;
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 7; j >= 0; j--) {
			if ((*pcPosition & cTemplate) == 0) {
				strBit[8 * i + j] = '0';
			}
			else {
				strBit[8 * i + j] = '1';
			}
			cTemplate <<= 1;
		}
		cTemplate = 00000001;
		pcPosition++;
	}
	strBit[16] = 0;
}
void Char2CharBit(char cTest, char strBit[9]){
	char* pcPosition = &cTest;
	char cTemplate = 00000001;
	int  j;
	for (j = 7; j >= 0; j--) {
		if ((*pcPosition & cTemplate) == 0) {
			strBit[j] = '0';
		}
		else {
			strBit[j] = '1';
		}	
		cTemplate <<= 1;
	}
	strBit[8] = 0;
}
bool IsLeapYear(int nYear) {
	if (((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0))return true;
	else return false;
}
int MonthType(int nMonth) {
	if (nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth == 8 || nMonth == 10 || nMonth == 12)return SolarMonth;
	else if (nMonth == 2)return LeapMonth;
	else return LunarMonth;
}
long CaculateDayFrom0(int nYear, int nMonth) {
	long nDay = 0;
	for (int i = 1; i < nYear; i++) {
		if (IsLeapYear(i))nDay += 366;
		else nDay += 365;
	}
	for (int i = 1; i <= nMonth; i++) {
		if (i - 1 == 0)nDay += 0;
        else if (MonthType(i - 1) == SolarMonth)nDay += 31;
		else if (MonthType(i - 1) == LunarMonth)nDay += 30;
		else if (MonthType(i - 1) == LeapMonth) {
			if (IsLeapYear(nYear))nDay += 29;
			else nDay += 28;
		}
	}
	return nDay;
}
void PrintCalendarMonth(int nYear, int nMonth) {
	const char strMonth[12][7] = { "一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月" };
	cout << setw(13) << strMonth[nMonth - 1] << endl;
	cout << "日 一 二 三 四 五 六" << endl;
	int nWeek = CaculateDayFrom0(nYear, nMonth) % 7 + 1;
	if (nWeek == 7)nWeek = 0;
	int nDay = 0;
	if (MonthType(nMonth) == SolarMonth)nDay = 31;
	else if (MonthType(nMonth) == LunarMonth)nDay = 30;
	else if (MonthType(nMonth) == LeapMonth) {
		if (IsLeapYear(nYear))nDay = 29;
		else nDay = 28;
	}
	int nCount = 1;
	cout << setw(3 * nWeek + 1);
	for (; nCount <= 7 - nWeek; nCount++) {
		cout << nCount << "  ";
	}
	cout << endl;
	int nWeek0 = (nDay - nCount) / 7;
	for (int n = 1; n <= nWeek0; n++) {
		for (int k = 1; k <= 7; k++, nCount++) {
			if (nCount < 10)cout << nCount << "  ";
			else cout << nCount << " ";
		}
		cout << endl;
	}
	int nDayRest = nDay - nCount + 1;
	for (int n = 1; n <= nDayRest; n++ , nCount++) {
		cout << nCount << " ";
	}
	cout << endl;
}
void PrintCalendarYear(int nYear) {
	if (nYear <= 0) { 
		cout << "数据不合法，请输入公元后的年份";
		return;
	}
	int i;
	for (i = 1; i <= 12; i++) {
		PrintCalendarMonth(nYear, i);
	}
}
void PrintTri(int N) {
	int i = 1;
	for (i = 1; i <= N; i++) {
		for (int j = 0; j <= i - 1; j++) {
			cout << ' ';
		}
		for (int j = 0; j <= 2 * N - 2 * i + 1; j++) {
			cout << '*';
		}
		cout << endl;
	}
	return;
}
void Sort(int A[], int nCount) {
	int i, j;
	for (i = 0; i < nCount; i++) {
		for (j = 0; j < nCount - 1; j++) {
			if (A[j] < A[j + 1]) {
				int temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
}
int Sum6(int m) {
	int ans = 1;
	if (m == 1)return 1;
	else {
		ans = Sum6(m - 1) + m;
		return ans;
	}
}
void ChangeStr(char* str) {
	int nLen = strlen(str), i;
	char* str0 = new char[nLen + 1];
	strcpy(str0, str);
	for (i = 0; i < nLen; i++) {
		str[i] = str0[nLen - i - 1];
	}
	delete[]str0;
}
void shpPrintFileHead(const char* strFILE) {
	ifstream FILEin;
	FILEin.open(strFILE, ios::in | ios::binary);
	if (!FILEin.is_open())return;
	int d;
	for (int i = 0; i < 36; i += 4) {
		FILEin.read((char*)&d, 4);
		if (i <= 24)cout << Change0xPlace(d) << endl;
		else cout << d << endl;
	}
	double D;
	for (int i = 36; i < 100; i += 8) {
		FILEin.read((char*)&D, 8);
		cout << setprecision(10) << D << endl;
	}
	FILEin.close();
}
int shpLength(const char* strFile) {
	ifstream FILEin;
	FILEin.open(strFile, ios::in | ios::binary);
	if (!FILEin.is_open())exit(0);
	int d, ans;
	for (int i = 0; i < 28; i += 4) {
		FILEin.read((char*)&d, 4);
		ans = Change0xPlace(d);
	}
	FILEin.close();
	return ans;
}
Point shpReadPoint(const char* strFile, int nPosition) {
	ifstream FileIn;
	FileIn.open(strFile, ios::in | ios::binary);
	if (!FileIn.is_open())exit(0);
	int nBit = nPosition / 4;
	int* d = new int[nBit + 3];
	FileIn.read((char*)d, nPosition + 12);
	delete[]d;
	Point ans;
	FileIn.read((char*)&ans.x, 8);
	FileIn.read((char*)&ans.y, 8);
	FileIn.close();
	return ans;
}