#pragma once
#include "igis_geoelebase.h"
#include "Vertex2D.h"
#include <vector>
using namespace std;
class CGIS_GeoLine :
	public IGIS_GeoEleBase
{
public:
	CGIS_GeoLine(void);
	~CGIS_GeoLine(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Save(CFile *pFile);
	virtual bool Read(CFile *pFile);
	virtual CString GetEleType();
public:
	long m_LineID;//ÏßºÅ
	vector<Vertex2D> m_LinePnts;//Î»ÖÃµã
	int m_SymID;//·ûºÅ
};

