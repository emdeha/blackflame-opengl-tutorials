#ifdef GRAPHICSGEOMETRY_EXPORTS
#define GRAPHICSGEOMETRY_API __declspec(dllexport)
#else
#define GRAPHICSGEOMETRY_API __declspec(dllimport)
#endif

#pragma once

#include <assert.h>
#include <math.h>

#define PI 3.14159265f
#define PI_DOUBLE 2.0f * PI
#define PI_OVER_TWO PI / 2.0f
#define PI_ONE_OVER 1.0f / PI
#define PI_DOUBLE_ONE_OVER 1.0f / PI_DOUBLE

#define INF 999999

extern GRAPHICSGEOMETRY_API float WrapPi(float angle);

extern GRAPHICSGEOMETRY_API float SafeAcos(float x);

inline void ComputeBothSinCos(float *returnSin, float *returnCos, float angle)
{
	*returnSin = sin(angle);
	*returnCos = cos(angle);
}