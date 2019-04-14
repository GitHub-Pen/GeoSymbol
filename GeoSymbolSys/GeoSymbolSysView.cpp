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

// GeoSymbolSysView.cpp : CGeoSymbolSysView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GeoSymbolSys.h"
#endif

#include "GeoSymbolSysDoc.h"
#include "GeoSymbolSysView.h"
#include "MainFrm.h"
#include "GISWorkSpace.h"
#include "IGIS_GeoEleBase.h"
#include "GIS_GeoLine.h"
#include "GIS_GeoPoint.h"
#include <conio.h>
#include <iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeoSymbolSysView

IMPLEMENT_DYNCREATE(CGeoSymbolSysView, CView)

BEGIN_MESSAGE_MAP(CGeoSymbolSysView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGeoSymbolSysView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_FILE_NEW, &CGeoSymbolSysView::OnButtonFileNew)
	ON_COMMAND(ID_BUTTON_FILE_OPEN, &CGeoSymbolSysView::OnButtonFileOpen)
	ON_COMMAND(ID_BUTTON_FILE_SAVE, &CGeoSymbolSysView::OnButtonFileSave)
	ON_COMMAND(ID_BUTTON_FILE_SAVEAS, &CGeoSymbolSysView::OnButtonFileSaveas)
	ON_COMMAND(ID_BUTTON_DISP_PAN, &CGeoSymbolSysView::OnButtonDispPan)
	ON_COMMAND(ID_BUTTON_DISP_REFRESH, &CGeoSymbolSysView::OnButtonDispRefresh)
	ON_COMMAND(ID_BUTTON_DISP_RESTORE, &CGeoSymbolSysView::OnButtonDispRestore)
	ON_COMMAND(ID_BUTTON_DISP_ZOOMIN, &CGeoSymbolSysView::OnButtonDispZoomin)
	ON_COMMAND(ID_BUTTON_DISP_ZOOMOUT, &CGeoSymbolSysView::OnButtonDispZoomout)
	ON_COMMAND(ID_BUTTON_SYMBOL_PNT_ONE, &CGeoSymbolSysView::OnButtonSymbolPntOne)
	ON_COMMAND(ID_BUTTON_SYMBOL_PNT_TWO, &CGeoSymbolSysView::OnButtonSymbolPntTwo)
	ON_COMMAND(ID_BUTTON_SYMBOL_PNT_THREE, &CGeoSymbolSysView::OnButtonSymbolPntThree)
	ON_COMMAND(ID_BUTTON_SYMBOL_PNT_FOUR, &CGeoSymbolSysView::OnButtonSymbolPntFour)
	ON_COMMAND(ID_BUTTON_SYMBOL_PNT_FIVE, &CGeoSymbolSysView::OnButtonSymbolPntFive)
	ON_COMMAND(ID_BUTTON_SYMBOL_LINE_ONE, &CGeoSymbolSysView::OnButtonSymbolLineOne)
	ON_COMMAND(ID_BUTTON_SYMBOL_LINE_TWO, &CGeoSymbolSysView::OnButtonSymbolLineTwo)
	ON_COMMAND(ID_BUTTON_SYMBOL_LINE_THREE, &CGeoSymbolSysView::OnButtonSymbolLineThree)
	ON_COMMAND(ID_BUTTON_SYMBOL_LINE_FOUR, &CGeoSymbolSysView::OnButtonSymbolLineFour)
	ON_COMMAND(ID_BUTTON_SYMBOL_LINE_FIVE, &CGeoSymbolSysView::OnButtonSymbolLineFive)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISP_PAN, &CGeoSymbolSysView::OnUpdateButtonDispPan)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISP_REFRESH, &CGeoSymbolSysView::OnUpdateButtonDispRefresh)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISP_RESTORE, &CGeoSymbolSysView::OnUpdateButtonDispRestore)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISP_ZOOMIN, &CGeoSymbolSysView::OnUpdateButtonDispZoomin)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISP_ZOOMOUT, &CGeoSymbolSysView::OnUpdateButtonDispZoomout)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_PNT_ONE, &CGeoSymbolSysView::OnUpdateButtonSymbolPntOne)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_PNT_TWO, &CGeoSymbolSysView::OnUpdateButtonSymbolPntTwo)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_PNT_THREE, &CGeoSymbolSysView::OnUpdateButtonSymbolPntThree)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_PNT_FOUR, &CGeoSymbolSysView::OnUpdateButtonSymbolPntFour)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_PNT_FIVE, &CGeoSymbolSysView::OnUpdateButtonSymbolPntFive)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_LINE_ONE, &CGeoSymbolSysView::OnUpdateButtonSymbolLineOne)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_LINE_TWO, &CGeoSymbolSysView::OnUpdateButtonSymbolLineTwo)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_LINE_THREE, &CGeoSymbolSysView::OnUpdateButtonSymbolLineThree)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_LINE_FOUR, &CGeoSymbolSysView::OnUpdateButtonSymbolLineFour)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SYMBOL_LINE_FIVE, &CGeoSymbolSysView::OnUpdateButtonSymbolLineFive)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CGeoSymbolSysView ����/����

