#include "StdAfx.h"
#include "GIS_ToolPan.h"
#include "resource.h"
#include "GISWorkSpace.h"
CGIS_ToolPan::CGIS_ToolPan(void)
{
	GIS_ToolName="CGIS_ToolPan";
	//m_Cursor=AfxGetApp()->LoadCursor(IDC_HAND);
	m_Cursor=AfxGetApp()->LoadStandardCursor(IDC_HAND);
	m_drag=false;
}


CGIS_ToolPan::~CGIS_ToolPan(void)
{
}

int CGIS_ToolPan::LButtonDown(UINT nFlags, CPoint point)
{
	SetCursor(m_Cursor);
	m_drag=true;
	lastPoint=point;
	return -1;
}

int CGIS_ToolPan::LButtonup(UINT nFlags, CPoint point)
{
	m_drag=false;
	return -1;
}

int CGIS_ToolPan::MouseMove(UINT nFlags, CPoint point)
{
	SetCursor(m_Cursor);
	if(m_drag)
	{
		float x1=0;float y1=0;
		float x2=0;float y2=0;
		CGISWorkSpace::WndToGeo(point,x1,y1);
		CGISWorkSpace::WndToGeo(lastPoint,x2,y2);
		CGISWorkSpace::viewArea.Left+=x2-x1;
		CGISWorkSpace::viewArea.Right+=x2-x1;
		CGISWorkSpace::viewArea.Up+=y2-y1;
		CGISWorkSpace::viewArea.Down+=y2-y1;
		CGISWorkSpace::DrawMap();
		lastPoint=point;
	}
	return -1;
}

int CGIS_ToolPan::RButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolPan::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	CGIS_ToolPan::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

CString CGIS_ToolPan::GetToolType()
{
	return GIS_ToolName;
}