#pragma once
#include "igis_symelement.h"
//Բ
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
	int r;				//�뾶
	CPoint m_CenPos;	//Բ�ģ�������꣩
	bool m_IsFill;		//�Ƿ����
	int m_LineWidth;	//�߿�
	long m_FillColor;	//�����ɫ
	long m_EdgeColor;	//�߽���ɫ
};

