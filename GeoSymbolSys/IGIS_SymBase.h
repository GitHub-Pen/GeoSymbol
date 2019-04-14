#pragma once
class IGIS_SymBase
{
public:
	IGIS_SymBase(void);
	~IGIS_SymBase(void);
	virtual bool Draw(CDC *pDc)=0;		//����
	virtual bool Save(CFile *pFile)=0;	//����
	virtual bool Read(CFile *pFile)=0;	//��ȡ
	virtual long GetSymID()=0;			//��ȡID
};

