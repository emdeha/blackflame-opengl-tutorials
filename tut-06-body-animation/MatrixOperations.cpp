#include "MatrixOperations.h"

inline float Transform::DegToRad(float angle_degs)
{
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	return angle_degs * degToRad;
}

glm::mat4 Transform::RotateX(float angle_degs)
{
	float angle_rads = DegToRad(angle_degs);
	float cos = cosf(angle_rads);
	float sin = sinf(angle_rads);

	glm::mat3 rotMat(1.0f);
	rotMat[1].y = cos; rotMat[2].y = -sin;
	rotMat[1].z = sin; rotMat[2].z = cos;

	return glm::mat4(rotMat);
}
glm::mat4 Transform::RotateY(float angle_degs)
{
	float angle_rads = DegToRad(angle_degs);
	float cos = cosf(angle_rads);
	float sin = sinf(angle_rads);

	glm::mat3 rotMat(1.0f);
	rotMat[0].x = cos; rotMat[2].x = sin;
	rotMat[0].z = -sin; rotMat[2].z = cos;

	return glm::mat4(rotMat);
}
glm::mat4 Transform::RotateZ(float angle_degs)
{
	float angle_rads = DegToRad(angle_degs);
	float cos = cosf(angle_rads);
	float sin = sinf(angle_rads);

	glm::mat3 rotMat(1.0f);
	rotMat[0].x = cos; rotMat[1].x = -sin;
	rotMat[0].y = sin; rotMat[1].y = cos;

	return glm::mat4(rotMat);
}

glm::mat4 Transform::Scale(const glm::vec3 &scaleVector)
{
	glm::mat4 scaleMat(1.0f);
	scaleMat[0].x = scaleVector.x;
	scaleMat[1].y = scaleVector.y;
	scaleMat[2].z = scaleVector.z;

	return scaleMat;
}

glm::mat4 Transform::Translate(const glm::vec3 &offsetVector)
{
	glm::mat4 translationMat(1.0f);
	translationMat[3].x = offsetVector.x;
	translationMat[3].y = offsetVector.y;
	translationMat[3].z = offsetVector.z;

	return translationMat;
}