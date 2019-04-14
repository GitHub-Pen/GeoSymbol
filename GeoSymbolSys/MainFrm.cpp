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

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "GeoSymbolSys.h"

#include "MainFrm.h"
#include "GISWorkSpace.h"
#include "GIS_SymPoint.h"
#include "GIS_SymLine.h"
#include "GIS_SymEleArc.h"
#include "GIS_SymEleCircle.h"
#include "GIS_SymElePloy.h"
#include "GIS_SymEleRect.h"
#include "GIS_SymEleSegment.h"
#include "GIS_GeoPoint.h"
#include "GIS_GeoLine.h"

#include "IGIS_ToolBase.h"
#include "GIS_ToolAddLine.h"
#include "GIS_ToolAddPnt.h"
#include "GIS_ToolPan.h"
#include "GIS_ToolSelect.h"
#include "GIS_ToolZoomIn.h"
#include "GIS_ToolZoomOut.h"
#include <conio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_AQUA);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1="当前坐标为：x=0.0000,y=0.0000  比例系数：k=1.0000";
	//CString strTitlePane2;
	//bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	//ASSERT(bNameValid);
	//bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	//ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane1, TRUE), strTitlePane1);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	InitPntSymbol();
	InitLineSymbol();
	InitGeoElement();
	InitTools();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

