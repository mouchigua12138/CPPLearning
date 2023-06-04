#pragma once

// CDialogPoint 对话框

class CDialogPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPoint)

public:
	CDialogPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogPoint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DialogPoint };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int ID;
	double x;
	double y;
	bool isOK;
	//CMFCExamView* pMain;

	afx_msg void OnBnClickedOk();
protected:
//	afx_msg LRESULT OnDialogPointOK(WPARAM wParam, LPARAM lParam);
};
