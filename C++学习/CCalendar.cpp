#include "CCalendar.h"
#include <iostream>
#include <iomanip>
using namespace std;
bool CCalendar::IsLeapYear(int nYear) {
	if (((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0))return true;
	else return false;
}
int CCalendar::MonthType(int nMonth) {
	if (nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth == 8 || nMonth == 10 || nMonth == 12)return SolarMonth;
	else if (nMonth == 2)return LeapMonth;
	else return LunarMonth;
}
long CCalendar::CaculateDayFrom0(int nMonth) {
	long nDay = 0;
	for (int i = 1; i < this->_nYear; i++) {
		if (this->IsLeapYear(i))nDay += 366;
		else nDay += 365;
	}
	for (int i = 1; i <= nMonth; i++) {
		if (i - 1 == 0)nDay += 0;
		else if (MonthType(i - 1) == SolarMonth)nDay += 31;
		else if (MonthType(i - 1) == LunarMonth)nDay += 30;
		else if (MonthType(i - 1) == LeapMonth) {
			if (this->IsLeapYear())nDay += 29;
			else nDay += 28;
		}
	}
	return nDay;
}
void CCalendar::PrintCalendarMonth(int nMonth) {
	const char strMonth[12][7] = { "一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月" };
	cout << setw(13) << strMonth[nMonth - 1] << endl;
	cout << "日 一 二 三 四 五 六" << endl;
	int nWeek = this->CaculateDayFrom0(nMonth) % 7 + 1;
	if (nWeek == 7)nWeek = 0;
	int nDay = 0;
	if (this->MonthType(nMonth) == SolarMonth)nDay = 31;
	else if (this->MonthType(nMonth) == LunarMonth)nDay = 30;
	else if (this->MonthType(nMonth) == LeapMonth) {
		if (this->IsLeapYear())nDay = 29;
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
	for (int n = 1; n <= nDayRest; n++, nCount++) {
		cout << nCount << " ";
	}
	cout << endl;
}
CCalendar::CCalendar(){
	this->_nYear = 1900;
	cout << "日历类构造成功" << endl;
}
CCalendar::CCalendar(unsigned int _nYear){
	this->_nYear = _nYear;
	cout << "日历类构造成功" << endl;
}
CCalendar::~CCalendar() {
	cout << "日历类析构成功" << endl;
}
void CCalendar::Set_nYear(int _nYear) {
	this->_nYear = _nYear;
}
bool CCalendar::IsLeapYear() {
	if (((this->_nYear % 4 == 0) && (this->_nYear % 100 != 0)) || (this->_nYear % 400 == 0))return true;
	else return false;
}
void CCalendar::PrintCalendar(){
	int i;
	for (i = 1; i <= 12; i++) {
		this->PrintCalendarMonth(i);
	}
}