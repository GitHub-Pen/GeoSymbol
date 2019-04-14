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

// GeoSymbolSysView.cpp : CGeoSymbolSysView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CGeoSymbolSysView 构造/析构

CGeoSymbolSysView::CGeoSymbolSysView()
{
	// TODO: 在此处添加构造代码
	GeoPath="";
}

CGeoSymbolSysView::~CGeoSymbolSysView()
{
}

BOOL CGeoSymbolSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


int CGeoSymbolSysView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CGISWorkSpace::BindView(this);
	return 0;
}


void CGeoSymbolSysView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CGISWorkSpace::OnSize(nType,cx,cy);
}

// CGeoSymbolSysView 绘制

void CGeoSymbolSysView::OnDraw(CDC* pDC)
{
	CGeoSymbolSysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CGISWorkSpace::DrawMap();
}


// CGeoSymbolSysView 打印


void CGeoSymbolSysView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGeoSymbolSysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGeoSymbolSysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGeoSymbolSysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

BOOL CGeoSymbolSysView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGISWorkSpace::GetCurTool()->MouseWheel(nFlags,zDelta,pt);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CGeoSymbolSysView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGISWorkSpace::GetCurTool()->LButtonup(nFlags,point);
	CView::OnLButtonUp(nFlags, point);
}


void CGeoSymbolSysView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGISWorkSpace::GetCurTool()->LButtonDown(nFlags,point);
	CView::OnLButtonDown(nFlags, point);
}


void CGeoSymbolSysView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CGISWorkSpace::GetCurTool()->RButtonDown(nFlags,point);
	CView::OnRButtonDown(nFlags, point);
}


void CGeoSymbolSysView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	float x=0;float y=0;
	CGISWorkSpace::WndToGeo(point,x,y);
	CString coordStr="";
	coordStr.Format("当前坐标： x=%.3f,y=%.3f  比例系数：k=%4f",x,y,CGISWorkSpace::mapScale);
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


// CGeoSymbolSysView 诊断

#ifdef _DEBUG
void CGeoSymbolSysView::AssertValid() const
{
	CView::AssertValid();
}

void CGeoSymbolSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeoSymbolSysDoc* CGeoSymbolSysView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeoSymbolSysDoc)));
	return (CGeoSymbolSysDoc*)m_pDocument;
}
#endif //_DEBUG


// CGeoSymbolSysView 消息处理程序


void CGeoSymbolSysView::OnButtonFileNew()
{
	// TODO: 在此添加命令处理程序代码
	if (GeoPath!="")
	{
		if(IDYES==MessageBox("是否保存当前内容？","新建文件",MB_YESNO))
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
	// TODO: 在此添加命令处理程序代码
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
		dlg.m_ofn.lpstrTitle="要素文件";
		dlg.m_ofn.lpstrFilter="要素文件(*.geo)\0*.geo\0All File(*.*)\0*.*\0\0";
		dlg.m_ofn.lpstrInitialDir=szPath;
		if (dlg.DoModal()==IDCANCEL)return;
		GeoPath=dlg.GetPathName();
		CGISWorkSpace::ReadGeoElements(GeoPath);
	}
	CGISWorkSpace::Restore();
}


void CGeoSymbolSysView::OnButtonFileSave()
{
	// TODO: 在此添加命令处理程序代码
	if (GeoPath=="")
	{
		OnButtonFileSaveas();
	}
	else
	{
		CGISWorkSpace::SaveGeoElements(GeoPath);
		MessageBox("保存到（"+GeoPath+"）路径下");
	}
}


void CGeoSymbolSysView::OnButtonFileSaveas()
{
	// TODO: 在此添加命令处理程序代码
	TCHAR szPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szPath);
	CFileDialog dlg(false);
	dlg.m_ofn.lStructSize=sizeof(OPENFILENAME);
	dlg.m_ofn.lpstrTitle="要素文件";
	dlg.m_ofn.lpstrFilter="要素文件(*.geo)\0*.geo\0\0";
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
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentToolName="CGIS_ToolPan";
}


void CGeoSymbolSysView::OnButtonDispRefresh()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::DrawMap();
}


void CGeoSymbolSysView::OnButtonDispRestore()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::Restore();
}


void CGeoSymbolSysView::OnButtonDispSelect()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentToolName="CGIS_ToolSelect";
}


void CGeoSymbolSysView::OnButtonDispZoomin()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentToolName="CGIS_ToolZoomIn";
}


void CGeoSymbolSysView::OnButtonDispZoomout()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentToolName="CGIS_ToolZoomOut";
}


void CGeoSymbolSysView::OnButtonSymbolPntOne()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=1;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntTwo()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=2;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntThree()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=3;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntFour()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=4;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolPntFive()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=5;
	CGISWorkSpace::currentToolName="CGIS_ToolAddPnt";
}


void CGeoSymbolSysView::OnButtonSymbolLineOne()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=6;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineTwo()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=7;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineThree()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=8;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineFour()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=9;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnButtonSymbolLineFive()
{
	// TODO: 在此添加命令处理程序代码
	CGISWorkSpace::currentSymId=10;
	CGISWorkSpace::currentToolName="CGIS_ToolAddLine";
}


void CGeoSymbolSysView::OnUpdateButtonDispPan(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolPan")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonDispRefresh(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CGeoSymbolSysView::OnUpdateButtonDispRestore(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CGeoSymbolSysView::OnUpdateButtonDispSelect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolSelect")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonDispZoomin(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolZoomIn")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonDispZoomout(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolZoomOut")
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntOne(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==1)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntTwo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==2)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntThree(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==3)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntFour(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==4)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolPntFive(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddPnt"&&CGISWorkSpace::currentSymId==5)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineOne(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==6)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineTwo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==7)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineThree(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==8)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineFour(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==9)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}


void CGeoSymbolSysView::OnUpdateButtonSymbolLineFive(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (CGISWorkSpace::currentToolName=="CGIS_ToolAddLine"&&CGISWorkSpace::currentSymId==10)
	{
		pCmdUI->SetCheck(1);
	}
	else pCmdUI->SetCheck(0);
}