CGeoSymbolSysView::CGeoSymbolSysView()
{
	// TODO: �ڴ˴���ӹ������
	GeoPath="";
}

CGeoSymbolSysView::~CGeoSymbolSysView()
{
}

BOOL CGeoSymbolSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}


int CGeoSymbolSysView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CGISWorkSpace::BindView(this);
	return 0;
}


void CGeoSymbolSysView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CGISWorkSpace::OnSize(nType,cx,cy);
}

// CGeoSymbolSysView ����

void CGeoSymbolSysView::OnDraw(CDC* pDC)
{
	CGeoSymbolSysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CGISWorkSpace::DrawMap();
}


// CGeoSymbolSysView ��ӡ


void CGeoSymbolSysView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGeoSymbolSysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGeoSymbolSysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGeoSymbolSysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

BOOL CGeoSymbolSysView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGISWorkSpace::GetCurTool()->MouseWheel(nFlags,zDelta,pt);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CGeoSymbolSysView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGISWorkSpace::GetCurTool()->LButtonup(nFlags,point);
	CView::OnLButtonUp(nFlags, point);
}


void CGeoSymbolSysView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGISWorkSpace::GetCurTool()->LButtonDown(nFlags,point);
	CView::OnLButtonDown(nFlags, point);
}


void CGeoSymbolSysView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CGISWorkSpace::GetCurTool()->RButtonDown(nFlags,point);
	CView::OnRButtonDown(nFlags, point);
}


void CGeoSymbolSysView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	float x=0;float y=0;
	CGISWorkSpace::WndToGeo(point,x,y);
	CString coordStr="";
	coordStr.Format("��ǰ���꣺ x=%.3f,y=%.3f  ����ϵ����k=%4f",x,y,CGISWorkSpace::mapScale);
	CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();
	//_cprintf(coordStr+"\n");
	pFrame->UpdateStatusCoordStr(coordStr);
	
	CGISWorkSpace::GetCurTool()->MouseMove(nFlags,point);
	CView::OnMouseMove(nFlags, point);
}

void CGeoSymbolSysView::OnRButtonUp(UINT  nFlags , CPoint point)
{
	CGISWorkSpace::GetCurTool()->RButtonUp(nFlags,point);
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CGeoSymbolSysView::OnContextMenu(CWnd*  pWnd , CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGeoSymbolSysView ���

#ifdef _DEBUG
void CGeoSymbolSysView::AssertValid() const
{
	CView::AssertValid();
}

void CGeoSymbolSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeoSymbolSysDoc* CGeoSymbolSysView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeoSymbolSysDoc)));
	return (CGeoSymbolSysDoc*)m_pDocument;
}
#endif //_DEBUG


// CGeoSymbolSysView ��Ϣ�������


