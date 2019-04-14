#include "StdAfx.h"
#include "GIS_ToolAddLine.h"
#include "GISWorkSpace.h"
CGIS_ToolAddLine::CGIS_ToolAddLine(void)
{
	GIS_ToolName="CGIS_ToolAddLine";
	pGeoLine=new CGIS_GeoLine();
	m_drag=false;
	VPoints.clear();
}


CGIS_ToolAddLine::~CGIS_ToolAddLine(void)
{
	VPoints.clear();
}

int CGIS_ToolAddLine::LButtonDown(UINT nFlags, CPoint point)
{
	m_drag=true;
	VPoints.push_back(point);
	//lastP=point;
	//CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
	//dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
	//CGIS_GeoLine *pTmpLine=new CGIS_GeoLine();
	//pTmpLine->m_LineID=11;
	//pTmpLine->m_SymID=CGISWorkSpace::currentSymId;
	//float x=0;float y=0;
	//for (int i=0;i<int(VPoints.size());i++)
	//{
	//	CGISWorkSpace::WndToGeo(VPoints[i],x,y);
	//	pTmpLine->m_LinePnts.push_back(Vertex2D(x,y));
	//}
	//pTmpLine->Draw(&dc);
	return -1;
}

int CGIS_ToolAddLine::LButtonup(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolAddLine::MouseMove(UINT nFlags, CPoint point)
{

	if(m_drag)
	{
		CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
		dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
		int num=int(VPoints.size());
		if(num>0)
		{
			if (!(lastP.x==point.x&&lastP.y==point.y))
			{
				dc.MoveTo(VPoints[num-1]);
				dc.LineTo(lastP);
				dc.MoveTo(VPoints[num-1]);
				dc.LineTo(point);
			}
		}
		//CRect rect;//矩形区域对象
		//CGISWorkSpace::GetDispView()->GetClientRect(&rect);//获得并保存窗口视图区区域坐标
		//CGISWorkSpace::GetDispView()->ClientToScreen(&rect);//用视图区区域坐标重新计算屏幕坐标
		//ClipCursor(&rect);	//限制鼠标在窗口视图区中
	}
	lastP=point;
	return -1;
}

int CGIS_ToolAddLine::RButtonDown(UINT nFlags, CPoint point)
{
	m_drag=0;
	CRect rect;//矩形区域对象
	CGISWorkSpace::GetDispView()->GetClientRect(&rect);//获得并保存窗口视图区区域坐标
	CGISWorkSpace::GetDispView()->ClientToScreen(&rect);//用视图区区域坐标重新计算屏幕坐标
	CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
	dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
	VPoints.push_back(point);
	int num=int(VPoints.size());
	if (num<2)return -1;
	if(num>0)
	{
		dc.MoveTo(VPoints[num-1].x,VPoints[num-1].y);
		dc.LineTo(point.x,point.y);
	}
	pGeoLine->m_LineID=11;
	pGeoLine->m_SymID=CGISWorkSpace::currentSymId;
	float x=0;float y=0;
	for (int i=0;i<int(VPoints.size());i++)
	{
		CGISWorkSpace::WndToGeo(VPoints[i],x,y);
		pGeoLine->m_LinePnts.push_back(Vertex2D(x,y));
	}
	CGISWorkSpace::GeoEleList.push_back(pGeoLine);
	CGISWorkSpace::DrawMap();
	pGeoLine=new CGIS_GeoLine();
	ClipCursor(NULL);//释放鼠标
	VPoints.clear();
	lastP=point;
	return -1;
}

int CGIS_ToolAddLine::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	CGIS_ToolAddLine::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	float x=0;float y=0;
	CGISWorkSpace::WndToGeo(pt,x,y);
	if (zDelta<0)
	{
		CGISWorkSpace::mapScale*=1.125f;
	}
	else
	{
		CGISWorkSpace::mapScale*=0.8f;
	}
	CGISWorkSpace::ReCalRealArea(x,y,CGISWorkSpace::mapScale);
	CGISWorkSpace::DrawMap();
	return -1;
}

CString CGIS_ToolAddLine::GetToolType()
{
	return GIS_ToolName;
}