
// MFCApplicationView.h: CMFCApplicationView 类的接口
//

#pragma once

#include <iostream>
#include <vector>

#include "CDialogPoint.h"
#include "ShapeType.h"

bool ReadCoorWithEmpty(std::vector<Point>& v, std::string strFile);



class CMFCApplicationView : public CView
{
protected: // 仅从序列化创建
	CMFCApplicationView() noexcept;
	DECLARE_DYNCREATE(CMFCApplicationView)

// 特性
public:
	CMFCApplicationDoc* GetDocument() const;

// 操作
public:
	void ClearDraw();
	void ClearDraw(CDC* pDC);

	void DrawPoint(CDC* pDC);
	void DrawPoint(Point pt, CDC* pDC);
	void DeletePoint(Point pt, CDC* pDC);

	void DrawLine(CDC* pDC);
	void DrawLine(Line l, CDC* pDC);

	void DrawPolygonLine(CDC* pDC);
	void DrawPolygonLine(PolygonLine p, CDC* pDC);

	void DrawPicture();
	void DrawPicture(CDC* pDC);

	void shpFileOpen();

protected:
	Point caculateGeoToDraw(Point& pt);
	Point caculateDrawToGeo(Point& pt);

	void ReadFileHead(std::ifstream& fileIn);
	void ReadShapeHead(std::ifstream& fileIn);
	int  ReadShapeType(std::ifstream& fileIn);

	void ReadPoint(std::ifstream& fileIn);
	void ReadLine(std::ifstream& fileIn);
	void ReadPolygonLine(std::ifstream& fileIn);

	bool ReadCoorWithEmpty(std::string strFile);
    bool ReadCoorWithoutEmpty(std::string strFile);

	//void Flash();

//变量
protected:
	std::vector<Point>       v; //点向量
	std::vector<Line>        vl;//折线向量
	std::vector<PolygonLine> vp;//面向量

	CRect   nClientRect;   //视窗窗口
	CPen    BlackPen;      //默认黑笔
	CDC     memDC;         //画在内存上
	CDC     memDCRButton;
	CBitmap bitmap;
	CBitmap bitmapRButton;
	Point   pointTemp;

	double x,     x0,     y,     y0;
	double xTemp, x0Temp, yTemp, y0Temp;
	Point  LDown, LUp,    RDown, RUp;
	int    nPosition;

	bool isLDown;//左键是否按下
	bool isRDown;//右键是否按下
	bool isFly;  //是否漫游
	
	CDialogPoint* dlgPoint;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);


	afx_msg void On3();    //导入文件
	afx_msg void On19();   //重置图形
	afx_msg void On32779();//左移
	afx_msg void On32780();//右移
	afx_msg void On32781();//上移
	afx_msg void On32782();//下移
	afx_msg void On32785();//清空图形
	afx_msg void On32786();//添加点
	afx_msg void On32787();//操作点
	afx_msg void On32788();//漫游
	afx_msg void On32793();//转到中心点
};

#ifndef _DEBUG  // MFCApplicationView.cpp 中的调试版本
inline CMFCApplicationDoc* CMFCApplicationView::GetDocument() const
   { return reinterpret_cast<CMFCApplicationDoc*>(m_pDocument); }
#endif

