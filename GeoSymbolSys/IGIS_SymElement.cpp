#include "StdAfx.h"
#include "IGIS_SymElement.h"
#include <math.h>

IGIS_SymElement::IGIS_SymElement(void)
{
	m_RelativeOrg.x=0;
	m_RelativeOrg.y=0;
	m_DirPoint.x=1;
	m_DirPoint.y=0;

	m_IsCutByX=false;
	StartPercent=0;
	EndPercent=1;
	m_UnitX=100;

	m_SymEleType="";
}


IGIS_SymElement::~IGIS_SymElement(void)
{
}

float IGIS_SymElement::GetDirCosValue()
{
	float dx=float(m_DirPoint.x-m_RelativeOrg.x);
	float dy=float(m_DirPoint.y-m_RelativeOrg.y);
	float len=sqrt(dx*dx+dy*dy);
	return dx/len;
}

float IGIS_SymElement::GetDirSinValue()
{
	float dx=float(m_DirPoint.x-m_RelativeOrg.x);
	float dy=float(m_DirPoint.y-m_RelativeOrg.y);
	float len=sqrt(dx*dx+dy*dy);
	return dy/len;
}