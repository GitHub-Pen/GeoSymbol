#pragma once
#include "igis_symelement.h"
#include <vector>
using namespace std;
//�����
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
	vector<CPoint> m_PathPos;	//�����λ�����꣨������꣩
	bool m_IsFill;				//�Ƿ����
	int m_LineWidth;			//�߿�
	long m_FillColor;			//�����ɫ
	long m_EdgeColor;			//�߽���ɫ
};

