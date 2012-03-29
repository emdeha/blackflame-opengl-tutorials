#include "stdafx.h"
#include "Vector.h"

void Vector3d::SetX(float newX)
{
	this->x = newX;
}
void Vector3d::SetY(float newY)
{
	this->y = newY;
}
void Vector3d::SetZ(float newZ)
{
	this->z = newZ;
}

float Vector3d::GetX()
{
	return this->x;
}
float Vector3d::GetY()
{
	return this->y;
}
float Vector3d::GetZ()
{
	return this->z;
}

Vector3d Vector3d::operator +(const Vector3d &other)
{
	return Vector3d(this->x + other.x,
		this->y + other.y,
		this->z + other.z);
}
Vector3d Vector3d::operator -(const Vector3d &other)
{
	return Vector3d(this->x - other.x,
		this->y - other.y,
		this->z - other.z);
}
Vector3d Vector3d::operator *(const float &coef)
{
	return Vector3d(this->x * coef,
		this->y * coef,
		this->z * coef);
}
Vector3d Vector3d::operator /(const float &coef)
{
	return Vector3d(this->x / coef,
		this->y / coef,
		this->z / coef);
}

float Vector3d::GetLength()
{
	float xSquare = this->x * this->x,
		ySquare = this->y * this->y,
		zSquare = this->z * this->z;

	return xSquare + ySquare + zSquare;
}
float Vector3d::GetLengthSqrt()
{
	float xSquare = this->x * this->x,
		ySquare = this->y * this->y,
		zSquare = this->z * this->z;

	return sqrt(xSquare + ySquare + zSquare);
}
void Vector3d::Normalize()
{
	float vectorLength = this->GetLength();
	Vector3d normalized = (*this);
	(*this) = normalized / vectorLength;
}

void Vector3d::RotateXY(float angle_degs)
{
	float alpha = angle_degs * PI/180;
	float newX = this->x * cos(alpha) - this->y * sin(alpha);
	float newY = this->x * sin(alpha) + this->y * cos(alpha);
	this->y = newY;
	this->x = newX;
}
void Vector3d::RotateYZ(float angle_degs)
{
	double alpha = angle_degs * PI/180;
	float newY = this->y * cos(alpha) - this->z * sin(alpha);
	float newZ = this->y * sin(alpha) + this->z * cos(alpha);
	this->y = newY;
	this->z = newZ;
}
void Vector3d::RotateZX(float angle_degs)
{
	double alpha = angle_degs * PI/180;
	float newZ = this->z * cos(alpha) - this->x * sin(alpha);
	float newX = this->z * sin(alpha) + this->x * cos(alpha);
	this->z = newZ;
	this->x = newX;
}

void Vector3d::RotateAroundY(float angle_degs)
{
	this->RotateZX(angle_degs);
}
void Vector3d::RotateAroundX(float angle_degs)
{
	this->RotateYZ(angle_degs);
}
void Vector3d::RotateAroundZ(float angle_degs)
{
	this->RotateXY(angle_degs);
}

double DotProduct(Vector3d A, Vector3d B)
{
	double result = A.GetX() * B.GetX() + A.GetY() * B.GetY() + A.GetZ() * B.GetZ();
	return result;
}
double CrossProduct2D(Vector3d A, Vector3d B)
{
	double result = A.GetX() * B.GetY() - A.GetY() * B.GetX();
	return result;
}
Vector3d CrossProduct3D(Vector3d A, Vector3d B)
{
	Vector3d result;
	result.SetX(A.GetY() * B.GetZ() - A.GetZ() * B.GetY());
	result.SetY(A.GetZ() * B.GetX() - B.GetZ() * A.GetX());
	result.SetZ(A.GetX() * B.GetY() - B.GetX() * A.GetY());
	return result;
}

double TriangleArea2D(Vector3d A, Vector3d B, Vector3d C)
{
	Vector3d AB = B - A;
	Vector3d AC = C - A;
	double area = fabs(CrossProduct2D(AB, AC));
	area /= 2;
	return area;
}
double TriangleArea3D(Vector3d A, Vector3d B, Vector3d C)
{
	Vector3d AB = B - A;
	Vector3d AC = C - A;
	Vector3d cpResult = CrossProduct3D(AB, AC);
	return cpResult.GetLength() / 2;
}

double GetAngle_rads(Vector3d A, Vector3d B)
{
	A.Normalize();
	B.Normalize();
	double cosAngle = DotProduct(A, B);
	double angle_rads = acos(cosAngle);
	return angle_rads;
}
double GetAngle_degs(Vector3d A, Vector3d B)
{
	A.Normalize();
	B.Normalize();
	double cosAngle = DotProduct(A, B);
	double angle_rads = acos(cosAngle);
	double angle_degs = angle_rads * 180.0 / PI;
	return angle_degs;
}

double GetProjectionLength2D(Vector3d A, Vector3d base)
{
	double dpResult = DotProduct(A, base);
	double projectionLength = dpResult / base.GetLength();
	return projectionLength;
}
Vector3d GetProjectionLength3D(Vector3d A, Vector3d base)
{
	Vector3d projection = CrossProduct3D(A, base) / base.GetLength();
	Vector3d projection3d = CrossProduct3D(base, projection) / base.GetLength();
	return projection3d;
}