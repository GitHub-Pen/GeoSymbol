#pragma once
class IGIS_GeoEleBase
{
public:
	IGIS_GeoEleBase(void);
	~IGIS_GeoEleBase(void);
	virtual bool Draw(CDC *pDc)=0;		//����
	virtual bool Save(CFile *pFile)=0;	//����
	virtual bool Read(CFile *pFile)=0;	//��ȡ
	virtual CString GetEleType()=0;		//��ȡҪ������
protected:
	CString m_EleTypeStr;				//Ҫ������
};