void CMainFrame::InitPntSymbol()
{
	int symId=0;
	/////////////////////////////////////////////////////////////////////////
	//符号一 烟囱
	symId++;
	CGIS_SymPoint * pSymPnt11=new CGIS_SymPoint();
	pSymPnt11->m_SymID=symId;
	pSymPnt11->m_SymName="烟囱";
	CGIS_SymEleSegment *pSeg11=new CGIS_SymEleSegment();
	pSeg11->m_PntStart=CPoint(-16,0);
	pSeg11->m_PntEnd=CPoint(16,0);
	pSeg11->m_LineWidth=2;
	pSeg11->m_SegColor=RGB(0,0,0);
	pSeg11->m_IsCutByX=false;
	pSymPnt11->m_SymElement.push_back(pSeg11);
	//CGIS_SymEleSegment *pSeg12=new CGIS_SymEleSegment();
	//pSeg12->m_PntStart=CPoint(-10,0);
	//pSeg12->m_PntEnd=CPoint(0,-40);
	//pSeg12->m_LineWidth=2;
	//pSeg12->m_SegColor=RGB(0,0,0);
	//pSeg12->m_IsCutByX=false;
	//pSymPnt11->m_SymElement.push_back(pSeg12);
	//CGIS_SymEleSegment *pSeg13=new CGIS_SymEleSegment();
	//pSeg13->m_PntStart=CPoint(10,0);
	//pSeg13->m_PntEnd=CPoint(0,-40);
	//pSeg13->m_LineWidth=2;
	//pSeg13->m_SegColor=RGB(0,0,0);
	//pSeg13->m_IsCutByX=false;
	//pSymPnt11->m_SymElement.push_back(pSeg13);
	CGIS_SymElePloy *pPloy11=new CGIS_SymElePloy();
	pPloy11->m_PathPos.push_back(CPoint(10,0));
	pPloy11->m_PathPos.push_back(CPoint(0,-40));
	pPloy11->m_PathPos.push_back(CPoint(-10,0));
	pPloy11->m_IsFill=true;
	pPloy11->m_LineWidth=2;
	pPloy11->m_EdgeColor=RGB(0,0,0);
	pPloy11->m_IsCutByX=false;
	pSymPnt11->m_SymElement.push_back(pPloy11);
	CGIS_SymEleArc *pArc11=new CGIS_SymEleArc();
	pArc11->m_CenPos=CPoint(3,-40);
	pArc11->r=3;
	pArc11->m_StartAngle=0;
	pArc11->m_SweepAngle=180;
	pArc11->m_IsFill=false;
	pArc11->m_LineWidth=2;
	pArc11->m_EdgeColor=RGB(0,0,0);
	pArc11->m_IsCutByX=false;
	pSymPnt11->m_SymElement.push_back(pArc11);
	CGIS_SymEleArc *pArc12=new CGIS_SymEleArc();
	pArc12->m_CenPos=CPoint(9,-40);
	pArc12->r=3;
	pArc12->m_StartAngle=-180;
	pArc12->m_SweepAngle=180;
	pArc12->m_IsFill=false;
	pArc12->m_LineWidth=2;
	pArc12->m_EdgeColor=RGB(0,0,0);
	pArc12->m_IsCutByX=false;
	pSymPnt11->m_SymElement.push_back(pArc12);
	CGISWorkSpace::SymbolList.push_back(pSymPnt11);


	/////////////////////////////////////////////////////////////////////////
	//符号二 塔
	symId++;
	CGIS_SymPoint * pSymPnt21=new CGIS_SymPoint();
	pSymPnt21->m_SymID=symId;
	pSymPnt21->m_SymName="塔";
	CGIS_SymEleSegment *pSeg21=new CGIS_SymEleSegment();
	pSeg21->m_PntStart=CPoint(-16,0);
	pSeg21->m_PntEnd=CPoint(16,0);
	pSeg21->m_LineWidth=2;
	pSeg21->m_SegColor=RGB(0,0,0);
	pSeg21->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg21);
	/*CGIS_SymEleSegment *pSeg22=new CGIS_SymEleSegment();
	pSeg22->m_PntStart=CPoint(-10,0);
	pSeg22->m_PntEnd=CPoint(0,-40);
	pSeg22->m_LineWidth=2;
	pSeg22->m_SegColor=RGB(0,0,0);
	pSeg22->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg22);
	CGIS_SymEleSegment *pSeg23=new CGIS_SymEleSegment();
	pSeg23->m_PntStart=CPoint(10,0);
	pSeg23->m_PntEnd=CPoint(0,-40);
	pSeg23->m_LineWidth=2;
	pSeg23->m_SegColor=RGB(0,0,0);
	pSeg23->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg23);*/
	CGIS_SymElePloy *pPloy21=new CGIS_SymElePloy();
	pPloy21->m_PathPos.push_back(CPoint(10,0));
	pPloy21->m_PathPos.push_back(CPoint(0,-40));
	pPloy21->m_PathPos.push_back(CPoint(-10,0));
	pPloy21->m_IsFill=true;
	pPloy21->m_LineWidth=2;
	pPloy21->m_EdgeColor=RGB(0,0,0);
	pPloy21->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pPloy21);
	CGIS_SymEleSegment *pSeg24=new CGIS_SymEleSegment();
	pSeg24->m_PntStart=CPoint(-14,-8);
	pSeg24->m_PntEnd=CPoint(-8,-8);
	pSeg24->m_LineWidth=2;
	pSeg24->m_SegColor=RGB(0,0,0);
	pSeg24->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg24);
	CGIS_SymEleSegment *pSeg25=new CGIS_SymEleSegment();
	pSeg25->m_PntStart=CPoint(8,-8);
	pSeg25->m_PntEnd=CPoint(14,-8);
	pSeg25->m_LineWidth=2;
	pSeg25->m_SegColor=RGB(0,0,0);
	pSeg25->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg25);
	CGIS_SymEleSegment *pSeg26=new CGIS_SymEleSegment();
	pSeg26->m_PntStart=CPoint(-12,-16);
	pSeg26->m_PntEnd=CPoint(-6,-16);
	pSeg26->m_LineWidth=2;
	pSeg26->m_SegColor=RGB(0,0,0);
	pSeg26->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg26);
	CGIS_SymEleSegment *pSeg27=new CGIS_SymEleSegment();
	pSeg27->m_PntStart=CPoint(12,-16);
	pSeg27->m_PntEnd=CPoint(6,-16);
	pSeg27->m_LineWidth=2;
	pSeg27->m_SegColor=RGB(0,0,0);
	pSeg27->m_IsCutByX=false;
	pSymPnt21->m_SymElement.push_back(pSeg27);
	CGISWorkSpace::SymbolList.push_back(pSymPnt21);

	/////////////////////////////////////////////////////////////////////////
	//符号三 省会
	symId++;
	CGIS_SymPoint * pSymPnt31=new CGIS_SymPoint();
	pSymPnt31->m_SymID=symId;
	pSymPnt31->m_SymName="省会";
	CGIS_SymEleCircle *pCircle31=new CGIS_SymEleCircle();
	pCircle31->m_CenPos=CPoint(0,0);
	pCircle31->r=6;
	pCircle31->m_IsFill=true;
	pCircle31->m_LineWidth=2;
	pCircle31->m_FillColor=RGB(0,0,0);
	pCircle31->m_IsCutByX=false;
	pSymPnt31->m_SymElement.push_back(pCircle31);
	CGIS_SymEleCircle *pCircle32=new CGIS_SymEleCircle();
	pCircle32->m_CenPos=CPoint(0,0);
	pCircle32->r=12;
	pCircle32->m_IsFill=false;
	pCircle32->m_LineWidth=2;
	pCircle32->m_EdgeColor=RGB(0,0,0);
	pCircle32->m_IsCutByX=false;
	pSymPnt31->m_SymElement.push_back(pCircle32);
	CGIS_SymEleCircle *pCircle33=new CGIS_SymEleCircle();
	pCircle33->m_CenPos=CPoint(0,0);
	pCircle33->r=20;
	pCircle33->m_IsFill=false;
	pCircle33->m_LineWidth=2;
	pCircle33->m_EdgeColor=RGB(0,0,0);
	pCircle33->m_IsCutByX=false;
	pSymPnt31->m_SymElement.push_back(pCircle33);
	CGISWorkSpace::SymbolList.push_back(pSymPnt31);

	/////////////////////////////////////////////////////////////////////////
	//符号四 控制点
	symId++;
	CGIS_SymPoint * pSymPnt41=new CGIS_SymPoint();
	pSymPnt41->m_SymID=symId;
	pSymPnt41->m_SymName="控制点";
	CGIS_SymElePloy *pPloy41=new CGIS_SymElePloy();
	float tmpValue=20/1.732f;
	pPloy41->m_PathPos.push_back(CPoint(int(-20),int(tmpValue+0.5)));
	pPloy41->m_PathPos.push_back(CPoint(int(20),int(tmpValue+0.5)));
	pPloy41->m_PathPos.push_back(CPoint(int(0),int(-tmpValue*2+0.5)));
	pPloy41->m_IsFill=false;
	pPloy41->m_LineWidth=2;
	pPloy41->m_EdgeColor=RGB(0,0,0);
	pPloy41->m_IsCutByX=false;
	pSymPnt41->m_SymElement.push_back(pPloy41);
	CGIS_SymEleCircle *pCircle42=new CGIS_SymEleCircle();
	pCircle42->m_CenPos=CPoint(0,0);
	pCircle42->r=4;
	pCircle42->m_IsFill=true;
	pCircle42->m_LineWidth=2;
	pCircle42->m_FillColor=RGB(0,0,0);
	pCircle42->m_IsCutByX=false;
	pSymPnt41->m_SymElement.push_back(pCircle42);
	CGISWorkSpace::SymbolList.push_back(pSymPnt41);

	/////////////////////////////////////////////////////////////////////////
	//符号五 风车
	symId++;
	CGIS_SymPoint * pSymPnt51=new CGIS_SymPoint();
	pSymPnt51->m_SymID=symId;
	pSymPnt51->m_SymName="风车";
	CGIS_SymElePloy *pPloy51=new CGIS_SymElePloy();
	pPloy51->m_PathPos.push_back(CPoint(-8,-8));
	pPloy51->m_PathPos.push_back(CPoint(8,-8));
	pPloy51->m_PathPos.push_back(CPoint(8,8));
	pPloy51->m_PathPos.push_back(CPoint(-8,8));
	pPloy51->m_IsFill=true;
	pPloy51->m_LineWidth=2;
	pPloy51->m_EdgeColor=RGB(0,0,0);
	pPloy51->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pPloy51);
	tmpValue=8+12*sin(45*3.141592653f/180)+0.5f;
	CGIS_SymEleSegment *pSeg51=new CGIS_SymEleSegment();
	pSeg51->m_PntStart=CPoint(-8,-8);
	pSeg51->m_PntEnd=CPoint(int(-tmpValue),int(-tmpValue));
	pSeg51->m_LineWidth=2;
	pSeg51->m_SegColor=RGB(0,0,0);
	pSeg51->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg51);
	CGIS_SymEleSegment *pSeg52=new CGIS_SymEleSegment();
	pSeg52->m_PntStart=CPoint(8,-8);
	pSeg52->m_PntEnd=CPoint(int(tmpValue),int(-tmpValue));
	pSeg52->m_LineWidth=2;
	pSeg52->m_SegColor=RGB(0,0,0);
	pSeg52->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg52);
	CGIS_SymEleSegment *pSeg53=new CGIS_SymEleSegment();
	pSeg53->m_PntStart=CPoint(8,8);
	pSeg53->m_PntEnd=CPoint(int(tmpValue),int(tmpValue));
	pSeg53->m_LineWidth=2;
	pSeg53->m_SegColor=RGB(0,0,0);
	pSeg53->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg53);
	CGIS_SymEleSegment *pSeg54=new CGIS_SymEleSegment();
	pSeg54->m_PntStart=CPoint(-8,8);
	pSeg54->m_PntEnd=CPoint(int(-tmpValue),int(tmpValue));
	pSeg54->m_LineWidth=2;
	pSeg54->m_SegColor=RGB(0,0,0);
	pSeg54->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg54);
	float tmpValue1=8+12*sin(45*3.141592653f/180)-6*sin(15*3.141592653f/180)+0.5f;
	float tmpValue2=8+12*sin(45*3.141592653f/180)-6*cos(15*3.141592653f/180)+0.5f;
	CGIS_SymEleSegment *pSeg55=new CGIS_SymEleSegment();
	pSeg55->m_PntStart=CPoint(int(tmpValue1),int(tmpValue2));
	pSeg55->m_PntEnd=CPoint(int(tmpValue),int(tmpValue));
	pSeg55->m_LineWidth=2;
	pSeg55->m_SegColor=RGB(0,0,0);
	pSeg55->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg55);
	CGIS_SymEleSegment *pSeg56=new CGIS_SymEleSegment();
	pSeg56->m_PntStart=CPoint(int(tmpValue2),int(tmpValue1));
	pSeg56->m_PntEnd=CPoint(int(tmpValue),int(tmpValue));
	pSeg56->m_LineWidth=2;
	pSeg56->m_SegColor=RGB(0,0,0);
	pSeg56->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg56);
	CGIS_SymEleSegment *pSeg57=new CGIS_SymEleSegment();
	pSeg57->m_PntStart=CPoint(int(-tmpValue1),int(tmpValue2));
	pSeg57->m_PntEnd=CPoint(int(-tmpValue),int(tmpValue));
	pSeg57->m_LineWidth=2;
	pSeg57->m_SegColor=RGB(0,0,0);
	pSeg57->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg57);
	CGIS_SymEleSegment *pSeg58=new CGIS_SymEleSegment();
	pSeg58->m_PntStart=CPoint(int(-tmpValue2),int(tmpValue1));
	pSeg58->m_PntEnd=CPoint(int(-tmpValue),int(tmpValue));
	pSeg58->m_LineWidth=2;
	pSeg58->m_SegColor=RGB(0,0,0);
	pSeg58->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg58);
	CGIS_SymEleSegment *pSeg59=new CGIS_SymEleSegment();
	pSeg59->m_PntStart=CPoint(int(-tmpValue1),int(-tmpValue2));
	pSeg59->m_PntEnd=CPoint(int(-tmpValue),int(-tmpValue));
	pSeg59->m_LineWidth=2;
	pSeg59->m_SegColor=RGB(0,0,0);
	pSeg59->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg59);
	CGIS_SymEleSegment *pSeg510=new CGIS_SymEleSegment();
	pSeg510->m_PntStart=CPoint(int(-tmpValue2),int(-tmpValue1));
	pSeg510->m_PntEnd=CPoint(int(-tmpValue),int(-tmpValue));
	pSeg510->m_LineWidth=2;
	pSeg510->m_SegColor=RGB(0,0,0);
	pSeg510->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg510);
	CGIS_SymEleSegment *pSeg511=new CGIS_SymEleSegment();
	pSeg511->m_PntStart=CPoint(int(tmpValue1),int(-tmpValue2));
	pSeg511->m_PntEnd=CPoint(int(tmpValue),int(-tmpValue));
	pSeg511->m_LineWidth=2;
	pSeg511->m_SegColor=RGB(0,0,0);
	pSeg511->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg511);
	CGIS_SymEleSegment *pSeg512=new CGIS_SymEleSegment();
	pSeg512->m_PntStart=CPoint(int(tmpValue2),int(-tmpValue1));
	pSeg512->m_PntEnd=CPoint(int(tmpValue),int(-tmpValue));
	pSeg512->m_LineWidth=2;
	pSeg512->m_SegColor=RGB(0,0,0);
	pSeg512->m_IsCutByX=false;
	pSymPnt51->m_SymElement.push_back(pSeg512);
	CGISWorkSpace::SymbolList.push_back(pSymPnt51);
}

