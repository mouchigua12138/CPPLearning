// CDialogPoint.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "CDialogPoint.h"

// CDialogPoint 对话框

IMPLEMENT_DYNAMIC(CDialogPoint, CDialogEx)

CDialogPoint::CDialogPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DialogPoint, pParent)
	, _ID(-1)
	, _x(0)
	, _y(0)
	, isOK(false)
	, isSearch(false)
{

}

CDialogPoint::~CDialogPoint()
{
}

void CDialogPoint::SetPointInformation(int _ID, double _x, double _y) {
	this->_ID = _ID;
	this->_x  = _x;
	this->_y  = _y;
}

void CDialogPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _ID);
	DDX_Text(pDX, IDC_EDIT2, _x);
	DDX_Text(pDX, IDC_EDIT3, _y);
}


BEGIN_MESSAGE_MAP(CDialogPoint, CDialogEx)

	ON_BN_CLICKED(IDOK, &CDialogPoint::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CDialogPoint::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDialogPoint 消息处理程序



void CDialogPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isOK = true;
	if(_ID != -1)MessageBox(L"删除成功！\n");

	CDialogEx::OnOK();
}


void CDialogPoint::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	isSearch = true;

	UpdateData(TRUE);

}
