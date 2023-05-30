
// MFCApplicationView.cpp: CMFCApplicationView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "MFCApplicationView.h"

#include "CDialogAddPoint.h"
#include "CDialogCenterPoint.h"
#include "CDialogPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationView

IMPLEMENT_DYNCREATE(CMFCApplicationView, CView)

BEGIN_MESSAGE_MAP(CMFCApplicationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT,         &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()

	ON_COMMAND(32775, &CMFCApplicationView::On3)    //导入文件
	ON_COMMAND(32778, &CMFCApplicationView::On19)   //重置图形
	ON_COMMAND(32779, &CMFCApplicationView::On32779)//左移
	ON_COMMAND(32780, &CMFCApplicationView::On32780)//右移
	ON_COMMAND(32781, &CMFCApplicationView::On32781)//上移
	ON_COMMAND(32782, &CMFCApplicationView::On32782)//下移
	ON_COMMAND(32785, &CMFCApplicationView::On32785)//清空图形
	ON_COMMAND(32786, &CMFCApplicationView::On32786)//添加点
	ON_COMMAND(32787, &CMFCApplicationView::On32787)//操作点
	ON_COMMAND(32788, &CMFCApplicationView::On32788)//漫游
	ON_COMMAND(32793, &CMFCApplicationView::On32793)//转到中心点
END_MESSAGE_MAP()

// CMFCApplicationView 构造/析构

CMFCApplicationView::CMFCApplicationView() noexcept : BlackPen(PS_SOLID, 1, RGB(255, 255, 255))
{
	// TODO: 在此处添加构造代码
	isLDown = false;
	isRDown = false;
	isFly = false;
	
	nPosition = -1;
	dlgPoint = new CDialogPoint();
	dlgPoint->Create(IDD_DialogPoint);
}

CMFCApplicationView::~CMFCApplicationView()
{
	delete this->dlgPoint;
	oldBitmap.DeleteObject();
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationView 绘图

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

bool operator == (Point const& x, Point const& y) {

	if (x.x == y.x && x.y == y.y)return true;
	else return false;
}

double distance(Point const& x, Point const& y) {

	return std::sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

double xMax(std::vector<Point> const& v) {

	double x = v[0].x;
	for (int i = 0; i < v.size(); i++) {
		if (x < v[i].x)x = v[i].x;
	}
	return x;
}

double xMin(std::vector<Point> const& v) {

	double x = v[0].x;
	for (int i = 0; i < v.size(); i++) {
		if (x > v[i].x)x = v[i].x;
	}
	return x;
}

double yMax(std::vector<Point> const& v) {

	double y = v[0].y;
	for (int i = 0; i < v.size(); i++) {
		if (y < v[i].y)y = v[i].y;
	}
	return y;
}

double yMin(std::vector<Point> const& v) {

	double y = v[0].y;
	for (int i = 0; i < v.size(); i++) {
		if (y > v[i].y)y = v[i].y;
	}
	return y;
}

void CMFCApplicationView::ClearDraw() {

	CDC* pDC = GetDC();
	CBrush clear(RGB(255, 255, 255));
	pDC->SelectObject(&clear);
	pDC->FillRect(nClientRect, &clear);
	ReleaseDC(pDC);
}

void CMFCApplicationView::ClearDraw(CDC* pDC) {

	CBrush clear(RGB(255, 255, 255));
	CBrush* pOldBrush = pDC->SelectObject(&clear);
	pDC->FillRect(nClientRect, &clear);
	pDC->SelectObject(pOldBrush);
}

void CMFCApplicationView::DrawPoint(CDC* pDC) {
	
	for (int i = 0; i < v.size(); i++) {

		Point pt = caculateGeoToDraw(v[i]);

		pDC->MoveTo(pt.x - 5, pt.y - 5);
		pDC->LineTo(pt.x + 5, pt.y + 5);
		pDC->MoveTo(pt.x + 5, pt.y - 5);
		pDC->LineTo(pt.x - 5, pt.y + 5);
		//pDC->MoveTo((v[i].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  - 5,
		//	        (v[i].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom + 5);
		//pDC->LineTo((v[i].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  + 5,
		//        	(v[i].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom - 5);
		//pDC->MoveTo((v[i].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  - 5,
		//	        (v[i].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom - 5);
		//pDC->LineTo((v[i].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  + 5,
		//	        (v[i].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom + 5);
	}
}

void CMFCApplicationView::DrawPoint(Point pt, CDC* pDC) {

	Point dpt = caculateGeoToDraw(pt);

	pDC->MoveTo(dpt.x - 5, dpt.y - 5);
	pDC->LineTo(dpt.x + 5, dpt.y + 5);
	pDC->MoveTo(dpt.x - 5, dpt.y + 5);
	pDC->LineTo(dpt.x + 5, dpt.y - 5);
	//pDC->MoveTo((pt.x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  - 5,
	//	        (pt.y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom + 5);
	//pDC->LineTo((pt.x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  + 5,
	//	        (pt.y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom - 5);
	//pDC->MoveTo((pt.x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  - 5,
	//	        (pt.y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom - 5);
	//pDC->LineTo((pt.x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right  + 5,
	//	        (pt.y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom + 5);
}

void CMFCApplicationView::DeletePoint(Point pt, CDC* pDC) {

	int nSearch = -1;

	for (int i = 0; i < v.size(); i++) {
		if (v[i] == pt) {
			nSearch = i;
			break;
		}
	}

	if (nSearch == -1) {
		MessageBoxA(NULL, "未找到该点", "提示", 0);
		return;
	}
	
	v.erase(v.begin() + nSearch);
	ClearDraw();

	pDC->SetTextColor(RGB(100, 100, 255));
	if (isFly == true)pDC->TextOutW(5, 0, L"已开启漫游状态");
	pDC->SetTextColor(RGB(0, 0, 0));

	DrawPoint(pDC);
	DrawLine(pDC);
	DrawPolygonLine(pDC);
}

void CMFCApplicationView::DrawLine(CDC* pDC) {

	GetClientRect(&nClientRect);
	for (int i = 0; i < vl.size(); i++)DrawLine(vl[i], pDC);
}

void CMFCApplicationView::DrawLine(Line l, CDC* pDC) {

	//Point pt0 = caculateGeoToDraw(l.pt[0]);

	//pDC->MoveTo(pt0.x, pt0.y);

	//for (int i = 1; i < l.size; i++) {

	//	Point pt = caculateGeoToDraw(l.pt[i]);
	//	pDC->LineTo(pt.x, pt.y);
	//}

	Point* pGeo = l.pt;
	Point* pDraw = new Point[l.size];

	for (int i = 0; i < l.size; i++) {
		pDraw[i] = caculateGeoToDraw(pGeo[i]);
	}

	CPoint* pClient = new CPoint[l.size];

	for (int i = 0; i < l.size; i++) {
		pClient[i].x = pDraw[i].x;
		pClient[i].y = pDraw[i].y;
	}

	pDC->Polyline(pClient, l.size);//使用Polyline()函数绘图可提升效率

	delete[]pDraw;
	delete[]pClient;
}

void CMFCApplicationView::DrawPolygonLine(CDC* pDC) {

	GetClientRect(&nClientRect);
	for (int i = 0; i < vp.size(); i++) { 
		DrawPolygonLine(vp[i], pDC);
		
		/*此处考虑用多线程提速，但遇到几个问题：
		* 
		* 1.CDC类的拷贝：
		    使用指向同一CDC类的指针pDC会导致绘图混乱，但pDC可以在客户去绘图，也可以在位图中绘图
			但是没找到拷贝CDC类的函数

		* 2.进程是否结束的判断：
		    使用detach()处理线程时无法保证在输出位图时绘制位图已完成，会导致混乱，而使用join()处理会阻塞程序运行，使程序运行速度与优化前相同，无法提升

		* 3.绘图资源的占用
		    使用多线程会导致绘图资源大量占用内存，也会拖慢程序运行速度，但针对同一操作单纯使用循环结构也会大幅降低程序速度。
			正想办法折中，使用较少的绘图资源绘出大量的图形。考虑减少线程数，但算法逻辑有点迷
		*/

		//std::thread thrDrawPolygonLine([=](PolygonLine l, CDC* pDC)->void {
		//   CDC* thrDC = GetDC();
		//   DrawPolygonLine(vp[i], thrDC);
		//   ReleaseDC(thrDC);
		//}, vp[i], pDC);
		
		//thrDrawPolygonLine.detach();
	}
}

void CMFCApplicationView::DrawPolygonLine(PolygonLine l, CDC* pDC) {

	//Point pt0 = caculateGeoToDraw(l.pt[0]);

	//pDC->MoveTo(pt0.x, pt0.y);
	//pDC->MoveTo((l.pt[0].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right,
	//	        (l.pt[0].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom);

	//for (int i = 1; i < l.size; i++) {
		//pDC->LineTo((l.pt[i].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right,
		//	        (l.pt[i].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom);
	//	Point pt = caculateGeoToDraw(l.pt[i]);
	//	pDC->LineTo(pt.x, pt.y);
	//}

	Point* pGeo = l.pt;
	Point* pDraw = new Point[l.size];

	for (int i = 0; i < l.size; i++) {
		pDraw[i] = caculateGeoToDraw(pGeo[i]);
	}

	CPoint* pClient = new CPoint[l.size];

	for (int i = 0; i < l.size; i++) {
		pClient[i].x = pDraw[i].x;
		pClient[i].y = pDraw[i].y;
	}

	pDC->Polyline(pClient, l.size);//使用Polyline()函数绘图可提升效率

	delete[]pDraw;
	delete[]pClient;
}

void CMFCApplicationView::DrawPicture() {

	CDC* pDC = GetDC();
	DrawPicture(pDC);
	ReleaseDC(pDC);
}

void CMFCApplicationView::DrawPicture(CDC* pDC) {

	GetClientRect(&nClientRect);

	if (dlgPoint->_ID > -1 && dlgPoint->_ID < v.size() && dlgPoint->isOK == true) {
		v.erase(v.begin() + dlgPoint->_ID);

		dlgPoint->_ID = -1;
		dlgPoint->_x  = 0;
		dlgPoint->_y  = 0;
		dlgPoint->UpdateData(FALSE);

		dlgPoint->isOK = false;
		nPosition = -1;
	}
	else if ((dlgPoint->_ID <= -1 || dlgPoint->_ID >= v.size()) && dlgPoint->isOK == true) {
		dlgPoint->isOK = false;
	}

	if (dlgPoint->isSearch == true) {
		if (dlgPoint->_ID < 0 || dlgPoint->_ID >= v.size()) {
			dlgPoint->_ID = -1;
			dlgPoint->_x  = 0;
			dlgPoint->_y  = 0;
			dlgPoint->UpdateData(FALSE);

			dlgPoint->isSearch = false;
		}
		else {
			dlgPoint->_x = v[dlgPoint->_ID].x;
			dlgPoint->_y = v[dlgPoint->_ID].y;
			dlgPoint->UpdateData(FALSE);

			dlgPoint->isSearch = false;
		}
	}

	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, nClientRect.Width(), nClientRect.Height());

	if (memDC.GetSafeHdc() != NULL) {
		CBitmap* pOldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		//oldBitmap = *(CBitmap*)memDC.SelectObject(&bitmap);

		ClearDraw(&memDC);
		memDC.SetTextColor(RGB(100, 100, 255));
		if (isFly == true)memDC.TextOutW(5, 0, L"已开启漫游状态");
		memDC.SetTextColor(RGB(0, 0, 0));

		if (! v.empty())DrawPoint(&memDC);
		if (!vl.empty())DrawLine(&memDC);
		if (!vp.empty())DrawPolygonLine(&memDC);

		pDC->BitBlt(0, 0, nClientRect.Width(), nClientRect.Height(), &memDC, 0, 0, SRCCOPY);//将位图拷贝入视图
	}
	else {//如果位图未成功打开
		ClearDraw(pDC);
		pDC->SetTextColor(RGB(100, 100, 255));
		if (isFly == true)pDC->TextOutW(5, 0, L"已开启漫游状态");
		pDC->SetTextColor(RGB(0, 0, 0));

		if (! v.empty())DrawPoint(pDC);
		if (!vl.empty())DrawLine(pDC);
		if (!vp.empty())DrawPolygonLine(pDC);
	}

	memDC.DeleteDC();
	bitmap.DeleteObject();//回收GDI


	/*此处尝试用位图平移实现漫游，遇到以下问题
	* 1.当原位图尺寸过小时图形会糊掉
	* 2.BitBlt()函数与StretchBlt()函数的选用
	*/

	//ClearDraw(pDC);

	//pDC->SetTextColor(RGB(100, 100, 255));
	//if (isFly == true)pDC->TextOutW(5, 0, L"已开启漫游状态");
	//pDC->SetTextColor(RGB(0, 0, 0));

	//memDC.CreateCompatibleDC(pDC);

	//memDC.SelectObject(&oldBitmap);

	//Point startPt{ x0Temp - 5, y0Temp - 5 }, endPt{ xTemp + 5, yTemp + 5 };
	//Point start = caculateGeoToDraw(startPt);
	//Point end   = caculateGeoToDraw(endPt);

	//pDC->StretchBlt(start.x, start.y, 
	//	        (end.x - start.x) * (x - x0 + 10) / (xTemp - x0Temp + 10), 
	//	        (end.y - start.y) * (y - y0 + 10) / (yTemp - y0Temp + 10), 
	//	        &memDC, 0, 0, xTemp - x0Temp + 10, yTemp - y0Temp + 10,
	//	        SRCCOPY);

	//memDC.DeleteDC();
}

void CMFCApplicationView::shpFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fileDlg(TRUE);
	std::string strFilePath;

	if (IDOK == fileDlg.DoModal()) {
		CString str = fileDlg.GetPathName();
		strFilePath = CT2A(str.GetString());
	}

	ReadCoorWithoutEmpty(strFilePath);
	return;
}

Point CMFCApplicationView::caculateGeoToDraw(Point& pt) {

	//double yCenter = (y + y0) / 2;
	double sx = (x - x0) / nClientRect.Width();
	double sy = (y - y0) / nClientRect.Height();
	double s = max(sx, sy);
	double cx = (x + x0) / 2;
	double cy = (y + y0) / 2;

	Point ans = { (pt.x - cx) / s + nClientRect.Width() / 2,(pt.y - cy) / s + nClientRect.Height() / 2 };
	//Point ans = { (pt.x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right,
	//			  (pt.y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom };
	//ans.y = ans.y + 2 * (yCenter - ans.y);
	return ans;
}

Point CMFCApplicationView::caculateDrawToGeo(Point& pt) {

	//double yCenter = (y + y0) / 2;
	//Point ans = { (pt.x - 0.1 * nClientRect.right ) * (x - x0) / 0.8 / nClientRect.right  + x0,
	//              (pt.y - 0.1 * nClientRect.bottom) * (y - y0) / 0.8 / nClientRect.bottom + y0 };
	double sx = (x - x0) / nClientRect.Width();
	double sy = (y - y0) / nClientRect.Height();
	double s = max(sx, sy);
	double cx = (x + x0) / 2;
	double cy = (y + y0) / 2;

	Point ans = { (pt.x - nClientRect.Width() / 2) * s + cx,(pt.y - nClientRect.Height() / 2) * s + cy };

	return ans;
}

void CMFCApplicationView::ReadFileHead(std::ifstream& fileIn) {

	int nTemp;

	for (int i = 0; i < 9; i++)fileIn.read((char*)&nTemp, 4);

	fileIn.read((char*)&this->x0, 8);
	fileIn.read((char*)&this->y0, 8);
	fileIn.read((char*)&this->x , 8);
	fileIn.read((char*)&this->y , 8);

	xTemp  = x;
	x0Temp = x0;
	yTemp  = y;
	y0Temp = y0;

	double dTemp;
	for (int i = 0; i < 4; i++)fileIn.read((char*)&dTemp, 8);
}

void CMFCApplicationView::ReadShapeHead(std::ifstream& fileIn) {

	int nTemp;
	fileIn.read((char*)&nTemp, 4);
	fileIn.read((char*)&nTemp, 4);
}

int CMFCApplicationView::ReadShapeType(std::ifstream& fileIn) {

	int nType;
	fileIn.read((char*)&nType, 4);
	return nType;
}

void CMFCApplicationView::ReadPoint(std::ifstream& fileIn) {

	Point pt;
	fileIn.read((char*)&pt.x, 8);
	fileIn.read((char*)&pt.y, 8);
	this->v.push_back(pt);
}

void CMFCApplicationView::ReadLine(std::ifstream& fileIn) {

	double dTemp;
	for (int i = 0; i < 4; i++)fileIn.read((char*)&dTemp, 8);

	int nLen, nTemp;
	fileIn.read((char*)&nTemp, 4);
	fileIn.read((char*)&nLen, 4);
	fileIn.read((char*)&nTemp, 4);

	Line l(nLen);

	for (int i = 0; i < nLen; i++) {
		//fileIn.read((char*)&nTemp, 4);
		//无需再次读入点的图形类型标识
		Point pt;
		fileIn.read((char*)&pt.x, 8);
		fileIn.read((char*)&pt.y, 8);
		l.setPosition(pt, i);
	}

	vl.push_back(l);
}

void CMFCApplicationView::ReadPolygonLine(std::ifstream& fileIn) {

	double dTemp;
	for (int i = 0; i < 4; i++)fileIn.read((char*)&dTemp, 8);

	int nNum, nLen;
	fileIn.read((char*)&nNum, 4);
	fileIn.read((char*)&nLen, 4);

	int* nPart = new int[nNum];
	fileIn.read((char*)nPart, nNum * 4);

	for (int i = 0; i < nNum; i++) {
		if (nNum - i == 1) {
			PolygonLine p(nLen - nPart[i]);

			for (int j = 0; j < nLen - nPart[i]; j++) {
				Point pt;
				fileIn.read((char*)&pt.x, 8);
				fileIn.read((char*)&pt.y, 8);
				p.setPosition(pt, j);
			}

			vp.push_back(p);
		}

		else {
			PolygonLine p(nPart[i + 1] - nPart[i]);

			for (int j = 0; j < nPart[i + 1] - nPart[i]; j++) {
				Point pt;
				fileIn.read((char*)&pt.x, 8);
				fileIn.read((char*)&pt.y, 8);
				p.setPosition(pt, j);
			}

			vp.push_back(p);
		}
	}

	delete[]nPart;
}

bool CMFCApplicationView::ReadCoorWithEmpty(std::string strFile) {

	if (! v.empty())v.clear();
	if (!vl.empty())vl.clear();
	if (!vp.empty())vp.clear();

	ReadCoorWithoutEmpty(strFile);

	return true;
}

bool CMFCApplicationView::ReadCoorWithoutEmpty(std::string strFile) {

	std::ifstream in;
	in.open(strFile, std::ios::in | std::ios::binary);

	if (!in.is_open()) {
		MessageBoxA(NULL, "文件未正确打开!", "错误", 0);
		if (v.empty() && vl.empty() && vp.empty())exit(0);
		DrawPicture();
		return false;
	}

	ReadFileHead(in);
	while (in.peek() != EOF) {
		ReadShapeHead(in);
		int nType = ReadShapeType(in);
		if      (nType == 1)ReadPoint(in);
		else if (nType == 3)ReadLine(in);
		else if (nType == 5)ReadPolygonLine(in);
	}

	in.close();
	return true;
}

void CMFCApplicationView::OnDraw(CDC* pDC)
{
	CMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	DrawPicture(pDC);

}

// CMFCApplicationView 打印

BOOL CMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplicationView 诊断



#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationView 消息处理程序



void CMFCApplicationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isRDown == true) {
		Point temp = { point.x, point.y };
		RUp = caculateDrawToGeo(temp);
		Point lt = { min(RDown.x, RUp.x), min(RDown.y, RUp.y) };
		Point rb = { max(RDown.x, RUp.x), max(RDown.y, RUp.y) };
		Point LT = caculateGeoToDraw(lt);
		Point RB = caculateGeoToDraw(rb);

		/*以下为拉框的程序，但由于个人不太喜欢，没有采用
		* 没有使用FillRect(),而是直接使用MoveTo()与LineTo()绘制矩形
		*/

		//DrawPicture();

		//CDC* pDC = GetDC();

		//CPen pen(PS_DASH, 1, RGB(0, 0, 255));
		//pDC->SelectObject(&pen);

		//pDC->MoveTo(LT.x, LT.y);
		//pDC->LineTo(LT.x, RB.y);
		//pDC->LineTo(RB.x, RB.y);
		//pDC->LineTo(RB.x, LT.y);
		//pDC->LineTo(LT.x, LT.y);

		//ReleaseDC(pDC);
	}

	if (isFly == true && isLDown == true) {
		Point temp = { point.x, point.y };
		LUp = caculateDrawToGeo(temp);

		x  = x  - LUp.x + LDown.x;
		x0 = x0 - LUp.x + LDown.x;
		y  = y  - LUp.y + LDown.y;
		y0 = y0 - LUp.y + LDown.y;

		DrawPicture();
	}

	CView::OnMouseMove(nFlags, point);
}

void CMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isLDown = true;

	if (isFly == false) {
		DrawPicture();

		CDC* pDC = GetDC();
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		pDC->SelectObject(&pen);

		nPosition = -1;
		Point pt = { point.x, point.y };

		for (int i = 0; i < v.size(); i++) {
			Point pt0 = caculateGeoToDraw(v[i]);
			//Point pt0 = { (v[i].x - x0) * nClientRect.right  / (x - x0) * 0.8 + 0.1 * nClientRect.right,
			//			  (v[i].y - y0) * nClientRect.bottom / (y - y0) * 0.8 + 0.1 * nClientRect.bottom };
			if (distance(pt, pt0) < 5) {
				nPosition = i;
				break;
			}
		}

		if (nPosition < 0) {
			std::string posi;
			CString str;
			Point pTemp = { point.x, point.y };
			pTemp = caculateDrawToGeo(pTemp);
			str.Format(_T("(%.2lf, %.2lf)"), pTemp.x, pTemp.y);

			CDC* newDC = GetDC();
			CPen Pen(PS_SOLID, 2, RGB(255, 0, 255));
			newDC->SelectObject(&Pen);
			DrawPoint(pTemp, newDC);
			pDC->TextOutW(caculateGeoToDraw(pTemp).x + 5, caculateGeoToDraw(pTemp).y, str);

			dlgPoint->SetPointInformation(-1, 0, 0);
			dlgPoint->UpdateData(FALSE);

			ReleaseDC(newDC);
			ReleaseDC(pDC);

			return;
		}

		CPen markPen(PS_DASHDOT, 2, RGB(255, 0, 0));//选用红色画笔标记
		pDC->SelectObject(&markPen);
		DrawPoint(v[nPosition], pDC);

		std::string posi;
		CString str;
		str.Format(_T("(%.2lf, %.2lf)"), v[nPosition].x, v[nPosition].y);
		pDC->TextOutW(caculateGeoToDraw(v[nPosition]).x + 5, caculateGeoToDraw(v[nPosition]).y, str);


		dlgPoint->SetPointInformation(nPosition, v[nPosition].x, v[nPosition].y);
		dlgPoint->UpdateData(FALSE);

		ReleaseDC(pDC);
	}

	else {
		Point ptTemp = { point.x, point.y };
		LDown = caculateDrawToGeo(ptTemp);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CMFCApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isLDown = false;

	CView::OnLButtonUp(nFlags, point);
}

void CMFCApplicationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Point pt = { point.x, point.y };
	RDown = caculateDrawToGeo(pt);

	CDC* pDC = GetDC();
	CPen Pen(PS_SOLID, 2.5, RGB(0, 0, 255));
	pDC->SelectObject(&Pen);

	pDC->MoveTo(pt.x - 10, pt.y);
	pDC->LineTo(pt.x + 10, pt.y);
	pDC->MoveTo(pt.x, pt.y - 10);
	pDC->LineTo(pt.x, pt.y + 10);

	ReleaseDC(pDC);

	isRDown = true;

	CView::OnRButtonDown(nFlags, point);
}

void CMFCApplicationView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isRDown = false;

	Point temp = { point.x, point.y };
	RUp = caculateDrawToGeo(temp);
	x0 = min(RDown.x, RUp.x);
	x  = max(RDown.x, RUp.x);
	y0 = min(RDown.y, RUp.y);
	y  = max(RDown.y, RUp.y);

	CDC* pDC = GetDC();

	ClearDraw(pDC);
	pDC->SetTextColor(RGB(100, 100, 255));
	if (isFly == true)pDC->TextOutW(5, 0, L"已开启漫游状态");
	pDC->SetTextColor(RGB(0, 0, 0));

	if (!v.empty())DrawPoint(pDC);
	if (!vl.empty())DrawLine(pDC);
	if (!vp.empty())DrawPolygonLine(pDC);

	ReleaseDC(pDC);

	CView::OnRButtonUp(nFlags, point);
}