void CMainFrame::InitLineSymbol()
{
	int symId=5;
	float sysK=0.5;
	/////////////////////////////////////////////////////////////////////////
	//符号六 乡村路
	symId++;
	CGIS_SymLine * pSymLine11=new CGIS_SymLine();
	pSymLine11->m_SymID=symId;
	pSymLine11->m_SymName="乡村路";
	pSymLine11->m_UnitX=int(180*sysK);
	CGIS_SymEleSegment *pSeg11=new CGIS_SymEleSegment();
	pSeg11->m_PntStart=CPoint(int(0*sysK),int(-7*sysK));
	pSeg11->m_PntEnd=CPoint(int(160*sysK),int(-7*sysK));
	pSeg11->m_LineWidth=2;
	pSeg11->m_SegColor=RGB(0,0,0);
	pSeg11->m_IsCutByX=true;
	pSeg11->m_UnitX=pSymLine11->m_UnitX;
	pSymLine11->m_SymElement.push_back(pSeg11);
	CGIS_SymEleSegment *pSeg12=new CGIS_SymEleSegment();
	pSeg12->m_PntStart=CPoint(int(0*sysK),int(7*sysK));
	pSeg12->m_PntEnd=CPoint(int(160*sysK),int(7*sysK));
	pSeg12->m_LineWidth=2;
	pSeg12->m_SegColor=RGB(0,0,0);
	pSeg12->m_IsCutByX=true;
	pSeg12->m_UnitX=pSymLine11->m_UnitX;
	pSymLine11->m_SymElement.push_back(pSeg12);
	CGISWorkSpace::SymbolList.push_back(pSymLine11);

	/////////////////////////////////////////////////////////////////////////
	//符号七 公路
	symId++;
	CGIS_SymLine * pSymLine21=new CGIS_SymLine();
	pSymLine21->m_SymID=symId;
	pSymLine21->m_SymName="公路";
	pSymLine21->m_UnitX=int(100*sysK);//100;
	CGIS_SymEleSegment *pSeg21=new CGIS_SymEleSegment();
	pSeg21->m_PntStart=CPoint(int(0*sysK),int(-7*sysK));//CPoint(0,-7);
	pSeg21->m_PntEnd=CPoint(int(100*sysK),int(-7*sysK));//CPoint(100,-7);
	pSeg21->m_LineWidth=2;
	pSeg21->m_SegColor=RGB(0,0,0);
	pSeg21->m_IsCutByX=true;
	pSeg21->m_UnitX=pSymLine21->m_UnitX;
	pSymLine21->m_SymElement.push_back(pSeg21);
	CGIS_SymEleSegment *pSeg22=new CGIS_SymEleSegment();
	pSeg22->m_PntStart=CPoint(int(0*sysK),int(7*sysK));//CPoint(0,7);
	pSeg22->m_PntEnd=CPoint(int(100*sysK),int(7*sysK));//CPoint(100,7);
	pSeg22->m_LineWidth=2;
	pSeg22->m_SegColor=RGB(0,0,0);
	pSeg22->m_IsCutByX=true;
	pSeg22->m_UnitX=pSymLine21->m_UnitX;
	pSymLine21->m_SymElement.push_back(pSeg22);
	CGISWorkSpace::SymbolList.push_back(pSymLine21);

	/////////////////////////////////////////////////////////////////////////
	//符号八 铁路
	symId++;
	CGIS_SymLine * pSymLine31=new CGIS_SymLine();
	pSymLine31->m_SymID=symId;
	pSymLine31->m_SymName="铁路";
	pSymLine31->m_UnitX=int(240*sysK);//
	CGIS_SymEleRect *pRect31=new CGIS_SymEleRect();
	pRect31->m_LeftUp=CPoint(int(0*sysK),int(-6*sysK));//CPoint(0,-6);
	pRect31->m_RightDown=CPoint(int(120*sysK),int(6*sysK));//CPoint(120,6);
	pRect31->m_LineWidth=2;
	pRect31->m_FillColor=RGB(0,0,0);
	pRect31->m_EdgeColor=RGB(0,0,0);
	pRect31->m_IsFill=true;
	pRect31->m_IsCutByX=true;
	pRect31->m_UnitX=pSymLine31->m_UnitX;
	pSymLine31->m_SymElement.push_back(pRect31);
	CGIS_SymEleRect *pRect32=new CGIS_SymEleRect();
	pRect32->m_LeftUp=CPoint(int(120*sysK),int(-6*sysK));//CPoint(120,-6);
	pRect32->m_RightDown=CPoint(int(240*sysK),int(6*sysK));//CPoint(240,6);
	pRect32->m_LineWidth=2;
	pRect32->m_FillColor=RGB(255,255,255);
	pRect32->m_EdgeColor=RGB(0,0,0);
	pRect32->m_IsFill=true;
	pRect32->m_IsCutByX=true;
	pRect32->m_UnitX=pSymLine31->m_UnitX;
	pSymLine31->m_SymElement.push_back(pRect32);
	CGISWorkSpace::SymbolList.push_back(pSymLine31);

	/////////////////////////////////////////////////////////////////////////
	//符号九 高压线
	symId++;
	CGIS_SymLine * pSymLine41=new CGIS_SymLine();
	pSymLine41->m_SymID=symId;
	pSymLine41->m_SymName="高压线";
	pSymLine41->m_UnitX=int(180*sysK);//180;
	CGIS_SymEleSegment *pSeg41=new CGIS_SymEleSegment();
	pSeg41->m_PntStart=CPoint(int(0*sysK),int(0*sysK));//CPoint(0,0);
	pSeg41->m_PntEnd=CPoint(int(180*sysK),int(0*sysK));//CPoint(180,0);
	pSeg41->m_LineWidth=3;
	pSeg41->m_SegColor=RGB(0,0,0);
	pSeg41->m_IsCutByX=true;
	pSeg41->m_UnitX=pSymLine41->m_UnitX;
	pSymLine41->m_SymElement.push_back(pSeg41);
	CGIS_SymEleSegment *pSeg42=new CGIS_SymEleSegment();
	pSeg42->m_PntStart=CPoint(int(10*sysK),int(-20*sysK));//CPoint(10,-20);
	pSeg42->m_PntEnd=CPoint(int(10*sysK),int(20*sysK));//CPoint(10,20);
	pSeg42->m_LineWidth=2;
	pSeg42->m_SegColor=RGB(0,0,0);
	pSeg42->m_IsCutByX=true;
	pSeg42->m_UnitX=pSymLine41->m_UnitX;
	pSymLine41->m_SymElement.push_back(pSeg42);
	CGIS_SymEleSegment *pSeg43=new CGIS_SymEleSegment();
	pSeg43->m_PntStart=CPoint(int(170*sysK),int(-20*sysK));//CPoint(170,-20);
	pSeg43->m_PntEnd=CPoint(int(170*sysK),int(20*sysK));//CPoint(170,20);
	pSeg43->m_LineWidth=2;
	pSeg43->m_SegColor=RGB(0,0,0);
	pSeg43->m_IsCutByX=true;
	pSeg43->m_UnitX=pSymLine41->m_UnitX;
	pSymLine41->m_SymElement.push_back(pSeg43);
	CGISWorkSpace::SymbolList.push_back(pSymLine41);

	/////////////////////////////////////////////////////////////////////////
	//符号十 国界
	symId++;
	CGIS_SymLine * pSymLine51=new CGIS_SymLine();
	pSymLine51->m_SymID=symId;
	pSymLine51->m_SymName="国界";
	pSymLine51->m_UnitX=int(100*sysK);//100;
	CGIS_SymEleSegment *pSeg51=new CGIS_SymEleSegment();
	pSeg51->m_PntStart=CPoint(int(0*sysK),int(0*sysK));//CPoint(0,0);
	pSeg51->m_PntEnd=CPoint(int(80*sysK),int(0*sysK));//CPoint(80,0);
	pSeg51->m_LineWidth=4;
	pSeg51->m_SegColor=RGB(0,0,0);
	pSeg51->m_IsCutByX=true;
	pSeg51->m_UnitX=pSymLine51->m_UnitX;
	pSymLine51->m_SymElement.push_back(pSeg51);
	CGIS_SymEleSegment *pSeg52=new CGIS_SymEleSegment();
	pSeg52->m_PntStart=CPoint(int(0*sysK),int(-18*sysK));//CPoint(0,-18);
	pSeg52->m_PntEnd=CPoint(int(0*sysK),int(18*sysK));//CPoint(0,18);
	pSeg52->m_LineWidth=2;
	pSeg52->m_SegColor=RGB(0,0,0);
	pSeg52->m_IsCutByX=true;
	pSeg52->m_UnitX=pSymLine51->m_UnitX;
	pSymLine51->m_SymElement.push_back(pSeg52);
	CGIS_SymEleSegment *pSeg53=new CGIS_SymEleSegment();
	pSeg53->m_PntStart=CPoint(int(80*sysK),int(-18*sysK));//CPoint(80,-18);
	pSeg53->m_PntEnd=CPoint(int(80*sysK),int(18*sysK));//CPoint(80,18);
	pSeg53->m_LineWidth=2;
	pSeg53->m_SegColor=RGB(0,0,0);
	pSeg53->m_IsCutByX=true;
	pSeg53->m_UnitX=pSymLine51->m_UnitX;
	pSymLine51->m_SymElement.push_back(pSeg53);
	CGIS_SymEleCircle *pCircle51=new CGIS_SymEleCircle();
	pCircle51->m_CenPos=CPoint(int(90*sysK),0);
	pCircle51->r=int(6*sysK);
	pCircle51->m_IsFill=true;
	pCircle51->m_LineWidth=2;
	pCircle51->m_FillColor=RGB(0,0,0);
	pCircle51->m_IsCutByX=true;
	pCircle51->m_UnitX=pSymLine51->m_UnitX;
	pSymLine51->m_SymElement.push_back(pCircle51);
	CGISWorkSpace::SymbolList.push_back(pSymLine51);
}

