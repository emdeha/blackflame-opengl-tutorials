#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

#pragma once 

#include "Framework.h"
#include "MatrixOperations.h"
#include <glm/glm.hpp>


#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f

#define YELLOW_COLOR 1.0f, 1.0f, 0.0f, 1.0f
#define CYAN_COLOR 0.0f, 1.0f, 1.0f, 1.0f
#define MAGENTA_COLOR 	1.0f, 0.0f, 1.0f, 1.0f


const GLshort indexDataPaddleH[] =
{
	0, 1, 2,
	2, 3, 0,
};

const GLshort indexDataBoundH[] =
{
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,
};

const GLshort indexDataBallH[] =
{
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,

	16, 17, 18,
	18, 19, 16,

	20, 21, 22,
	22, 23, 20,
};


class Paddle
{
private:
	glm::vec3 position;
	glm::vec3 minCorner;
	glm::vec3 maxCorner;

	float offsetX;
	float offsetY;
	float prevOffsetX;
	float prevOffsetY;

	bool isLockedAndLoaded;
	bool isMiss;
	bool isAI;

public:
	Paddle(float zPosition = 1.0f);

	void Render(glm::mat4 &transform, 
				GLuint shaderProgram, GLuint vao, 
				GLuint matrixUnif);
	void Update(glm::vec3 ballPosition);

	void MoveX(float delta);
	void MoveY(float delta);

	glm::vec3 GetPosition();
	glm::vec3 GetMinCorner();
	glm::vec3 GetMaxCorner();
	float GetDifferenceX();
	float GetDifferenceY();
	float GetOffsetX();
	float GetOffsetY();
	bool IsLockedAndLoaded();
	bool IsMiss();

	void LockAndLoad();
	void UnLockAndLoad();

	void SetAI(bool newIsAI);
	void SetMiss(bool newIsMiss);
};

class BoxBall
{
private:
	glm::vec3 position;
	glm::vec3 velocity;

public:
	BoxBall(glm::vec3 newVelocity);

	bool IsInPaddle(Paddle &pad);

	void Render(glm::mat4 &transform,
				GLuint shaderProgram, GLuint vao,
				GLuint matrixUnif);
	void Update(Paddle &pad, bool isFirst);

	glm::vec3 GetPosition();

private:
	void CheckCollision(Paddle &pad, bool isFirst);
	void CheckWallCollision(Paddle &pad);
	void CheckPaddleCollision(Paddle &pad, bool isFirst);
};

class Boundary
{
public:
	static void Render(glm::mat4 &transform, 
					   GLuint shaderProgram, GLuint vao,
				       GLuint matrixUnif);
};

#endif