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
	CPoint m_PntStart;	//起点（相对坐标）
	CPoint m_PntEnd;	//终点（相对坐标）
	int m_LineWidth;	//线宽
	long m_SegColor;	//颜色
};