void CGeoSymbolSysView::OnButtonFileNew()
{
	// TODO: �ڴ���������������
	if (GeoPath!="")
	{
		if(IDYES==MessageBox("�Ƿ񱣴浱ǰ���ݣ�","�½��ļ�",MB_YESNO))
		{
			OnButtonFileSave();
		}
	}
	GeoPath="";
	CGISWorkSpace::ClearGeoData();
	this->Invalidate(TRUE);
}


void CGeoSymbolSysView::OnButtonFileOpen()
{
	// TODO: �ڴ���������������
	if (GeoPath!="")
	{
		OnButtonFileNew();
	}
	else
	{
		TCHAR szPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szPath);
		CFileDialog dlg(TRUE);
		dlg.m_ofn.lStructSize=sizeof(OPENFILENAME);
		dlg.m_ofn.lpstrTitle="Ҫ���ļ�";
		dlg.m_ofn.lpstrFilter="Ҫ���ļ�(*.geo)\0*.geo\0All File(*.*)\0*.*\0\0";
		dlg.m_ofn.lpstrInitialDir=szPath;
		if (dlg.DoModal()==IDCANCEL)return;
		GeoPath=dlg.GetPathName();
		CGISWorkSpace::ReadGeoElements(GeoPath);
	}
	CGISWorkSpace::Restore();
}


void CGeoSymbolSysView::OnButtonFileSave()
{
	// TODO: �ڴ���������������
	if (GeoPath=="")
	{
		OnButtonFileSaveas();
	}
	else
	{
		CGISWorkSpace::SaveGeoElements(GeoPath);
		MessageBox("���浽��"+GeoPath+"��·����");
	}
}


void CGeoSymbolSysView::OnButtonFileSaveas()
{
	// TODO: �ڴ���������������
	TCHAR szPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szPath);
	CFileDialog dlg(false);
	dlg.m_ofn.lStructSize=sizeof(OPENFILENAME);
	dlg.m_ofn.lpstrTitle="Ҫ���ļ�";
	dlg.m_ofn.lpstrFilter="Ҫ���ļ�(*.geo)\0*.geo\0\0";
	dlg.m_ofn.lpstrInitialDir=szPath;
	if (dlg.DoModal()==IDCANCEL)return;
	GeoPath=dlg.GetPathName();
	if(dlg.GetFileExt()!="geo")
	{
		GeoPath+=".geo";
	}
	CGISWorkSpace::SaveGeoElements(GeoPath);
}


void CGeoSymbolSysView::OnButtonDispPan()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentToolName="CGIS_ToolPan";
}


void CGeoSymbolSysView::OnButtonDispRefresh()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::DrawMap();
}


void CGeoSymbolSysView::OnButtonDispRestore()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::Restore();
}


void CGeoSymbolSysView::OnButtonDispSelect()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentToolName="CGIS_ToolSelect";
}


void CGeoSymbolSysView::OnButtonDispZoomin()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentToolName="CGIS_ToolZoomIn";
}


void CGeoSymbolSysView::OnButtonDispZoomout()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentToolName="CGIS_ToolZoomOut";
}


void CGeoSymbolSysView::OnButtonSymbolPntOne()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=1;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntTwo()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=2;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntThree()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=3;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntFour()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=4;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntFive()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=5;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolLineOne()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=6;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineTwo()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=7;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineThree()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=8;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineFour()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=9;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineFive()
{
	// TODO: �ڴ���������������
	CGISWorkSpace::currentSymId=10;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnUpdateButtonDispPan(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolPan")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonDispRefresh(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CGeoSymbolSysView::OnUpdateButtonDispRestore(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CGeoSymbolSysView::OnUpdateButtonDispSelect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolSelect")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonDispZoomin(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolZoomIn")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonDispZoomout(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolZoomOut")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntOne(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==1)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntTwo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==2)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntThree(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==3)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntFour(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==4)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntFive(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==5)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineOne(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==6)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineTwo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==7)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineThree(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==8)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineFour(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==9)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineFive(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==10)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}



