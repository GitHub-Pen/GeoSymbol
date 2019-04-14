#include "StdAfx.h"
#include "GIS_ToolAddPnt.h"
#include "GISWorkSpace.h"
CGIS_ToolAddPnt::CGIS_ToolAddPnt(void)
{
	GIS_ToolName="CGIS_ToolAddPnt";
	pGeoPnt=new CGIS_GeoPoint();
}


CGIS_ToolAddPnt::~CGIS_ToolAddPnt(void)
{
}

int CGIS_ToolAddPnt::LButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
	dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
	CGIS_GeoPoint *pGeoP=new CGIS_GeoPoint();
	pGeoP->m_PntID=11;
	pGeoP->m_SymID=CGISWorkSpace::currentSymId;
	CGISWorkSpace::WndToGeo(oldPoint,pGeoP->m_PntPos.posX,pGeoP->m_PntPos.posY);
	CGISWorkSpace::GeoEleList.push_back(pGeoP);
	CGISWorkSpace::DrawMap();
	pGeoP->Draw(&dc);
	return -1;
}

int CGIS_ToolAddPnt::LButtonup(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolAddPnt::MouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(CGISWorkSpace::GetDispView());//构造设备环境对象
	dc.SetROP2(R2_NOT);//设置绘图模式为R2_NOT
	pGeoPnt->m_PntID=11;
	pGeoPnt->m_SymID=CGISWorkSpace::currentSymId;
	CGISWorkSpace::WndToGeo(oldPoint,pGeoPnt->m_PntPos.posX,pGeoPnt->m_PntPos.posY);
	pGeoPnt->Draw(&dc);
	CGISWorkSpace::WndToGeo(point,pGeoPnt->m_PntPos.posX,pGeoPnt->m_PntPos.posY);
	pGeoPnt->Draw(&dc);
	oldPoint=point;
	return -1;
}

int CGIS_ToolAddPnt::RButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int CGIS_ToolAddPnt::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	CGIS_ToolAddPnt::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

CString CGIS_ToolAddPnt::GetToolType()
{
	return GIS_ToolName;
}
