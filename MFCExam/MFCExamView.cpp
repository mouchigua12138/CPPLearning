
// MFCExamView.cpp: CMFCExamView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCExam.h"
#endif

#include "MFCExamDoc.h"
#include "MFCExamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCExamView

IMPLEMENT_DYNCREATE(CMFCExamView, CView)

BEGIN_MESSAGE_MAP(CMFCExamView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	

	ON_COMMAND(32771, &CMFCExamView::On32771)
	ON_COMMAND(32772, &CMFCExamView::On32772)
	ON_COMMAND(32773, &CMFCExamView::On32773)
	ON_COMMAND(32774, &CMFCExamView::On32774)
	ON_COMMAND(32775, &CMFCExamView::On32775)
	ON_COMMAND(32776, &CMFCExamView::On32776)
	
END_MESSAGE_MAP()

// CMFCExamView 构造/析构

CMFCExamView::CMFCExamView() noexcept
{
	// TODO: 在此处添加构造代码
	xMin = DBL_MAX; xMax = DBL_MIN;
	yMin = DBL_MAX; yMax = DBL_MIN;

	xMin0 = DBL_MAX; xMax0 = DBL_MIN;
	yMin0 = DBL_MAX; yMax0 = DBL_MIN;

	nSearch = -1;
	isFly = false;
	isLDown = false;
	isRDown = false;

	dlgPoint = new CDialogPoint();

	dlgPoint->Create(IDD_DialogPoint);
}

CMFCExamView::~CMFCExamView()
{
	delete dlgPoint;
}

BOOL CMFCExamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCExamView 绘图

void CMFCExamView::OnDraw(CDC* pDC)
{
	CMFCExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (!v.empty())DrawPicture();

}


// CMFCExamView 打印

BOOL CMFCExamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCExamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCExamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

Point CMFCExamView::CaculateGeoToDraw(Point pt) {
	double sx = (xMax - xMin) / nClientRect.Width();
	double sy = (yMax - yMin) / nClientRect.Height();
	double s = max(sx, sy);
	double cx = (xMax + xMin) / 2;
	double cy = (yMax + yMin) / 2;

	Point ans = { (pt.x - cx) / s + nClientRect.Width() / 2,(pt.y - cy) / s + nClientRect.Height() / 2 };

	return ans;
}

Point CMFCExamView::CaculateDrawToGeo(Point pt) {
	double sx = (xMax - xMin) / nClientRect.Width();
	double sy = (yMax - yMin) / nClientRect.Height();
	double s = max(sx, sy);
	double cx = (xMax + xMin) / 2;
	double cy = (yMax + yMin) / 2;

	Point ans = { (pt.x - nClientRect.Width() / 2) * s + cx,(pt.y - nClientRect.Height() / 2) * s + cy };

	return ans;
}

void CMFCExamView::ReadFile() {

	CFileDialog fileDlg(TRUE);
	std::string strPath;

	if (fileDlg.DoModal() == IDOK) {
		CString str = fileDlg.GetPathName();
		strPath = CT2A(str.GetString());
	}

	std::ifstream fileIn;
	fileIn.open(strPath, std::ios::in | std::ios::binary);

	if (!fileIn.is_open()) {
		MessageBoxA(NULL, "文件未正确打开!", "错误", 0);
		return;
	}

	int nNum;
	fileIn.read((char*)&nNum, 4);

	for (int i = 0; i < nNum; i++) {
		CStudent stu;
		char lenID, lenName, cElem;

		fileIn.read(&lenID, 1);
		for (int j = 0; j < lenID; j++) {
			fileIn.read(&cElem, 1);
			stu.ID.push_back(cElem);
		}

		fileIn.read(&lenName, 1);
		for (int j = 0; j < lenName; j++) {
			fileIn.read(&cElem, 1);
			stu.Name.push_back(cElem);
		}

		fileIn.read((char*)&stu.pt.x, 8);
		fileIn.read((char*)&stu.pt.y, 8);

		fileIn.read((char*)stu.score, 12);

		v.push_back(stu);

	}

	fileIn.close();
}


void CMFCExamView::PrintTxt() {
	CFileDialog fileDlg(TRUE);
	std::string strPath;

	if (fileDlg.DoModal() == IDOK) {
		CString str = fileDlg.GetPathName();
		strPath = CT2A(str.GetString());
	}

	std::ofstream fileOut;
	fileOut.open(strPath);

	if (!fileOut.is_open()) {
		MessageBoxA(NULL, "文件未正确打开!", "错误", 0);
		return;
	}

	fileOut << "学生总数：" << v.size() << "\n" << "\n";

	for (int i = 0; i < v.size(); i++) {
		fileOut << "IDLength:"   << v[i].ID.length()   << "\n";
		fileOut << "ID:"         << v[i].ID            << "\n";
		fileOut << "NameLength:" << v[i].Name.length() << "\n";
		fileOut << "Name:"       << v[i].Name          << "\n";
		fileOut << "Longitude:"  << v[i].pt.x          << "\n";
		fileOut << "Latitude:"   << v[i].pt.y          << "\n";
		fileOut << "score1:"     << v[i].score[0]      << "\n";
		fileOut << "score2:"     << v[i].score[1]      << "\n";
		fileOut << "score3:"     << v[i].score[2]      << "\n";

		fileOut << "\n";
	}

	fileOut.close();
}

void CMFCExamView::DrawPicture() {
	if (dlgPoint->isOK == true) {
		dlgPoint->isOK = false;
		if (dlgPoint->ID >= 0 && dlgPoint->ID < v.size()) {
			v.erase(v.begin() + dlgPoint->ID);
		}
	}
	
	GetClientRect(&nClientRect);
	CDC* pDC = GetDC();

	std::vector<Point> vptDraw;

	for (int i = 0; i < v.size(); i++) {
		vptDraw.push_back(CaculateGeoToDraw(v[i].pt));
	}


	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, nClientRect.Width(), nClientRect.Height());

	if (memDC.GetSafeHdc() != NULL) {
		CBitmap* pOldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);

		CBrush brush(RGB(255, 255, 255));
		memDC.FillRect(nClientRect, &brush);

		memDC.SetTextColor(RGB(100, 100, 255));
		if (isFly == true)memDC.TextOutW(5, 0, L"已开启漫游状态");
		memDC.SetTextColor(RGB(0, 0, 0));

		CString strInformation;
		strInformation = CA2T(v[0].Name.c_str());
		memDC.MoveTo(vptDraw[0].x, vptDraw[0].y);
		memDC.TextOutW(vptDraw[0].x, vptDraw[0].y + 5, strInformation);

		for (int i = 1; i < vptDraw.size(); i++) {
			memDC.LineTo(vptDraw[i].x, vptDraw[i].y);
			strInformation = CA2T(v[i].Name.c_str());
			memDC.TextOutW(vptDraw[i].x, vptDraw[i].y + 5, strInformation);
		}

		pDC->BitBlt(0, 0, nClientRect.Width(), nClientRect.Height(), &memDC, 0, 0, SRCCOPY);//将位图拷贝入视图
	}
	else {
		CBrush brush(RGB(255, 255, 255));
		pDC->FillRect(nClientRect, &brush);

		pDC->SetTextColor(RGB(100, 100, 255));
		if (isFly == true)pDC->TextOutW(5, 0, L"已开启漫游状态");
		pDC->SetTextColor(RGB(0, 0, 0));

		CString strInformation;
		strInformation = CA2T(v[0].Name.c_str());
		pDC->MoveTo(vptDraw[0].x, vptDraw[0].y);
		pDC->TextOutW(vptDraw[0].x, vptDraw[0].y + 5, strInformation);

		for (int i = 1; i < vptDraw.size(); i++) {
			pDC->LineTo(vptDraw[i].x, vptDraw[i].y);
			strInformation = CA2T(v[i].Name.c_str());
			pDC->TextOutW(vptDraw[i].x, vptDraw[i].y + 5, strInformation);
		}
	}

	memDC.DeleteDC();
	bitmap.DeleteObject();//回收GDI

	ReleaseDC(pDC);
}
// CMFCExamView 诊断

