#pragma once
#include "igis_symelement.h"
class CGIS_SymEleSegment :
	public IGIS_SymElement
{
public:
	CGIS_SymEleSegment(void);
	~CGIS_SymEleSegment(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual CString GetSymEleType(){return m_SymEleType;}
public:
	CPoint m_PntStart;	//��㣨������꣩
	CPoint m_PntEnd;	//�յ㣨������꣩
	int m_LineWidth;	//�߿�
	long m_SegColor;	//��ɫ
};

