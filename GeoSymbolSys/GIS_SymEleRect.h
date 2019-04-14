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
	CPoint m_LeftUp;	//���ϵ����꣨������꣩
	CPoint m_RightDown;	//���µ����꣨������꣩
	bool m_IsFill;		//�Ƿ����
	int m_LineWidth;	//�߿�
	long m_FillColor;	//�����ɫ
	long m_EdgeColor;	//�߽���ɫ
};