#ifdef _DEBUG
void CMFCExamView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCExamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCExamDoc* CMFCExamView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCExamDoc)));
	return (CMFCExamDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCExamView 消息处理程序
void CMFCExamView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isLDown == true && isFly == true) {
		Point ptDraw = { point.x,point.y };
		flyEnd = CaculateDrawToGeo(ptDraw);

		double dx = flyEnd.x - flyFirst.x;
		double dy = flyEnd.y - flyFirst.y;
		xMax -= dx; xMin -= dx;
		yMax -= dy; yMin -= dy;

		DrawPicture();
	}

	if (isRDown == true) {
		Point ptDraw = { point.x,point.y };
		REnd = CaculateDrawToGeo(ptDraw);

		Point lt = { min(RFirst.x, REnd.x), min(RFirst.y, REnd.y) };
		Point rb = { max(RFirst.x, REnd.x), max(RFirst.y, REnd.y) };

		Point LT = CaculateGeoToDraw(lt);
		Point RB = CaculateGeoToDraw(rb);

		DrawPicture();

		CDC* pDC = GetDC();
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 255));

		pDC->SelectObject(&pen);

		pDC->MoveTo(LT.x, LT.y);
		pDC->LineTo(LT.x, RB.y);
		pDC->LineTo(RB.x, RB.y);
		pDC->LineTo(RB.x, LT.y);
		pDC->LineTo(LT.x, LT.y);

		ReleaseDC(pDC);
	}

	//if (isLDown == true && isFly == false) {
	//	if (nSearch >= 0 && nSearch < v.size()) {
	//		Point ptDraw = { point.x,point.y };
	//		moveEnd = CaculateDrawToGeo(ptDraw);

	//		double dx = flyEnd.x - flyFirst.x;
	//		double dy = flyEnd.y - flyFirst.y;
	//		v[nSearch].pt.x -= dx;
	//		v[nSearch].pt.y -= dy;

	//		dlgPoint->x = v[nSearch].pt.x;
	//		dlgPoint->y = v[nSearch].pt.y;
	//		dlgPoint->UpdateData(FALSE);

	//		CDC* pDC = GetDC();

	//		CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	//		pDC->SelectObject(&pen);

	//		std::vector<Point> vptDraw;

	//		for (int i = 0; i < v.size(); i++) {
	//			vptDraw.push_back(CaculateGeoToDraw(v[i].pt));
	//		}
	//		pDC->MoveTo(vptDraw[nSearch].x - 5, vptDraw[nSearch].y - 5);
	//		pDC->LineTo(vptDraw[nSearch].x + 5, vptDraw[nSearch].y + 5);
	//		pDC->MoveTo(vptDraw[nSearch].x - 5, vptDraw[nSearch].y + 5);
	//		pDC->LineTo(vptDraw[nSearch].x + 5, vptDraw[nSearch].y - 5);

	//		ReleaseDC(pDC);

	//		DrawPicture();
	//	}
	//}
	CView::OnMouseMove(nFlags, point);
}

