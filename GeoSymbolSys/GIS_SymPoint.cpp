#include "StdAfx.h"
#include "GIS_SymPoint.h"
#include "GISWorkSpace.h"

CGIS_SymPoint::CGIS_SymPoint(void)
{
	m_SymID=-1;
	m_SymName="";
	m_SymElement.clear();
}


CGIS_SymPoint::~CGIS_SymPoint(void)
{
	m_SymElement.clear();
}

bool CGIS_SymPoint::Draw(CDC *pDc)
{
	for (int i=0;i<int(m_SymElement.size());i++)
	{
		m_SymElement[i]->m_RelativeOrg=m_PntPos;
		m_SymElement[i]->m_DirPoint=m_PntPos+CPoint(1,0);
		m_SymElement[i]->StartPercent=0;
		m_SymElement[i]->EndPercent=1;
		m_SymElement[i]->Draw(pDc);
	}
	return false;
}

bool CGIS_SymPoint::Read(CFile *pFile)
{
	return false;
}

bool CGIS_SymPoint::Save(CFile *pFile)
{

	return false;
}