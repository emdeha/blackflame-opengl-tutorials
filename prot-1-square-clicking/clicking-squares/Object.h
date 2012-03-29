#ifndef OBJECT_H
#define OBJECT_H

#include "../GraphicsGeometry/Vector.h"

#include <glload/gl_3_3.h>
#include <glload/gll.hpp>
#include <glutil/Shader.h>
#include <gl/freeglut.h>

class Object
{
private:
	Vector3d minCorner;
	Vector3d maxCorner;

	GLuint positionBufferObject;

	float offsetX;
	float offsetY;

	bool isClicked;

public:
	Object();
	Object(Vector3d newMinCorner, Vector3d newMaxCorner);

	void Render(GLuint shaderProgram, GLuint offsetUniform, 
									  GLuint colorUniform);
	void Update();

	bool IsClicked();
	void SetBO(GLuint newPositionBufferObject);

	void Click(Vector3d currMousePos);
};

#endif