void CMFCApplicationView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	x  = xTemp;
	x0 = x0Temp;
	y  = yTemp;
	y0 = y0Temp;

	CDC* pDC = GetDC();
	ClearDraw();

	pDC->SetTextColor(RGB(100, 100, 255));
	if (isFly == true)pDC->TextOutW(5, 0, L"已开启漫游状态");
	pDC->SetTextColor(RGB(0, 0, 0));

	DrawPoint(pDC);
	DrawLine(pDC);
	DrawPolygonLine(pDC);

	ReleaseDC(pDC);

	CView::OnMButtonDown(nFlags, point);
}



void CMFCApplicationView::On3()
{
	// TODO: 在此添加命令处理程序代码
	shpFileOpen();

	DrawPicture();

	/*CDC* pDC = GetDC();

	oldBitmap.DeleteObject();

	memDC.CreateCompatibleDC(pDC);
    oldBitmap.CreateCompatibleBitmap(pDC, xTemp - x0Temp + 10, yTemp - y0Temp + 10);
	if (memDC.GetSafeHdc() != NULL) {
		memDC.SelectObject(&oldBitmap);

		if (!v.empty()) {
			for (int i = 0; i < v.size(); i++) {
				memDC.MoveTo(v[i].x - x0Temp - 5 + 5, v[i].y - y0Temp - 5 + 5);
				memDC.LineTo(v[i].x - x0Temp + 5 + 5, v[i].y - y0Temp + 5 + 5);
				memDC.MoveTo(v[i].x - x0Temp - 5 + 5, v[i].y - y0Temp + 5 + 5);
				memDC.LineTo(v[i].x - x0Temp + 5 + 5, v[i].y - y0Temp - 5 + 5);
			}
		}

		if (!vl.empty()) {
			for (int i = 0; i < vl.size(); i++) {
				memDC.MoveTo(vl[i].pt[0].x - xTemp + 5, vl[i].pt[0].y - yTemp + 5);
				for (int j = 1; j < vl[i].size; j++) {
					memDC.LineTo(vl[i].pt[j].x - xTemp + 5, vl[i].pt[j].y - yTemp + 5);
				}
			}
		}

		if (!vp.empty()) {
			for (int i = 0; i < vp.size(); i++) {
				memDC.MoveTo(vp[i].pt[0].x - xTemp + 5, vp[i].pt[0].y - yTemp + 5);
				for (int j = 1; j < vp[i].size; j++) {
					memDC.LineTo(vp[i].pt[j].x - xTemp + 5, vp[i].pt[j].y - yTemp + 5);
				}
			}
		}
	}
	memDC.DeleteDC();
	ReleaseDC(pDC);*/
}//导入文件

