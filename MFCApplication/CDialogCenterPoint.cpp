// CDialogCenterPoint.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "CDialogCenterPoint.h"


// CDialogCenterPoint 对话框

IMPLEMENT_DYNAMIC(CDialogCenterPoint, CDialogEx)

CDialogCenterPoint::CDialogCenterPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DialogCenterPoint, pParent)
	, x(0)
	, y(0)
	, isOK(false)
{

}

CDialogCenterPoint::~CDialogCenterPoint()
{
}

void CDialogCenterPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, x);
	DDX_Text(pDX, IDC_EDIT2, y);
}


BEGIN_MESSAGE_MAP(CDialogCenterPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogCenterPoint::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogCenterPoint 消息处理程序


void CDialogCenterPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isOK = true;

	CDialogEx::OnOK();
}
