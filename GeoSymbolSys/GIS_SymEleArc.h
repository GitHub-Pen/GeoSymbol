#pragma once
#include "igis_symelement.h"
//弧形
class CGIS_SymEleArc :
	public IGIS_SymElement
{
public:
	CGIS_SymEleArc(void);
	~CGIS_SymEleArc(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual CString GetSymEleType(){return m_SymEleType;}
public:
	CPoint m_CenPos;	//中心点坐标（相对坐标）
	int r;				//半径
	float m_StartAngle;	//起始角度 0-360 x正轴为起点
	float m_SweepAngle;	//扫过角度 0-360 大于360重复绘制
	bool m_IsFill;		//是否填充
	int m_LineWidth;	//线宽
	long m_FillColor;	//填充颜色
	long m_EdgeColor;	//边界颜色
};

