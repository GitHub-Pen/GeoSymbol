#pragma once
class IGIS_ToolBase
{
public:
	IGIS_ToolBase(void);
	~IGIS_ToolBase(void);
	virtual int LButtonDown(UINT nFlags, CPoint point);
	virtual int LButtonup(UINT nFlags, CPoint point);
	virtual int MouseMove(UINT nFlags, CPoint point);
	virtual int RButtonDown(UINT nFlags, CPoint point);
	virtual int RButtonUp(UINT nFlags, CPoint point);
	virtual int	MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual CString GetToolType()=0;
public:
	CString GIS_ToolName;		//交互工具名称
	HCURSOR m_Cursor;			//光标资源句柄
};

