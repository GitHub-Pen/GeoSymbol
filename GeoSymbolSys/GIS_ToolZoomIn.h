#pragma once
#include "igis_toolbase.h"
class CGIS_ToolZoomIn :
	public IGIS_ToolBase
{
public:
	CGIS_ToolZoomIn(void);
	~CGIS_ToolZoomIn(void);
	virtual int LButtonDown(UINT nFlags, CPoint point);
	virtual int LButtonup(UINT nFlags, CPoint point);
	virtual int MouseMove(UINT nFlags, CPoint point);
	virtual int RButtonDown(UINT nFlags, CPoint point);
	virtual int RButtonUp(UINT nFlags, CPoint point);
	virtual int	MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual CString GetToolType();
private:
	bool m_rectsel;
	bool m_drag;
	CPoint lastPoint;
	CPoint oriPoint;
};

