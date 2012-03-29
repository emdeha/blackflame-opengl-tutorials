#include "stdafx.h"
#include "GraphicsGeometry.h"

float WrapPi(float angle)
{
	angle = angle + PI;
	angle = angle - floor(angle * PI_DOUBLE_ONE_OVER) * PI_DOUBLE;
	angle = angle - PI;
	return angle;
}

float SafeAcos(float x)
{
	if(x <= -1.0f)
	{
		return PI;
	}
	if(x >= 1.0f)
	{
		return 0.0f;
	}

	return acos(x);
}















