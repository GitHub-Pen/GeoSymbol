#include "StdAfx.h"
#include "IGIS_ToolBase.h"

IGIS_ToolBase::IGIS_ToolBase(void)
{
}

IGIS_ToolBase::~IGIS_ToolBase(void)
{
}

int IGIS_ToolBase::LButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int IGIS_ToolBase::LButtonup(UINT nFlags, CPoint point)
{
	return -1;
}

int IGIS_ToolBase::MouseMove(UINT nFlags, CPoint point)
{
	return -1;
}

int IGIS_ToolBase::RButtonDown(UINT nFlags, CPoint point)
{
	return -1;
}

int IGIS_ToolBase::RButtonUp(UINT nFlags, CPoint point)
{
	return -1;
}

int	IGIS_ToolBase::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return -1;
}