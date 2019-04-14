#include "StdAfx.h"
#include "GIS_SymLine.h"


CGIS_SymLine::CGIS_SymLine(void)
{
	m_SymID=-1;
	m_SymName="";
	m_NewPerPos=0;
	m_OldPerPos=0;
	m_UnitX=100;
	m_SymElement.clear();
}


CGIS_SymLine::~CGIS_SymLine(void)
{
	m_SymElement.clear();
}

bool CGIS_SymLine::Draw(CDC *pDc)
{
	float SymLenth=sqrt(float((m_PntStart.x-m_PntEnd.x)*(m_PntStart.x-m_PntEnd.x)+(m_PntStart.y-m_PntEnd.y)*(m_PntStart.y-m_PntEnd.y)));
	float desRate=SymLenth/m_UnitX;
	CPoint winPos(0,0);
	if (desRate<1)
	{
		if (desRate>m_OldPerPos)
		{
			m_NewPerPos=desRate-m_OldPerPos;
			//m_OldPerPos=1-m_NewPerPos;
			if (m_OldPerPos>0)
			{
				for(int j=0;j<int(m_SymElement.size());j++)
				{
					m_SymElement[j]->m_RelativeOrg=m_PntStart;
					m_SymElement[j]->m_DirPoint=m_PntEnd;
					m_SymElement[j]->StartPercent=1-m_OldPerPos;
					m_SymElement[j]->EndPercent=1;
					m_SymElement[j]->Draw(pDc);
				}
			}
			if (m_NewPerPos>0)
			{
				float k=(m_OldPerPos)*m_UnitX/SymLenth;
				winPos.x=int(m_PntStart.x+k*(m_PntEnd.x-m_PntStart.x)+0.5);
				winPos.y=int(m_PntStart.y+k*(m_PntEnd.y-m_PntStart.y)+0.5);
				for(int j=0;j<int(m_SymElement.size());j++)
				{
					m_SymElement[j]->m_RelativeOrg=winPos;
					m_SymElement[j]->m_DirPoint=m_PntEnd;
					m_SymElement[j]->StartPercent=0;
					m_SymElement[j]->EndPercent=m_NewPerPos;
					m_SymElement[j]->Draw(pDc);
				}
			}
			m_OldPerPos=1-m_NewPerPos;
		}
		else
		{
			m_NewPerPos=0;
			//m_OldPerPos=1-m_NewPerPos;
			if (m_OldPerPos>0)
			{
				for(int j=0;j<int(m_SymElement.size());j++)
				{
					m_SymElement[j]->m_RelativeOrg=m_PntStart;
					m_SymElement[j]->m_DirPoint=m_PntEnd;
					m_SymElement[j]->StartPercent=1-m_OldPerPos;
					m_SymElement[j]->EndPercent=1-m_OldPerPos+desRate;
					m_SymElement[j]->Draw(pDc);
				}
			}
			m_OldPerPos=m_OldPerPos-desRate;
		}
	}
	else
	{
		int times=int((SymLenth-m_UnitX*m_OldPerPos)/m_UnitX);	// 多少组符号纹理
		m_NewPerPos=desRate-times-m_OldPerPos;			// 剩余比例

		if (m_OldPerPos>0)
		{
			for(int j=0;j<int(m_SymElement.size());j++)
			{
				m_SymElement[j]->m_RelativeOrg=m_PntStart;
				m_SymElement[j]->m_DirPoint=m_PntEnd;
				m_SymElement[j]->StartPercent=1-m_OldPerPos;
				m_SymElement[j]->EndPercent=1;
				m_SymElement[j]->Draw(pDc);
			}
		}
		for (int i=0;i<times;i++)//绘制完整的线纹理
		{
			float k=(i+m_OldPerPos)*m_UnitX/SymLenth;
			winPos.x=int(m_PntStart.x+k*(m_PntEnd.x-m_PntStart.x)+0.5);
			winPos.y=int(m_PntStart.y+k*(m_PntEnd.y-m_PntStart.y)+0.5);
			for(int j=0;j<int(m_SymElement.size());j++)
			{
				m_SymElement[j]->m_RelativeOrg=winPos;
				m_SymElement[j]->m_DirPoint=m_PntEnd;
				m_SymElement[j]->StartPercent=0;
				m_SymElement[j]->EndPercent=1;
				m_SymElement[j]->Draw(pDc);
			}
		}
		if (m_NewPerPos>0)
		{
			float k=(times+m_OldPerPos)*m_UnitX/SymLenth;
			winPos.x=int(m_PntStart.x+k*(m_PntEnd.x-m_PntStart.x)+0.5);
			winPos.y=int(m_PntStart.y+k*(m_PntEnd.y-m_PntStart.y)+0.5);
			for(int j=0;j<int(m_SymElement.size());j++)
			{
				m_SymElement[j]->m_RelativeOrg=winPos;
				m_SymElement[j]->m_DirPoint=m_PntEnd;
				m_SymElement[j]->StartPercent=0;
				m_SymElement[j]->EndPercent=m_NewPerPos;
				m_SymElement[j]->Draw(pDc);
			}
		}
		m_OldPerPos=1-m_NewPerPos;
	}
	return false;
}

bool CGIS_SymLine::Read(CFile *pFile)
{
	return false;
}

bool CGIS_SymLine::Save(CFile *pFile)
{
	return false;
}