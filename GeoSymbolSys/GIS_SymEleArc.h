#pragma once
#include "igis_symelement.h"
//����
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
	CPoint m_CenPos;	//���ĵ����꣨������꣩
	int r;				//�뾶
	float m_StartAngle;	//��ʼ�Ƕ� 0-360 x����Ϊ���
	float m_SweepAngle;	//ɨ���Ƕ� 0-360 ����360�ظ�����
	bool m_IsFill;		//�Ƿ����
	int m_LineWidth;	//�߿�
	long m_FillColor;	//�����ɫ
	long m_EdgeColor;	//�߽���ɫ
};

