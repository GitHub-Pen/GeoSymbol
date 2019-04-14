#pragma once
class IGIS_SymBase
{
public:
	IGIS_SymBase(void);
	~IGIS_SymBase(void);
	virtual bool Draw(CDC *pDc)=0;		//绘制
	virtual bool Save(CFile *pFile)=0;	//保存
	virtual bool Read(CFile *pFile)=0;	//读取
	virtual long GetSymID()=0;			//获取ID
};

