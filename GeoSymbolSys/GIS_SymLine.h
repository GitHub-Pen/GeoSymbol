#pragma once
#include "igis_symbase.h"
#include "IGIS_SymElement.h"
#include <vector>
using namespace std;
class CGIS_SymLine :
	public IGIS_SymBase
{
public:
	CGIS_SymLine(void);
	~CGIS_SymLine(void);
	virtual bool Draw(CDC *pDc);
	virtual bool Read(CFile *pFile);
	virtual bool Save(CFile *pFile);
	virtual long GetSymID(){return m_SymID;}
	void InitDraw(){m_OldPerPos=0;}
public:
	CPoint m_PntStart;							//起点
	CPoint m_PntEnd;							//终点
	long m_SymID;								//符号ID
	CString m_SymName;							//名称
	vector<IGIS_SymElement*> m_SymElement;		//符号组成元素
	int m_UnitX;								//单元长度
private:
	float m_NewPerPos;							//符号绘制长度比例 [0,1）
	float m_OldPerPos;							//上次绘制比例余留 [0,1)
};

