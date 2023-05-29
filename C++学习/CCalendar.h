#pragma once
#define SolarMonth 2
#define LunarMonth 1
#define LeapMonth 0
class CCalendar {
private:
	unsigned int _nYear;
	bool IsLeapYear(int nYear);
	int MonthType(int nMonth);
	long CaculateDayFrom0(int nMonth);
	void PrintCalendarMonth(int nMonth);
public:
	CCalendar();
	CCalendar(unsigned int _nYear);
	~CCalendar();
	void Set_nYear(int _nYear);
	bool IsLeapYear();
	void PrintCalendar();
};

