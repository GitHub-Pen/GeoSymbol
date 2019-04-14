#pragma once
#include "igis_geoelebase.h"
#include "Vertex2D.h"
class CGIS_GeoPoint :
	public IGIS_GeoEleBase
{
public:
	CGIS_GeoPoint(void);
	~CGIS_GeoPoint(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Save(CFile *pFile);
	virtual bool Read(CFile *pFile);
	virtual CString GetEleType();
public:
	long m_PntID;//µãºÅ
	Vertex2D m_PntPos;//Î»ÖÃ
	int m_SymID;//·ûºÅ
};

