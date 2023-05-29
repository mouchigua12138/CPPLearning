#pragma once
class CMyString {
protected:
	char* _pBuffer;
public:
	CMyString();
	CMyString(const char* str);
	CMyString(CMyString const& c);
	~CMyString();
	int length() const;
	void print() const;
	CMyString& operator = (const char* str);
	char operator [] (int n);
	
	friend CMyString operator + (CMyString const& c1, CMyString const& c2);
	friend CMyString operator + (CMyString const& c1, const char* str2);
	friend bool operator == (CMyString const& c1, CMyString const& c2);
};
CMyString operator + (CMyString const& c1, CMyString const& c2);
CMyString operator + (CMyString const& c1, const char* str2);
bool operator == (CMyString const& c1, CMyString const& c2);