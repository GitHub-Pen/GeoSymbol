#include "StdAfx.h"
#include "GIS_GeoLine.h"
#include "GISWorkSpace.h"
#include "GIS_SymLine.h"

CGIS_GeoLine::CGIS_GeoLine(void)
{
	m_EleTypeStr="CGIS_GeoLine";
	m_LineID=-1;
	m_SymID=-1;
	m_LinePnts.clear();
}

CGIS_GeoLine::~CGIS_GeoLine(void)
{
	m_LinePnts.clear();
}


bool CGIS_GeoLine::Draw(CDC *pDc)
{
	CGIS_SymLine * pLineSym=(CGIS_SymLine *)CGISWorkSpace::GetSymbol(m_SymID);
	pLineSym->InitDraw();
	CPoint wndP(0,0);
	for (int i=0;i<int(m_LinePnts.size())-1;i++)
	{
		CGISWorkSpace::GeoToWnd(m_LinePnts[i].posX,m_LinePnts[i].posY,wndP);
		pLineSym->m_PntStart=wndP;
		CGISWorkSpace::GeoToWnd(m_LinePnts[i+1].posX,m_LinePnts[i+1].posY,wndP);
		pLineSym->m_PntEnd=wndP;
		pLineSym->Draw(pDc);
	}
	return true;
}

bool CGIS_GeoLine::Read(CFile *pFile)
{
	pFile->Read(&m_LineID,sizeof(long));
	pFile->Read(&m_SymID,sizeof(long));
	int sum=0;
	pFile->Read(&sum,sizeof(int));
	Vertex2D tmpPos;
	for (int i=0;i<sum;i++)
	{
		pFile->Read(&(tmpPos.posX),sizeof(float));
		pFile->Read(&(tmpPos.posY),sizeof(float));
		m_LinePnts.push_back(tmpPos);
	}
	return true;
}

bool CGIS_GeoLine::Save(CFile *pFile)
{
	pFile->Write(&m_LineID,sizeof(long));
	pFile->Write(&m_SymID,sizeof(long));
	int sum=int(m_LinePnts.size());
	pFile->Write(&sum,sizeof(int));
	for (int i=0;i<sum;i++)
	{
		pFile->Write(&(m_LinePnts[i].posX),sizeof(float));
		pFile->Write(&(m_LinePnts[i].posY),sizeof(float));
	}
	return true;
}

CString CGIS_GeoLine::GetEleType()
{
	return m_EleTypeStr;
}