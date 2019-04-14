// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// GeoSymbolSysView.h : CGeoSymbolSysView ��Ľӿ�
//

#pragma once


class CGeoSymbolSysView : public CView
{
protected: // �������л�����
	CGeoSymbolSysView();
	DECLARE_DYNCREATE(CGeoSymbolSysView)

// ����
public:
	CGeoSymbolSysDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGeoSymbolSysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString GeoPath;
// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // GeoSymbolSysView.cpp �еĵ��԰汾
inline CGeoSymbolSysDoc* CGeoSymbolSysView::GetDocument() const
   { return reinterpret_cast<CGeoSymbolSysDoc*>(m_pDocument); }
#endif

