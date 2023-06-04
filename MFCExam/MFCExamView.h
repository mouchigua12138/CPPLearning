
// MFCExamView.h: CMFCExamView 类的接口
//

#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "CDialogPoint.h"
#include "CStudent.h"

class CMFCExamView : public CView
{
protected: // 仅从序列化创建
	CMFCExamView() noexcept;
	DECLARE_DYNCREATE(CMFCExamView)

// 特性
public:
	CMFCExamDoc* GetDocument() const;

// 变量
	std::vector<CStudent> v;

	double xMin,  xMax,  yMin,  yMax;
	double xMin0, xMax0, yMin0, yMax0;

	CDC           memDC;
	CBitmap       bitmap;
	CRect         nClientRect;
	CDialogPoint* dlgPoint;
	int           nSearch;

	bool isFly;
	bool isLDown;
	bool isRDown;

	Point flyFirst,  flyEnd;
	Point moveFirst, moveEnd;
	Point RFirst,    REnd;
// 操作
public:
	Point CaculateGeoToDraw(Point pt);
	Point CaculateDrawToGeo(Point pt);
	void ReadFile();
	void PrintTxt();
	void DrawPicture();
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
	virtual ~CMFCExamView();
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
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	

	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32776();
	
};

#ifndef _DEBUG  // MFCExamView.cpp 中的调试版本
inline CMFCExamDoc* CMFCExamView::GetDocument() const
   { return reinterpret_cast<CMFCExamDoc*>(m_pDocument); }
#endif

