#pragma once
#include "igis_symelement.h"
//圆
class CGIS_SymEleCircle :
	public IGIS_SymElement
{
public:
	CGIS_SymEleCircle(void);
	~CGIS_SymEleCircle(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual CString GetSymEleType(){return m_SymEleType;}
public:
	int r;				//半径
	CPoint m_CenPos;	//圆心（相对坐标）
	bool m_IsFill;		//是否填充
	int m_LineWidth;	//线宽
	long m_FillColor;	//填充颜色
	long m_EdgeColor;	//边界颜色
};

