#pragma once
#include "igis_symbase.h"
#include "IGIS_SymElement.h"
#include <vector>
using namespace std;
class CGIS_SymPoint :
	public IGIS_SymBase
{
public:
	CGIS_SymPoint(void);
	~CGIS_SymPoint(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual long GetSymID(){return m_SymID;}
public:
	CPoint m_PntPos;							//中心点
	long m_SymID;								//符号ID
	CString m_SymName;							//名称
	vector<IGIS_SymElement*> m_SymElement;	//符号组成元素
};

