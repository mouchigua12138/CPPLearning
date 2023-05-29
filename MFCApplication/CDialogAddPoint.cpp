// CDialogAddPoint.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "CDialogAddPoint.h"

CDialogAddPoint* pDialogAddPoint;

// CDialogAddPoint 对话框

IMPLEMENT_DYNAMIC(CDialogAddPoint, CDialogEx)

CDialogAddPoint::CDialogAddPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DialogAddPoint, pParent)


	, isOK(false)
{
	pDialogAddPoint = this;
}

CDialogAddPoint::~CDialogAddPoint()
{
}

void CDialogAddPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _x);
	DDX_Text(pDX, IDC_EDIT2, _y);
}

BEGIN_MESSAGE_MAP(CDialogAddPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogAddPoint::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogAddPoint 消息处理程序


void CDialogAddPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isOK = true;

	CDialogEx::OnOK();
}
