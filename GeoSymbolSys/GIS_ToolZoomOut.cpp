#include "StdAfx.h"
#include "GIS_ToolZoomOut.h"
#include "GISWorkSpace.h"

CGIS_ToolZoomOut::CGIS_ToolZoomOut(void)
{
	GIS_ToolName="CGIS_ToolZoomOut";
}


CGIS_ToolZoomOut::~CGIS_ToolZoomOut(void)
{
}

int CGIS_ToolZoomOut::LButtonDown(UINT nFlags, CPoint point)
{
	float x=0;float y=0;
	CGISWorkSpace::WndToGeo(point,x,y);
	CGISWorkSpace::mapScale*=1.25;
	CGISWorkSpace::ReCalRealArea(x,y,CGISWorkSpace::mapScale);
	CGISWorkSpace::DrawMap();
	return -1;
}

int CGIS_ToolZoomOut::LButtonup(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolZoomOut::MouseMove(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolZoomOut::RButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolZoomOut::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	CGIS_ToolZoomOut::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

CString CGIS_ToolZoomOut::GetToolType()
{
	return GIS_ToolName;
}