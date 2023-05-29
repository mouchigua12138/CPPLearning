#pragma once
class CTest{
public:
	CTest();
	CTest(int _nLength);
	CTest(const CTest& Copy);
	void SetElem(int Elem, int nPosition);
	void ScanElem(int nPosition);
	void ScanArray();
	void Lengthen(int Elem);
	void Shorten();
	void PrintElem(int nPosition);
	void PrintArray();
	int GetLength();
	int GetElem(int nPosition);
	~CTest();
protected:
	const double _dPi;
private:
	int* _nArray;
	int _nLength;
};
int GetLengthCTest(CTest CT);
