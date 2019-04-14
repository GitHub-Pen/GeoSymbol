#include "StdAfx.h"
#include "GIS_SymEleRect.h"


CGIS_SymEleRect::CGIS_SymEleRect(void)
{
	m_IsFill=false;
	m_LineWidth=1;
	m_FillColor=RGB(0,0,0);
	m_EdgeColor=RGB(0,0,0);
	m_SymEleType="CGIS_SymEleRect";
}


CGIS_SymEleRect::~CGIS_SymEleRect(void)
{
}

//绘制
//因为旋转会导致成为非矩形 不可用rectangle 而需要转为ploy绘制
bool CGIS_SymEleRect::Draw(CDC *pDc)
{
	float cosValue=GetDirCosValue();
	float sinValue=GetDirSinValue();
	if (m_IsCutByX)//受长度分割
	{
		//构建新的矩形
		float startX=StartPercent*m_UnitX;
		float endX=EndPercent*m_UnitX;
		float xmin=float(m_LeftUp.x)>startX? float(m_LeftUp.x):startX;
		float xmax=float(m_RightDown.x)<endX? float(m_RightDown.x):endX;
		if(xmax<=xmin) return false;
		if (StartPercent!=0)
		{
			xmax=xmax-startX;
			xmin=xmin-startX;
		}
		CPoint *pntSet=new CPoint[4]; 

		pntSet[0].x=int(m_RelativeOrg.x+cosValue*xmin-sinValue*m_LeftUp.y+0.5);
		pntSet[0].y=int(m_RelativeOrg.y+sinValue*xmin+cosValue*m_LeftUp.y+0.5);

		pntSet[1].x=int(m_RelativeOrg.x+cosValue*xmin-sinValue*m_RightDown.y+0.5);
		pntSet[1].y=int(m_RelativeOrg.y+sinValue*xmin+cosValue*m_RightDown.y+0.5);

		pntSet[2].x=int(m_RelativeOrg.x+cosValue*xmax-sinValue*m_RightDown.y+0.5);
		pntSet[2].y=int(m_RelativeOrg.y+sinValue*xmax+cosValue*m_RightDown.y+0.5);

		pntSet[3].x=int(m_RelativeOrg.x+cosValue*xmax-sinValue*m_LeftUp.y+0.5);
		pntSet[3].y=int(m_RelativeOrg.y+sinValue*xmax+cosValue*m_LeftUp.y+0.5);

		if (m_IsFill)
		{
			CBrush *newBrush=new CBrush(m_FillColor);
			CBrush *oldBrush=pDc->SelectObject(newBrush);
			pDc->Polygon(pntSet,4);
			pDc->SelectObject(oldBrush);
			newBrush->DeleteObject();
			delete newBrush;
			newBrush=NULL;
			CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_EdgeColor);
			CPen *oldPen=pDc->SelectObject(newPen);
			pDc->SelectStockObject(NULL_BRUSH);
			pDc->Polygon(pntSet,4);
			pDc->SelectObject(oldPen);
			newPen->DeleteObject();
			delete newPen;
			delete pntSet;
			newPen=NULL;
		}
		else
		{
			CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_EdgeColor);
			CPen *oldPen=pDc->SelectObject(newPen);
			pDc->SelectStockObject(NULL_BRUSH);
			pDc->Polygon(pntSet,4);
			pDc->SelectObject(oldPen);
			newPen->DeleteObject();
			delete newPen;
			delete pntSet;
			newPen=NULL;
		}
		return true;
	}
	else //不受长度分割 仅判断是否绘制
	{
		float k=float(m_LeftUp.x+m_RightDown.x)/float(m_UnitX);
		if (k>=StartPercent||k<=EndPercent)
		{
			CPoint *pntSet=new CPoint[4]; 
			pntSet[0].x=int(m_RelativeOrg.x+cosValue*m_LeftUp.x-sinValue*m_LeftUp.y+0.5);
			pntSet[0].y=int(m_RelativeOrg.y+sinValue*m_LeftUp.x+cosValue*m_LeftUp.y+0.5);

			pntSet[1].x=int(m_RelativeOrg.x+cosValue*m_LeftUp.x-sinValue*m_RightDown.y+0.5);
			pntSet[1].y=int(m_RelativeOrg.y+sinValue*m_LeftUp.x+cosValue*m_RightDown.y+0.5);

			pntSet[2].x=int(m_RelativeOrg.x+cosValue*m_RightDown.x-sinValue*m_RightDown.y+0.5);
			pntSet[2].y=int(m_RelativeOrg.y+sinValue*m_RightDown.x+cosValue*m_RightDown.y+0.5);

			pntSet[3].x=int(m_RelativeOrg.x+cosValue*m_RightDown.x-sinValue*m_LeftUp.y+0.5);
			pntSet[3].y=int(m_RelativeOrg.y+sinValue*m_RightDown.x+cosValue*m_LeftUp.y+0.5);

			if (m_IsFill)
			{
				CBrush *newBrush=new CBrush(m_FillColor);
				CBrush *oldBrush=pDc->SelectObject(newBrush);
				pDc->Polygon(pntSet,4);
				pDc->SelectObject(oldBrush);
				newBrush->DeleteObject();
				delete newBrush;
				newBrush=NULL;
				CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_EdgeColor);
				CPen *oldPen=pDc->SelectObject(newPen);
				pDc->Polygon(pntSet,4);
				pDc->SelectObject(oldPen);
				newPen->DeleteObject();
				delete newPen;
				delete pntSet;
				newPen=NULL;
			}
			else
			{
				CPen *newPen=new CPen(PS_SOLID,m_LineWidth,m_EdgeColor);
				CPen *oldPen=pDc->SelectObject(newPen);
				pDc->Polygon(pntSet,4);
				pDc->SelectObject(oldPen);
				newPen->DeleteObject();
				delete newPen;
				delete pntSet;
				newPen=NULL;
			}
			return true;
		}
	}
	return false;
}

bool CGIS_SymEleRect::Read(CFile *pFile)
{
	return false;
}

bool CGIS_SymEleRect::Save(CFile *pFile)
{
	return false;
}