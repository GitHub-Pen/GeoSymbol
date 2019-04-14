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
	CPoint m_PntStart;							//���
	CPoint m_PntEnd;							//�յ�
	long m_SymID;								//����ID
	CString m_SymName;							//����
	vector<IGIS_SymElement*> m_SymElement;		//�������Ԫ��
	int m_UnitX;								//��Ԫ����
private:
	float m_NewPerPos;							//���Ż��Ƴ��ȱ��� [0,1��
	float m_OldPerPos;							//�ϴλ��Ʊ������� [0,1)
};

