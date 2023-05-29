#pragma once
#include "afxdialogex.h"


// CDialogPoint 对话框

class CDialogPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPoint)

public:
	CDialogPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogPoint();

	void SetPointInformation(int _ID, double _x, double _y);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DialogPoint };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int    _ID;
	double _x;
	double _y;
	bool   isOK;
	bool   isSearch;

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
