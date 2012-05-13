#ifndef HIERARCHY_H
#define HIERARCHY_H

#pragma once

#include "MatrixStack.h"

#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include <glload/gl_3_3.h>
#include <glload/gll.hpp>
#include <gl/freeglut.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

const GLshort indexDataH[] =
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

class RootNode;

class Node
{
private:
	glm::vec3 position;
	glm::vec3 axisPosition;
	glm::vec3 scale;

	float animAngleMinX_degs;
	float animAngleMaxX_degs;
	float animAngleMinY_degs;
	float animAngleMaxY_degs;
	float animAngleMinZ_degs;
	float animAngleMaxZ_degs;

	float angleX_degs;
	float angleY_degs;
	float angleZ_degs;

	float decrement;

	std::vector<Node*> childNodes;
	Node *parent;

public:
	Node();
	Node(glm::vec3 newPosition, glm::vec3 newAxisPosition, glm::vec3 newScale, 
		 float newAngleX_degs, float newAngleY_degs, float newAngleZ_degs,
		 float newAnimAngleMinX_degs = 0.0f, float newAnimAngleMaxX_degs = 0.0f,
		 float newAnimAngleMinY_degs = 0.0f, float newAnimAngleMaxY_degs = 0.0f,
		 float newAnimAngleMinZ_degs = 0.0f, float newAnimAngleMaxZ_degs = 0.0f,
		 float newDecrement = 1.0f);

	static void RenderWithoutMatrixStack(Node *node, glm::mat4 &matrix, GLuint matrixUnif);
	static void Render(Node *node, MatrixStack &stack, GLuint matrixUnif);

	static void Update(Node *node);

	void AdjustAngX(bool increment, float minVal, float maxVal);
	void AdjustAngY(bool increment, float minVal, float maxVal);
	void AdjustAngZ(bool increment, float minVal, float maxVal);

	void AdjustAnimAngleX();
	void AdjustAnimAngleY();
	void AdjustAnimAngleZ();

	void AddChild(Node *child);
};

class RootNode
{
private:
	glm::vec3 position;

	float angleX_degs;
	float angleY_degs;
	float angleZ_degs;

	std::vector<Node *> childNodes;

public:
	RootNode();
	RootNode(glm::vec3 newPosition,
			 float newAngleX_degs, float newAngleY_degs, float newAngleZ_degs);

	void RenderWithoutMatrixStack(GLuint shaderProgram, GLuint vao, GLuint matrixUnif);
	void Render(GLuint shaderProgram, GLuint vao, GLuint matrixUnif);

	void Update();

	void AdjustAngX(bool increment, float minVal, float maxVal);
	void AdjustAngY(bool increment, float minVal, float maxVal);
	void AdjustAngZ(bool increment, float minVal, float maxVal);

	void AddChild(Node *child);
};

#endif