void CMFCApplicationView::On19()
{
	// TODO: 在此添加命令处理程序代码
	x  = xTemp;
	x0 = x0Temp;
	y  = yTemp;
	y0 = y0Temp;

	DrawPicture();

}//充值图形

void CMFCApplicationView::On32779()
{
	// TODO: 在此添加命令处理程序代码
	double Length = 0.05 * (x - x0);

	this->x  += Length;
	this->x0 += Length;

	DrawPicture();
}//左移

void CMFCApplicationView::On32780()
{
	// TODO: 在此添加命令处理程序代码
	double Length = 0.05 * (x - x0);

	this->x  -= Length;
	this->x0 -= Length;

	DrawPicture();
}//右移

void CMFCApplicationView::On32781()
{
	// TODO: 在此添加命令处理程序代码
	double Length = 0.05 * (y - y0);

	this->y  += Length;
	this->y0 += Length;

	DrawPicture();
}//上移

void CMFCApplicationView::On32782()
{
	// TODO: 在此添加命令处理程序代码
	double Length = 0.05 * (y - y0);

	this->y  -= Length;
	this->y0 -= Length;

	DrawPicture();
}//下移

void CMFCApplicationView::On32785()
{
	// TODO: 在此添加命令处理程序代码
	if (! v.empty())v.clear();
	if (!vl.empty())vl.clear();
	if (!vp.empty())vp.clear();

	DrawPicture();
}//清空图形