void CMFCExamView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (v.empty())return;
	DrawPicture();

	Point ptDraw = { point.x, point.y };
	flyFirst = CaculateDrawToGeo(ptDraw);
	moveFirst = CaculateDrawToGeo(ptDraw);
	isLDown = true;
	std::vector<Point> vptDraw;

	for (int i = 0; i < v.size(); i++) {
		vptDraw.push_back(CaculateGeoToDraw(v[i].pt));
	}

	for (int i = 0; i < vptDraw.size(); i++) {
		if (Distance(ptDraw, vptDraw[i]) < 3) {
			nSearch = i;
			break;
		}
		nSearch = -1;
	}

	if (nSearch == -1) {
		dlgPoint->ID = -1; dlgPoint->x = 0; dlgPoint->y = 0;
		dlgPoint->UpdateData(FALSE);
	}
	else {
		dlgPoint->ID = nSearch;
		dlgPoint->x = v[nSearch].pt.x;
		dlgPoint->y = v[nSearch].pt.y;
		dlgPoint->UpdateData(FALSE);

		CDC* pDC = GetDC();

		CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
		pDC->SelectObject(&pen);

		pDC->MoveTo(vptDraw[nSearch].x - 5, vptDraw[nSearch].y - 5);
		pDC->LineTo(vptDraw[nSearch].x + 5, vptDraw[nSearch].y + 5);
		pDC->MoveTo(vptDraw[nSearch].x - 5, vptDraw[nSearch].y + 5);
		pDC->LineTo(vptDraw[nSearch].x + 5, vptDraw[nSearch].y - 5);

		ReleaseDC(pDC);
	}


	CView::OnLButtonDown(nFlags, point);
}


