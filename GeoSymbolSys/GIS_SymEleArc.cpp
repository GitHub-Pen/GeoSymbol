#include "StdAfx.h"
#include "GIS_SymEleArc.h"
#include <math.h>
float PI=3.141592653f;
CGIS_SymEleArc::CGIS_SymEleArc(void)
{
	r=0;
	m_StartAngle=0;
	m_SweepAngle=0;
	m_IsFill=false;
	m_LineWidth=1;
	m_FillColor=RGB(0,0,0);
	m_EdgeColor=RGB(0,0,0);

	m_SymEleType="CGIS_SymEleArc";
}


CGIS_SymEleArc::~CGIS_SymEleArc(void)
{
}

bool CGIS_SymEleArc::Draw(CDC *pDc)
{
	float cosValue=GetDirCosValue();
	float sinValue=GetDirSinValue();
	if (m_IsCutByX)
	{
		float startX=StartPercent*m_UnitX;
		float endX=EndPercent*m_UnitX;
		float tmpX=float(m_CenPos.x);
		if (tmpX>startX&&tmpX<endX)
		{
			if (StartPercent!=0)
			{
				tmpX=tmpX-startX;
			}
			int x=int(m_RelativeOrg.x+cosValue*tmpX-sinValue*m_CenPos.y);
			int y=int(m_RelativeOrg.y+sinValue*tmpX+cosValue*m_CenPos.y);
			if (m_IsFill)
			{
				CBrush *newBrush=new CBrush(m_FillColor);
				CBrush *oldBrush=pDc->SelectObject(newBrush);
				pDc->MoveTo(int(x+r*cos(m_StartAngle*PI/180)+0.5),int(y+r*sin(m_StartAngle*PI/180)+0.5));
				pDc->AngleArc(x,y,r,m_StartAngle,m_SweepAngle);
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
				pDc->MoveTo(int(x+r*cos(m_StartAngle*PI/180)+0.5),int(y+r*sin(m_StartAngle*PI/180)+0.5));
				pDc->AngleArc(x,y,r,m_StartAngle,m_SweepAngle);
				pDc->SelectObject(oldPen);
				newPen->DeleteObject();
				delete newPen;
				newPen=NULL;
			}
			return true;
		}
	}
	else
	{
		int x=int(m_RelativeOrg.x+cosValue*m_CenPos.x-sinValue*m_CenPos.y);
		int y=int(m_RelativeOrg.y+sinValue*m_CenPos.x+cosValue*m_CenPos.y);
		if (m_IsFill)
		{
			CBrush *newBrush=new CBrush(m_FillColor);
			CBrush *oldBrush=pDc->SelectObject(newBrush);
			pDc->MoveTo(int(x+r*cos(m_StartAngle*PI/180)+0.5),int(y+r*sin(m_StartAngle*PI/180)+0.5));
			pDc->AngleArc(x,y,r,m_StartAngle,m_SweepAngle);
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
			pDc->MoveTo(int(x+r*cos(m_StartAngle*PI/180)+0.5),int(y+r*sin(m_StartAngle*PI/180)+0.5));
			pDc->AngleArc(x,y,r,m_StartAngle,m_SweepAngle);
			pDc->SelectObject(oldPen);
			newPen->DeleteObject();
			delete newPen;
			newPen=NULL;
		}
		return true;
	}
	return false;
}

bool CGIS_SymEleArc::Read(CFile *pFile)
{
	return false;
}

bool CGIS_SymEleArc::Save(CFile *pFile)
{
	return false;
}