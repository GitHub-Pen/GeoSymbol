#pragma once
class IGIS_SymElement
{
public:
	IGIS_SymElement(void);
	~IGIS_SymElement(void);
	virtual bool Draw(CDC *pDc)=0;		//绘制
	virtual bool Save(CFile *pFile)=0;	//保存
	virtual bool Read(CFile *pFile)=0;	//读取
	float GetDirCosValue();				//获取方位上余弦值	
	float GetDirSinValue();				//获取方位上正弦值
	virtual CString GetSymEleType()=0;	//获取图元要素类型

	CPoint m_RelativeOrg;				//相对原点
	CPoint m_DirPoint;					//方向点 为旋转服务的
	bool m_IsCutByX;					//是否横向分割
	float StartPercent;					//绘制区间 起始百分比 [0，1）
	float EndPercent;					//绘制区间 终止百分比 （0，1]
	int m_UnitX;						//单元长度

protected:
	CString m_SymEleType;				//图元要素类型
};

