#include "StdAfx.h"
#include "AreaRect.h"


CAreaRect::CAreaRect(void)
{
	Left=0;
	Up=0;
	Right=0;
	Down=0;
}


CAreaRect::~CAreaRect(void)
{
}

CAreaRect::CAreaRect(float l, float r, float u, float d)
{
	Left=l;
	Right=r;
	Up=u;
	Down=d;
}

float CAreaRect::GetHeigh()
{
	if (Up>Down)
		return Up-Down;
	else
		return Down-Up;
}

float CAreaRect::GetWidth()
{
	if (Left>Right)
		return Left-Right;
	else
		return Right-Left;
}