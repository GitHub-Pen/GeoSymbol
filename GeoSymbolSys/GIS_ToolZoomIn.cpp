#include "StdAfx.h"
#include "GIS_ToolZoomIn.h"
#include "GISWorkSpace.h"

CGIS_ToolZoomIn::CGIS_ToolZoomIn(void)
{
	GIS_ToolName="CGIS_ToolZoomIn";
	m_rectsel=false;
	m_drag=false;
}


CGIS_ToolZoomIn::~CGIS_ToolZoomIn(void)
{
}

int CGIS_ToolZoomIn::LButtonDown(UINT nFlags, CPoint point)
{
	m_drag=true;
	m_rectsel=false;
	lastPoint=point;
	oriPoint=point;
	return -1;
}

int CGIS_ToolZoomIn::LButtonup(UINT nFlags, CPoint point)
{
	if(m_rectsel)
	{
		CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
		dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
		CPen *pNewPen=new CPen(PS_SOLID,1,RGB(0,0,255));
		CPen *pOldPen=dc.SelectObject(pNewPen);
		pOldPen=dc.SelectObject(pNewPen);
		dc.MoveTo(oriPoint);
		dc.LineTo(oriPoint.x,lastPoint.y);
		dc.MoveTo(oriPoint);
		dc.LineTo(lastPoint.x,oriPoint.y);

		dc.MoveTo(lastPoint);
		dc.LineTo(oriPoint.x,lastPoint.y);
		dc.MoveTo(lastPoint);
		dc.LineTo(lastPoint.x,oriPoint.y);

		dc.SelectObject(pOldPen);
		pNewPen->DeleteObject();
		delete pNewPen;
		pNewPen=NULL;
		pOldPen=NULL;

		float x1=0;float y1=0;
		float x2=0;float y2=0;
		CGISWorkSpace::WndToGeo(oriPoint,x1,y1);
		CGISWorkSpace::WndToGeo(lastPoint,x2,y2);
		if(x1>x2)
		{
			CGISWorkSpace::viewArea.Right=x1;
			CGISWorkSpace::viewArea.Left=x2;
		}
		else
		{
			CGISWorkSpace::viewArea.Right=x2;
			CGISWorkSpace::viewArea.Left=x1;
		}
		if(y1>y2)
		{
			CGISWorkSpace::viewArea.Up=y2;
			CGISWorkSpace::viewArea.Down=y1;
		}
		else
		{
			CGISWorkSpace::viewArea.Up=y1;
			CGISWorkSpace::viewArea.Down=y2;
		}
		float dx=x1>x2?x1-x2:x2-x1;
		float dy=y1>y2?y1-y2:y2-y1;
		//取比值大的那个
		float widRate=dx/CGISWorkSpace::viewRect.Width();
		float heiRate=dy/CGISWorkSpace::viewRect.Height();
		CGISWorkSpace::mapScale=widRate>heiRate?widRate:heiRate;
	}
	else
	{
		float x=0;float y=0;
		CGISWorkSpace::WndToGeo(point,x,y);
		CGISWorkSpace::mapScale*=0.8f;
		CGISWorkSpace::ReCalRealArea(x,y,CGISWorkSpace::mapScale);
	}
	CGISWorkSpace::DrawMap();
	ClipCursor(NULL);//释放鼠标

	m_rectsel=false;
	m_drag=false;
	return -1;
}

int CGIS_ToolZoomIn::MouseMove(UINT nFlags, CPoint point)
{
	if (m_drag)
	{   
		CRect rect;//矩形区域对象
		CGISWorkSpace::GetDispView()->GetClientRect(&rect);//获得并保存窗口视图区区域坐标
		CGISWorkSpace::GetDispView()->ClientToScreen(&rect);//用视图区区域坐标重新计算屏幕坐标
		ClipCursor(&rect);//限制鼠标在窗口视图区中
		m_rectsel=true;
		CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
		dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
		CPen *pNewPen=new CPen(PS_SOLID,1,RGB(0,0,255));
		CPen *pOldPen=dc.SelectObject(pNewPen);
		dc.MoveTo(oriPoint);
		dc.LineTo(oriPoint.x,lastPoint.y);
		dc.MoveTo(oriPoint);
		dc.LineTo(lastPoint.x,oriPoint.y);

		dc.MoveTo(lastPoint);
		dc.LineTo(oriPoint.x,lastPoint.y);
		dc.MoveTo(lastPoint);
		dc.LineTo(lastPoint.x,oriPoint.y);

		////////////////////////////////////////////////////////////////////////
		dc.MoveTo(oriPoint);
		dc.LineTo(oriPoint.x,point.y);
		dc.MoveTo(oriPoint);
		dc.LineTo(point.x,oriPoint.y);

		dc.MoveTo(point);
		dc.LineTo(oriPoint.x,point.y);
		dc.MoveTo(point);
		dc.LineTo(point.x,oriPoint.y);
		
		dc.SelectObject(pOldPen);
		pNewPen->DeleteObject();
		delete pNewPen;
		pNewPen=NULL;
		pOldPen=NULL;
	}
	lastPoint=point;
	return 1;
}

int CGIS_ToolZoomIn::RButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolZoomIn::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	CGIS_ToolZoomIn::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

CString CGIS_ToolZoomIn::GetToolType()
{
	return GIS_ToolName;
}