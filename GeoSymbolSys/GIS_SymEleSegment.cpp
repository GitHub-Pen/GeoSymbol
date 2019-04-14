#include "StdAfx.h"
#include "GIS_SymEleSegment.h"


CGIS_SymEleSegment::CGIS_SymEleSegment(void)
{
	m_LineWidth=1;
	m_SegColor=RGB(0,0,0);
	m_SymEleType="CGIS_SymEleSegment";
}


CGIS_SymEleSegment::~CGIS_SymEleSegment(void)
{
}

bool CGIS_SymEleSegment::Draw(CDC *pDc)
{
	float cosValue=GetDirCosValue();
	float sinValue=GetDirSinValue();
	if (m_IsCutByX)//受长度分割
	{
		//构建新线段
		float startX=StartPercent*m_UnitX;
		float endX=EndPercent*m_UnitX;
		float xmin=float(m_PntStart.x)>startX? float(m_PntStart.x):startX;
		float xmax=float(m_PntEnd.x)<endX? float(m_PntEnd.x):endX;
		if(xmax<xmin) return false;
		if (StartPercent!=0)
		{
			xmax=xmax-startX;
			xmin=xmin-startX;
		}
		CPoint *pntSet=new CPoint[2]; 
		pntSet[0].x=int(m_RelativeOrg.x+cosValue*xmin-sinValue*m_PntStart.y+0.5);
		pntSet[0].y=int(m_RelativeOrg.y+sinValue*xmin+cosValue*m_PntStart.y+0.5);

		pntSet[1].x=int(m_RelativeOrg.x+cosValue*xmax-sinValue*m_PntEnd.y+0.5);
		pntSet[1].y=int(m_RelativeOrg.y+sinValue*xmax+cosValue*m_PntEnd.y+0.5);

		CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_SegColor);
		CPen *oldPen=pDc->SelectObject(newPen);
		pDc->MoveTo(pntSet[0]);
		pDc->LineTo(pntSet[1]);
		pDc->SelectObject(oldPen);
		newPen->DeleteObject();
		delete newPen;
		newPen=NULL;
		oldPen=NULL;
		delete pntSet;
		return true;
	}
	else //不受长度分割 仅判断是否绘制
	{
		CPoint *pntSet=new CPoint[2]; 
		pntSet[0].x=int(m_RelativeOrg.x+cosValue*m_PntStart.x-sinValue*m_PntStart.y+0.5);
		pntSet[0].y=int(m_RelativeOrg.y+sinValue*m_PntStart.x+cosValue*m_PntStart.y+0.5);

		pntSet[1].x=int(m_RelativeOrg.x+cosValue*m_PntEnd.x-sinValue*m_PntEnd.y+0.5);
		pntSet[1].y=int(m_RelativeOrg.y+sinValue*m_PntEnd.x+cosValue*m_PntEnd.y+0.5);
		CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_SegColor);
		CPen *oldPen=pDc->SelectObject(newPen);
		pDc->MoveTo(pntSet[0]);
		pDc->LineTo(pntSet[1]);
		pDc->SelectObject(oldPen);
		newPen->DeleteObject();
		delete newPen;
		newPen=NULL;
		oldPen=NULL;
		delete pntSet;
		return true;
	}
	return false;
}

bool CGIS_SymEleSegment::Read(CFile *pFile)
{
	return false;
}

bool CGIS_SymEleSegment::Save(CFile *pFile)
{
	return false;
}