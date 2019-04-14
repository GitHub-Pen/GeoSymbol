#include "StdAfx.h"
#include "GIS_GeoPoint.h"
#include "GISWorkSpace.h"
#include "GIS_SymPoint.h"

CGIS_GeoPoint::CGIS_GeoPoint(void)
{
	m_EleTypeStr="CGIS_GeoPoint";
	m_PntID=-1;
	m_SymID=-1;
}


CGIS_GeoPoint::~CGIS_GeoPoint(void)
{
}

bool CGIS_GeoPoint::Draw(CDC *pDc)
{
	CGIS_SymPoint * pPntSym=(CGIS_SymPoint *)CGISWorkSpace::GetSymbol(m_SymID);
	CPoint wndP(0,0);
	CGISWorkSpace::GeoToWnd(m_PntPos.posX,m_PntPos.posY,wndP);
	pPntSym->m_PntPos=wndP;
	pPntSym->Draw(pDc);
	return true;
}

bool CGIS_GeoPoint::Read(CFile *pFile)
{
	pFile->Read(&m_PntID,sizeof(long));
	pFile->Read(&m_SymID,sizeof(long));
	pFile->Read(&(m_PntPos.posX),sizeof(float));
	pFile->Read(&(m_PntPos.posY),sizeof(float));
	return true;
}

bool CGIS_GeoPoint::Save(CFile *pFile)
{
	pFile->Write(&m_PntID,sizeof(long));
	pFile->Write(&m_SymID,sizeof(long));
	pFile->Write(&(m_PntPos.posX),sizeof(float));
	pFile->Write(&(m_PntPos.posY),sizeof(float));
	return true;
}

CString CGIS_GeoPoint::GetEleType()
{
	return m_EleTypeStr;
}