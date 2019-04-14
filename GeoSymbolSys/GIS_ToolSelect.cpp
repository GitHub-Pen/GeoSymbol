#include "StdAfx.h"
#include "GIS_ToolSelect.h"
#include "GISWorkSpace.h"

CGIS_ToolSelect::CGIS_ToolSelect(void)
{
	GIS_ToolName="CGIS_ToolSelect";
}


CGIS_ToolSelect::~CGIS_ToolSelect(void)
{
}

int CGIS_ToolSelect::LButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolSelect::LButtonup(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolSelect::MouseMove(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolSelect::RButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolSelect::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	CGIS_ToolSelect::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

CString CGIS_ToolSelect::GetToolType()
{
	return GIS_ToolName;
}