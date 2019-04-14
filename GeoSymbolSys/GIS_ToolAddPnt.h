#pragma once
#include "igis_toolbase.h"
#include "GIS_GeoPoint.h"
class CGIS_ToolAddPnt :
	public IGIS_ToolBase
{
public:
	CGIS_ToolAddPnt(void);
	~CGIS_ToolAddPnt(void);
	virtual int LButtonDown(UINT nFlags, CPoint point);
	virtual int LButtonup(UINT nFlags, CPoint point);
	virtual int MouseMove(UINT nFlags, CPoint point);
	virtual int RButtonDown(UINT nFlags, CPoint point);
	virtual int RButtonUp(UINT nFlags, CPoint point);
	virtual int	MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual CString GetToolType();
private:
	CPoint oldPoint;
	CGIS_GeoPoint *pGeoPnt;
};

