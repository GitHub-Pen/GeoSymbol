#pragma once
class IGIS_SymElement
{
public:
	IGIS_SymElement(void);
	~IGIS_SymElement(void);
	virtual bool Draw(CDC *pDc)=0;		//����
	virtual bool Save(CFile *pFile)=0;	//����
	virtual bool Read(CFile *pFile)=0;	//��ȡ
	float GetDirCosValue();				//��ȡ��λ������ֵ	
	float GetDirSinValue();				//��ȡ��λ������ֵ
	virtual CString GetSymEleType()=0;	//��ȡͼԪҪ������

	CPoint m_RelativeOrg;				//���ԭ��
	CPoint m_DirPoint;					//����� Ϊ��ת�����
	bool m_IsCutByX;					//�Ƿ����ָ�
	float StartPercent;					//�������� ��ʼ�ٷֱ� [0��1��
	float EndPercent;					//�������� ��ֹ�ٷֱ� ��0��1]
	int m_UnitX;						//��Ԫ����

protected:
	CString m_SymEleType;				//ͼԪҪ������
};

