#pragma once
#include "afxdialogex.h"


// CDialogCenterPoint 对话框

class CDialogCenterPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCenterPoint)

public:
	CDialogCenterPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogCenterPoint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DialogCenterPoint };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double x;
	double y;
	bool   isOK;
	afx_msg void OnBnClickedOk();
};
