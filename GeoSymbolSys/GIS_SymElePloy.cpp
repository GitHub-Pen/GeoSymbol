#include "StdAfx.h"
#include "GIS_SymElePloy.h"


CGIS_SymElePloy::CGIS_SymElePloy(void)
{
	m_PathPos.clear();
	m_IsFill=false;
	m_LineWidth=1;
	m_FillColor=RGB(0,0,0);
	m_EdgeColor=RGB(0,0,0);
	m_SymEleType="CGIS_SymElePloy";
}


CGIS_SymElePloy::~CGIS_SymElePloy(void)
{
	m_PathPos.clear();
}

bool CGIS_SymElePloy::Draw(CDC *pDc)
{
	int sum=int(m_PathPos.size());
	if(sum<3)	return false;
	CPoint *pntSet=new CPoint[sum]; 
	float cosValue=GetDirCosValue();
	float sinValue=GetDirSinValue();

	if (m_IsCutByX)
	{
		float startX=StartPercent*m_UnitX;
		float endX=EndPercent*m_UnitX;
		for (int i=0;i<sum;i++)
		{
			float tmpX=float(m_PathPos[i].x);
			if (tmpX<startX||tmpX>endX) return false;
			if (StartPercent!=0)
			{
				tmpX=tmpX-startX;
			}
			pntSet[i].x=int(m_RelativeOrg.x+cosValue*tmpX-sinValue*m_PathPos[i].y+0.5);
			pntSet[i].y=int(m_RelativeOrg.y+sinValue*tmpX+cosValue*m_PathPos[i].y+0.5);
		}

		if (m_IsFill)
		{
			CBrush *newBrush=new CBrush(m_FillColor);
			CBrush *oldBrush=pDc->SelectObject(newBrush);
			pDc->Polygon(pntSet,sum);
			pDc->SelectObject(oldBrush);
			newBrush->DeleteObject();
			delete newBrush;
			newBrush=NULL;
		}
		else
		{
			CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_EdgeColor);
			CPen *oldPen=pDc->SelectObject(newPen);
			pDc->SelectStockObject(NULL_BRUSH);
			pDc->Polygon(pntSet,sum);
			pDc->SelectObject(oldPen);
			newPen->DeleteObject();
			delete newPen;
			newPen=NULL;
		}
		delete pntSet;
		return true;
	}
	else
	{
		for (int i=0;i<sum;i++)
		{
			pntSet[i].x=int(m_RelativeOrg.x+cosValue*m_PathPos[i].x-sinValue*m_PathPos[i].y+0.5);
			pntSet[i].y=int(m_RelativeOrg.y+sinValue*m_PathPos[i].x+cosValue*m_PathPos[i].y+0.5);
		}

		if (m_IsFill)
		{
			CBrush *newBrush=new CBrush(m_FillColor);
			CBrush *oldBrush=pDc->SelectObject(newBrush);
			pDc->Polygon(pntSet,sum);
			pDc->SelectObject(oldBrush);
			newBrush->DeleteObject();
			delete newBrush;
			newBrush=NULL;
		}
		else
		{
			CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_EdgeColor);
			CPen *oldPen=pDc->SelectObject(newPen);
			pDc->SelectStockObject(NULL_BRUSH);
			pDc->Polygon(pntSet,sum);
			pDc->SelectObject(oldPen);
			newPen->DeleteObject();
			delete newPen;
			newPen=NULL;
		}
		delete pntSet;
		return true;
	}
	return false;
}

bool CGIS_SymElePloy::Read(CFile *pFile)
{
	return false;
}

bool CGIS_SymElePloy::Save(CFile *pFile)
{
	return false;
}