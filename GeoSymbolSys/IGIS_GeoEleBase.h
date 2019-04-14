#pragma once
class IGIS_GeoEleBase
{
public:
	IGIS_GeoEleBase(void);
	~IGIS_GeoEleBase(void);
	virtual bool Draw(CDC *pDc)=0;		//绘制
	virtual bool Save(CFile *pFile)=0;	//保存
	virtual bool Read(CFile *pFile)=0;	//读取
	virtual CString GetEleType()=0;		//获取要素类型
protected:
	CString m_EleTypeStr;				//要素类型
};

