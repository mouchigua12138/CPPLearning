// CDialogPoint.cpp: 实现文件
//

#include "pch.h"
#include "MFCExam.h"
#include "afxdialogex.h"
#include "CDialogPoint.h"


// CDialogPoint 对话框

IMPLEMENT_DYNAMIC(CDialogPoint, CDialogEx)

CDialogPoint::CDialogPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DialogPoint, pParent)
	, ID(0)
	, x(0)
	, y(0)
{

}

CDialogPoint::~CDialogPoint()
{
}

void CDialogPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ID);
	DDX_Text(pDX, IDC_EDIT2, x);
	DDX_Text(pDX, IDC_EDIT3, y);
}


BEGIN_MESSAGE_MAP(CDialogPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogPoint::OnBnClickedOk)
//	ON_MESSAGE(WM_DIALOGPOINTOK, &CDialogPoint::OnDialogPointOK)
END_MESSAGE_MAP()


// CDialogPoint 消息处理程序


void CDialogPoint::OnBnClickedOk()
{
	isOK = true;
	//GetParent()->GetParent()->Invalidate();
	AfxGetApp()->m_pMainWnd->Invalidate();
	CDialogEx::OnOK();
}
