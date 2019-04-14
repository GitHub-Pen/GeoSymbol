#pragma once
#include "igis_symelement.h"
class CGIS_SymEleRect :
	public IGIS_SymElement
{
public:
	CGIS_SymEleRect(void);
	~CGIS_SymEleRect(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual CString GetSymEleType(){return m_SymEleType;}
public:
	CPoint m_LeftUp;	//左上点坐标（相对坐标）
	CPoint m_RightDown;	//右下点坐标（相对坐标）
	bool m_IsFill;		//是否填充
	int m_LineWidth;	//线宽
	long m_FillColor;	//填充颜色
	long m_EdgeColor;	//边界颜色
};