void CMainFrame::InitGeoElement()
{
	CGIS_GeoPoint *pGeoEle1=new CGIS_GeoPoint();
	pGeoEle1->m_PntID=1;
	pGeoEle1->m_SymID=1;
	pGeoEle1->m_PntPos.posX=1000;
	pGeoEle1->m_PntPos.posY=500;
	CGISWorkSpace::GeoEleList.push_back(pGeoEle1);

	CGIS_GeoPoint *pGeoEle2=new CGIS_GeoPoint();
	pGeoEle2->m_PntID=2;
	pGeoEle2->m_SymID=2;
	pGeoEle2->m_PntPos.posX=1000;
	pGeoEle2->m_PntPos.posY=400;
	CGISWorkSpace::GeoEleList.push_back(pGeoEle2);

	CGIS_GeoPoint *pGeoEle3=new CGIS_GeoPoint();
	pGeoEle3->m_PntID=3;
	pGeoEle3->m_SymID=3;
	pGeoEle3->m_PntPos.posX=1000;
	pGeoEle3->m_PntPos.posY=300;
	CGISWorkSpace::GeoEleList.push_back(pGeoEle3);

	CGIS_GeoPoint *pGeoEle4=new CGIS_GeoPoint();
	pGeoEle4->m_PntID=4;
	pGeoEle4->m_SymID=4;
	pGeoEle4->m_PntPos.posX=1000;
	pGeoEle4->m_PntPos.posY=200;
	CGISWorkSpace::GeoEleList.push_back(pGeoEle4);

	CGIS_GeoPoint *pGeoEle5=new CGIS_GeoPoint();
	pGeoEle5->m_PntID=5;
	pGeoEle5->m_SymID=5;
	pGeoEle5->m_PntPos.posX=1000;
	pGeoEle5->m_PntPos.posY=100;
	CGISWorkSpace::GeoEleList.push_back(pGeoEle5);

	CGIS_GeoLine *pGeoEle6=new CGIS_GeoLine();
	pGeoEle6->m_LineID=6;
	pGeoEle6->m_SymID=6;
	pGeoEle6->m_LinePnts.push_back(Vertex2D(20,400));
	pGeoEle6->m_LinePnts.push_back(Vertex2D(400,400));
	pGeoEle6->m_LinePnts.push_back(Vertex2D(400,600));
	CGISWorkSpace::GeoEleList.push_back(pGeoEle6);

	CGIS_GeoLine *pGeoEle7=new CGIS_GeoLine();
	pGeoEle7->m_LineID=7;
	pGeoEle7->m_SymID=7;
	pGeoEle7->m_LinePnts.push_back(Vertex2D(20,320));
	pGeoEle7->m_LinePnts.push_back(Vertex2D(500,320));
	pGeoEle7->m_LinePnts.push_back(Vertex2D(500,600));
	CGISWorkSpace::GeoEleList.push_back(pGeoEle7);

	CGIS_GeoLine *pGeoEle8=new CGIS_GeoLine();
	pGeoEle8->m_LineID=8;
	pGeoEle8->m_SymID=8;
	pGeoEle8->m_LinePnts.push_back(Vertex2D(20,240));
	pGeoEle8->m_LinePnts.push_back(Vertex2D(600,240));
	pGeoEle8->m_LinePnts.push_back(Vertex2D(600,600));
	CGISWorkSpace::GeoEleList.push_back(pGeoEle8);

	CGIS_GeoLine *pGeoEle9=new CGIS_GeoLine();
	pGeoEle9->m_LineID=9;
	pGeoEle9->m_SymID=9;
	pGeoEle9->m_LinePnts.push_back(Vertex2D(20,160));
	pGeoEle9->m_LinePnts.push_back(Vertex2D(700,160));
	pGeoEle9->m_LinePnts.push_back(Vertex2D(700,600));
	CGISWorkSpace::GeoEleList.push_back(pGeoEle9);

	CGIS_GeoLine *pGeoEle10=new CGIS_GeoLine();
	pGeoEle10->m_LineID=10;
	pGeoEle10->m_SymID=10;
	pGeoEle10->m_LinePnts.push_back(Vertex2D(20,80));
	pGeoEle10->m_LinePnts.push_back(Vertex2D(800,80));
	pGeoEle10->m_LinePnts.push_back(Vertex2D(800,600));
	CGISWorkSpace::GeoEleList.push_back(pGeoEle10);
}

void CMainFrame::InitTools()
{
	CGISWorkSpace::ToolList.push_back(new CGIS_ToolZoomIn());
	CGISWorkSpace::ToolList.push_back(new CGIS_ToolZoomOut());
	CGISWorkSpace::ToolList.push_back(new CGIS_ToolPan());
	CGISWorkSpace::ToolList.push_back(new CGIS_ToolSelect());
	CGISWorkSpace::ToolList.push_back(new CGIS_ToolAddPnt());
	CGISWorkSpace::ToolList.push_back(new CGIS_ToolAddLine());	
}

void CMainFrame::UpdateStatusCoordStr( CString PaneElementStr )
{
	//MessageBox(PaneElementStr);
	CMFCRibbonStatusBarPane *pCoordPane=DYNAMIC_DOWNCAST(CMFCRibbonStatusBarPane,m_wndStatusBar.FindElement(ID_STATUSBAR_PANE1));
	pCoordPane->SetText(PaneElementStr);
	m_wndStatusBar.RedrawWindow();
}