void CMFCApplicationView::On32786()
{
	// TODO: 在此添加命令处理程序代码
	CDialogAddPoint dlg;

	if (dlg.DoModal() == IDOK) {
		if (dlg.isOK == true) {
			Point pt = { dlg._x, dlg._y };
			v.push_back(pt);

			MessageBox(L"添加成功！");
			DrawPicture();
		}
	}
}//添加点

void CMFCApplicationView::On32787()
{
	// TODO: 在此添加命令处理程序代码
	if (nPosition != -1 && dlgPoint->isOK == true)DrawPicture();
	dlgPoint->ShowWindow(SW_SHOWNORMAL);
	//MessageBox(L"删除成功！");
	//ClearDraw();
}//操作点

void CMFCApplicationView::On32788()
{
	// TODO: 在此添加命令处理程序代码
	if (isFly == false)isFly = true;
	else isFly = false;
	DrawPicture();
}//漫游

void CMFCApplicationView::On32793()
{
	// TODO: 在此添加命令处理程序代码
	CDialogCenterPoint dlg;

	if (dlg.DoModal() == IDOK) {
		if (dlg.isOK == true) {

			double xLen = (x - x0) / 2;
			double yLen = (y - y0) / 2;

			x  = dlg.x + xLen;
			x0 = dlg.x - xLen;
			y  = dlg.y + yLen;
			y0 = dlg.y - yLen;

			DrawPicture();

			dlg.isOK = false;
			MessageBox(L"移动成功！");
		}
	}
}
