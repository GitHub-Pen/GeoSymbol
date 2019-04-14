// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// GeoSymbolSysView.h : CGeoSymbolSysView 类的接口
//

#pragma once


class CGeoSymbolSysView : public CView
{
protected: // 仅从序列化创建
	CGeoSymbolSysView();
	DECLARE_DYNCREATE(CGeoSymbolSysView)

// 特性
public:
	CGeoSymbolSysDoc* GetDocument() const;

// 操作
public:

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
	virtual ~CGeoSymbolSysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString GeoPath;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonFileNew();
	afx_msg void OnButtonFileOpen();
	afx_msg void OnButtonFileSave();
	afx_msg void OnButtonFileSaveas();
	afx_msg void OnButtonDispPan();
	afx_msg void OnButtonDispRefresh();
	afx_msg void OnButtonDispRestore();
	afx_msg void OnButtonDispSelect();
	afx_msg void OnButtonDispZoomin();
	afx_msg void OnButtonDispZoomout();
	afx_msg void OnButtonSymbolPntOne();
	afx_msg void OnButtonSymbolPntTwo();
	afx_msg void OnButtonSymbolPntThree();
	afx_msg void OnButtonSymbolPntFour();
	afx_msg void OnButtonSymbolPntFive();
	afx_msg void OnButtonSymbolLineOne();
	afx_msg void OnButtonSymbolLineTwo();
	afx_msg void OnButtonSymbolLineThree();
	afx_msg void OnButtonSymbolLineFour();
	afx_msg void OnButtonSymbolLineFive();
	afx_msg void OnUpdateButtonDispPan(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonDispRefresh(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonDispRestore(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonDispSelect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonDispZoomin(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonDispZoomout(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolPntOne(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolPntTwo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolPntThree(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolPntFour(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolPntFive(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolLineOne(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolLineTwo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolLineThree(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolLineFour(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSymbolLineFive(CCmdUI *pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // GeoSymbolSysView.cpp 中的调试版本
inline CGeoSymbolSysDoc* CGeoSymbolSysView::GetDocument() const
   { return reinterpret_cast<CGeoSymbolSysDoc*>(m_pDocument); }
#endif

