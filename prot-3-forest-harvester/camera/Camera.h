#ifdef CAMERA_EXPORTS
#define CAMERA_API __declspec(dllexport)
#else
#define CAMERA_API __declspec(dllimport)
#endif

#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>

class CAMERA_API Camera
{	
private:
	glm::vec3 sphereCamRelPos;
	glm::vec3 camPos;
	
	glm::vec3 camTarget;	
	glm::vec3 upVector;

public:
	Camera();
	Camera(glm::vec3 newCamTarget, glm::vec3 newSphereCamRelPos);

	glm::mat4 CalcLookAtMatrix();

	glm::vec3 GetPosition();
	glm::vec3 GetForwardVector();
	glm::vec3 GetRightVector();

	void LookLeft(float angle_degs);
	void LookRight(float angle_degs);
	void LookUp(float angle_degs);
	void LookDown(float angle_degs);

	void MoveForward(float units);
	void MoveBackward(float units);
	void MoveLeft(float units);
	void MoveRight(float units);

private:
	glm::vec3 ResolveCamPosition();
};

#endif