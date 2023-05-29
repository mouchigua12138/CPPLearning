#pragma once
#include "afxdialogex.h"
#include "ShapeType.h"


// CDialogAddPoint 对话框

class CDialogAddPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAddPoint)

public:
	CDialogAddPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogAddPoint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DialogAddPoint };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	double _x;
	double _y;
	bool   isOK;

	afx_msg void OnBnClickedOk();
};
