#include "Framework.h"
#include "../Mouse/Mouse.h"
#include "Object.h"

#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <string.h>

Mouse userMouse;


const float vertexPositionsOne[] = {
	0.1f, 0.1f, 0.0f, 1.0f,
	0.1f, -0.1f, 0.0f, 1.0f,
	-0.1f, 0.1f, 0.0f, 1.0f,
	-0.1f, -0.1f, 0.0f, 1.0f,
	0.1f, -0.1f, 0.0f, 1.0f,
	-0.1f, 0.1f, 0.0f, 1.0f,
};

Object obj = Object(Vector3d(vertexPositionsOne[12], vertexPositionsOne[13]),
					Vector3d(vertexPositionsOne[0], vertexPositionsOne[1]));

void HandleMouse()
{
	//if(userMouse.IsLeftButtonDown())
		obj.Click(userMouse.GetCurrentPosition());
}
void HandleMouseButtons(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		userMouse.PressLeftButton();
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		userMouse.ReleaseLeftButton();
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		userMouse.PressRightButton();
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		userMouse.ReleaseRightButton();
	}
}
void HandlePassiveMovement(int x, int y)
{
	userMouse.SetCurrentPosition(Vector3d(x, y));
}
void HandleActiveMovement(int x, int y)
{
	userMouse.SetCurrentPosition(Vector3d(x, y));
}


GLuint theProgram;

GLuint offsetUniform;
GLuint colorUniform;

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "vertexShader.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "fragShader.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	offsetUniform = glGetUniformLocation(theProgram, "offset");
	colorUniform = glGetUniformLocation(theProgram, "inputColor");

	glUseProgram(0);
}

GLuint vao;
GLuint positionBufferObject;

void InitializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionsOne), vertexPositionsOne, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	obj.SetBO(positionBufferObject);
}

void Init()
{
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Display()
{
	obj.Update();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	HandleMouse();

	obj.Render(theProgram, offsetUniform, colorUniform);

	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

unsigned int Defaults(unsigned int displayMode, int &width, int &height) 
{
	return displayMode;
}