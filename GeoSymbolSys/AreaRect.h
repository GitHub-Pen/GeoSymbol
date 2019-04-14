#pragma once
class CAreaRect
{
public:
	CAreaRect(void);
	~CAreaRect(void);
	CAreaRect(float l, float r, float u, float d);//вСсриооб
	float GetWidth();
	float GetHeigh();
public:
	float Left;
	float Right;
	float Up;
	float Down;
};

