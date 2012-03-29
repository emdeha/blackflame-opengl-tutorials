#include "Object.h"

Object::Object()
{
	minCorner = Vector3d();
	maxCorner = Vector3d();

	positionBufferObject = 0;

	offsetX = 0.0f;
	offsetY = 0.0f;

	isClicked = false;
}

Object::Object(Vector3d newMinCorner, Vector3d newMaxCorner)
{
	minCorner = newMinCorner;
	maxCorner = newMaxCorner;

	positionBufferObject = 0;

	offsetX = 0.0f;
	offsetY = 0.0f;

	isClicked = false;
}

void Object::Render(GLuint shaderProgram, GLuint offsetUniform, 
										  GLuint colorUniform)
{
	glUseProgram(shaderProgram);

	glUniform2f(offsetUniform, offsetX, offsetY);
	if(isClicked)
	{
		float color[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		glUniform4f(colorUniform, color[0], color[1], color[2], color[3]);
	}
	else
	{
		float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glUniform4f(colorUniform, color[0], color[1], color[2], color[3]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

void Object::Update()
{
	const float fLoopDuration = 20.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

	offsetX = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
	offsetY = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}

void Object::Click(Vector3d currMousePos)
{
	float minPosX = (minCorner.GetX() * 2.0f + offsetX / 0.5f) * 125.0f + 250.0f;
	float minPosY = fabs((minCorner.GetY() * 2.0f + offsetY / 0.5f) * 125.0f - 250.0f);
	float maxPosX = (maxCorner.GetX() * 2.0f + offsetX / 0.5f) * 125.0f + 250.0f;
	float maxPosY = fabs((maxCorner.GetY() * 2.0f + offsetY / 0.5f) * 125.0f - 250.0f);

	float mouseX = currMousePos.GetX();
	float mouseY = currMousePos.GetY();

	if(mouseX < maxPosX && 
	   mouseX > minPosX &&
	   mouseY > maxPosY && 
	   mouseY < minPosY)
	{
		isClicked = true;
	}
	else
	{
		isClicked = false;
	}
}

bool Object::IsClicked()
{
	return isClicked;
}

void Object::SetBO(GLuint newPositionBufferObject)
{
	positionBufferObject = newPositionBufferObject;
}