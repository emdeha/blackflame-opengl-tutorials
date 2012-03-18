#include "stdafx.h"
#include "GraphicsGeometry.h"

#include<math.h>


Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}
Vector3D::Vector3D(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

float Vector3D::GetLength()
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3D::Normalize(Vector3D &A)
{
	float newX = A.x / A.GetLength();
	float newY = A.y / A.GetLength();
	float newZ = A.z / A.GetLength();
	
	A = Vector3D(newX, newY, newZ);
}