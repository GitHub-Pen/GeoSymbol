#pragma once
#include "igis_symelement.h"
#include <vector>
using namespace std;
//多边形
class CGIS_SymElePloy :
	public IGIS_SymElement
{
public:
	CGIS_SymElePloy(void);
	~CGIS_SymElePloy(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual CString GetSymEleType(){return m_SymEleType;}
public:
	vector<CPoint> m_PathPos;	//多边形位置坐标（相对坐标）
	bool m_IsFill;				//是否填充
	int m_LineWidth;			//线宽
	long m_FillColor;			//填充颜色
	long m_EdgeColor;			//边界颜色
};