void CMFCExamView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isLDown = false;
	CView::OnLButtonUp(nFlags, point);
}

void CMFCExamView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (v.empty())return;
	xMin = xMin0; xMax = xMax0;
	yMin = yMin0; yMax = yMax0;

	DrawPicture();

	CView::OnMButtonDown(nFlags, point);
}


void CMFCExamView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (v.empty())return;
	isRDown = true;
	Point ptDraw = { point.x, point.y };

	RFirst = CaculateDrawToGeo(ptDraw);

	CView::OnRButtonDown(nFlags, point);
}


void CMFCExamView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isRDown = false;

	Point ptDraw = { point.x, point.y };
	REnd = CaculateDrawToGeo(ptDraw);

	Point lt = { min(RFirst.x, REnd.x), min(RFirst.y, REnd.y) };
	Point rb = { max(RFirst.x, REnd.x), max(RFirst.y, REnd.y) };

	xMin = lt.x; xMax = rb.x;
	yMin = lt.y; yMax = rb.y;

	DrawPicture();

	CView::OnRButtonUp(nFlags, point);
}




void CMFCExamView::On32771()
{
	// TODO: 在此添加命令处理程序代码
	if (!v.empty()) { 
		v.clear();
		xMin = DBL_MAX; xMax = DBL_MIN;
		yMin = DBL_MAX; yMax = DBL_MIN;

		xMin0 = DBL_MAX; xMax0 = DBL_MIN;
		yMin0 = DBL_MAX; yMax0 = DBL_MIN;
	}

	ReadFile();

	if (v.empty())return;

	for (int i = 0; i < v.size(); i++) {
		if (v[i].pt.x < xMin)xMin = v[i].pt.x;
		if (v[i].pt.x > xMax)xMax = v[i].pt.x;
		if (v[i].pt.y < yMin)yMin = v[i].pt.y;
		if (v[i].pt.y > yMax)yMax = v[i].pt.y;
	}
	xMin0 = xMin; xMax0 = xMax;
	yMin0 = yMin; yMax0 = yMax;

	DrawPicture();
}


void CMFCExamView::On32772()
{
	// TODO: 在此添加命令处理程序代码
	if (v.empty())return;

	SortAverage(v);
	PrintTxt();

	DrawPicture();
}


void CMFCExamView::On32773()
{
	// TODO: 在此添加命令处理程序代码
	dlgPoint->ShowWindow(SW_SHOWNORMAL);
}


void CMFCExamView::On32774()
{
	// TODO: 在此添加命令处理程序代码
	if (isFly == false)isFly = true;
	else if (isFly == true)isFly = false;
}


void CMFCExamView::On32775()
{
	// TODO: 在此添加命令处理程序代码
	double dx = xMax - xMin;
	double dy = yMax - yMin;

	xMax -= dx / 10; xMin += dx / 10;
	yMax -= dy / 10; yMin += dy / 10;

	DrawPicture();
}


void CMFCExamView::On32776()
{
	// TODO: 在此添加命令处理程序代码
	double dx = xMax - xMin;
	double dy = yMax - yMin;

	xMax += dx / 10; xMin -= dx / 10;
	yMax += dy / 10; yMin -= dy / 10;

	DrawPicture();
}


