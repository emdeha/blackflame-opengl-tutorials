#include "stdafx.h"
#include "Camera.h"
#include <iostream>

static float DegToRad(float angle_degs)
{
	const float fDegToRad = 3.14159f * 2.0f / 360.0f;
	return angle_degs * fDegToRad;
}

Camera::Camera()
{
	camTarget = glm::vec3();
	sphereCamRelPos = glm::vec3();
	camPos = glm::vec3();

	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}
Camera::Camera(glm::vec3 newCamTarget, glm::vec3 newSphereCamRelPos)
{
	camTarget = newCamTarget;
	sphereCamRelPos = newSphereCamRelPos;
	camPos = ResolveCamPosition();

	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Camera::ResolveCamPosition()
{
	float phi = DegToRad(sphereCamRelPos.x);
	float theta = DegToRad(sphereCamRelPos.y + 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	return (dirToCamera * sphereCamRelPos.z) + camTarget;
}

glm::mat4 Camera::CalcLookAtMatrix()
{
	glm::vec3 lookDir = glm::normalize(camTarget - camPos);
	glm::vec3 upDir = glm::normalize(glm::vec3(upVector));

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f);

	rotMat = glm::transpose(rotMat);

	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-camPos, 1.0f);

	return rotMat * transMat;
}

glm::vec3 Camera::GetPosition()
{
	return camPos;
}
glm::vec3 Camera::GetForwardVector()
{
	glm::vec3 forwardVector = glm::vec3(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::normalize(forwardVector);

	return forwardVector;
}
glm::vec3 Camera::GetRightVector()
{
	glm::vec3 forwardVector = this->GetForwardVector();
	glm::vec3 rightVector = glm::cross(forwardVector, upVector);
	glm::normalize(rightVector);

	return rightVector;
}

void Camera::LookDown(float angle_degs)
{
	sphereCamRelPos.y += angle_degs;
	sphereCamRelPos.y = glm::clamp(sphereCamRelPos.y, -78.75f, -1.0f);
	camPos = ResolveCamPosition();
}
void Camera::LookUp(float angle_degs)
{
	sphereCamRelPos.y += angle_degs;
	sphereCamRelPos.y = glm::clamp(sphereCamRelPos.y, -78.75f, -1.0f);
	camPos = ResolveCamPosition();
}
void Camera::LookLeft(float angle_degs)
{
	sphereCamRelPos.x += angle_degs;
	camPos = ResolveCamPosition();
}
void Camera::LookRight(float angle_degs)
{
	sphereCamRelPos.x += angle_degs;
	camPos = ResolveCamPosition();
}

void Camera::MoveForward(float units)
{
	glm::vec3 forwardVector = glm::vec3(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::normalize(forwardVector);	

	camTarget += units * forwardVector;
	camPos = ResolveCamPosition();
}
void Camera::MoveBackward(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::normalize(forwardVector);
	
	camTarget -= units * forwardVector;
	camPos = ResolveCamPosition();
}
void Camera::MoveLeft(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::vec3 rightVector = glm::cross(forwardVector, upVector);
	glm::normalize(rightVector);

	camTarget -= units * rightVector;
	camPos = ResolveCamPosition();
}
void Camera::MoveRight(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::vec3 rightVector = glm::cross(forwardVector, upVector);
	glm::normalize(rightVector);

	camTarget += units * rightVector;
	camPos = ResolveCamPosition();
}