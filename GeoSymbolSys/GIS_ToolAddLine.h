#pragma once
#include "igis_toolbase.h"
#include "GIS_GeoLine.h"
class CGIS_ToolAddLine :
	public IGIS_ToolBase
{
public:
	CGIS_ToolAddLine(void);
	~CGIS_ToolAddLine(void);
	virtual int LButtonDown(UINT nFlags, CPoint point);
	virtual int LButtonup(UINT nFlags, CPoint point);
	virtual int MouseMove(UINT nFlags, CPoint point);
	virtual int RButtonDown(UINT nFlags, CPoint point);
	virtual int RButtonUp(UINT nFlags, CPoint point);
	virtual int	MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual CString GetToolType();
private:
	bool m_drag;		//表示在画线中
	CPoint lastP;
	CGIS_GeoLine *pGeoLine;
	vector <CPoint> VPoints;
};

