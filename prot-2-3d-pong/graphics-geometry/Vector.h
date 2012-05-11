#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

#pragma once

#include "GraphicsGeometry.h"

class GRAPHICSGEOMETRY_API Vector3d
{
private:
	float x, y, z;

public:
	Vector3d(float x=0, float y=0, float z=0)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
	
	void SetX(float newX);
	void SetY(float newY);
	void SetZ(float newZ);

	float GetX();
	float GetY();
	float GetZ();
	
	Vector3d operator+(const Vector3d &other);
	Vector3d operator-(const Vector3d &other);
	Vector3d operator*(const float &coef);
	Vector3d operator/(const float &coef);

	float GetLength();
	float GetLengthSqrt();
	void Normalize();

	void RotateXY(float angle_degs);
	void RotateYZ(float angle_degs);
	void RotateZX(float angle_degs);

	void RotateAroundY(float angle_degs);
	void RotateAroundX(float angle_degs);
	void RotateAroundZ(float angle_degs);
};

double GRAPHICSGEOMETRY_API DotProduct(Vector3d A, Vector3d B);
double GRAPHICSGEOMETRY_API CrossProduct2D(Vector3d A, Vector3d B);
Vector3d GRAPHICSGEOMETRY_API CrossProduct3D(Vector3d A, Vector3d B);
	
//Points are represented as vectors (point = vector)
double GRAPHICSGEOMETRY_API TriangleArea2D(Vector3d A, Vector3d B, Vector3d C);
double GRAPHICSGEOMETRY_API TriangleArea3D(Vector3d A, Vector3d B, Vector3d C);

double GRAPHICSGEOMETRY_API GetAngle_rads(Vector3d A, Vector3d B);
double GRAPHICSGEOMETRY_API GetAngle_degs(Vector3d A, Vector3d B);

double GRAPHICSGEOMETRY_API GetProjectionLength2D(Vector3d A, Vector3d base);
Vector3d GRAPHICSGEOMETRY_API GetProjectionLength3D(Vector3d A, Vector3d base);