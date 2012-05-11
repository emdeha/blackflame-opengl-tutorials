
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include "../Mouse/Mouse.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Framework.h"
#include "MatrixOperations.h"
#include "SceneObjects.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

GLuint theProgram;
GLuint positionAttrib;
GLuint colorAttrib;

GLuint modelToCameraMatrixUnif;
GLuint cameraToClipMatrixUnif;

glm::mat4 cameraToClipMatrix(0.0f);

float CalcFrustumScale(float fFovDeg)
{
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	float fFovRad = fFovDeg * degToRad;
	return 1.0f / tan(fFovRad / 2.0f);
}

const float fFrustumScale = CalcFrustumScale(45.0f);


void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "PosColorLocalTransform.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "ColorPassthrough.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	positionAttrib = glGetAttribLocation(theProgram, "position");
	colorAttrib = glGetAttribLocation(theProgram, "color");

	modelToCameraMatrixUnif = glGetUniformLocation(theProgram, "modelToCameraMatrix");
	cameraToClipMatrixUnif = glGetUniformLocation(theProgram, "cameraToClipMatrix");

	float fzNear = 1.0f; float fzFar = 100.0f;

	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);
}

const int numberOfVertices = 24;
const int numberOfVerticesBound = 16;
const int numberOfVerticesPaddle = 4;

#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f

#define YELLOW_COLOR 1.0f, 1.0f, 0.0f, 1.0f
#define CYAN_COLOR 0.0f, 1.0f, 1.0f, 1.0f
#define MAGENTA_COLOR 	1.0f, 0.0f, 1.0f, 1.0f

const float vertexDataBound[] =
{
	//Front
	+1.0f, +1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	//Top
	+1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,

	//Back
	+1.0f, +1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	//Bottom
	+1.0f, -1.0f, +1.0f,
	+1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, +1.0f,

	YELLOW_COLOR,
	YELLOW_COLOR,
	YELLOW_COLOR,
	YELLOW_COLOR,

	CYAN_COLOR,
	CYAN_COLOR,
	CYAN_COLOR,
	CYAN_COLOR,

	YELLOW_COLOR,
	YELLOW_COLOR,
	YELLOW_COLOR,
	YELLOW_COLOR,

	CYAN_COLOR,
	CYAN_COLOR,
	CYAN_COLOR,
	CYAN_COLOR,
};

const GLshort indexDataBound[] =
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

const float vertexDataPaddle[] =
{
	+1.0f, +1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	MAGENTA_COLOR,
	MAGENTA_COLOR,
	MAGENTA_COLOR,
	MAGENTA_COLOR,
};

const GLshort indexDataPaddle[] =
{
	0, 1, 2,
	2, 3, 0,
};

const float vertexData[] =
{
	//Front
	+1.0f, +1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	//Top
	+1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,

	//Left
	+1.0f, +1.0f, +1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,

	//Back
	+1.0f, +1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	//Bottom
	+1.0f, -1.0f, +1.0f,
	+1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, +1.0f,

	//Right
	-1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
};

const GLshort indexData[] =
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

Mouse userMouse;

Paddle pad1(-2.0f);
Paddle pad2(-5.8f);
BoxBall ball(glm::vec3(0.0f, 0.0f, -0.05f));

void HandleMouse()
{
	double deltaX = userMouse.GetCurrentPosition().GetX() - userMouse.GetLastPosition().GetX();
	double deltaY = -(userMouse.GetCurrentPosition().GetY() - userMouse.GetLastPosition().GetY());

	// TODO: Mouse reaches border => pad can't move correctly
	if(deltaX > 0.0)
	{
		pad1.MoveX(deltaX / 290.0f);
	}
	else if(deltaX < 0.0)
	{
		pad1.MoveX(deltaX / 290.0f);
	}

	if(deltaY > 0.0)
	{
		pad1.MoveY(deltaY / 290.0f); 
	}
	else if(deltaY < 0.0)
	{
		pad1.MoveY(deltaY / 290.0f);
	}

	if(userMouse.IsLeftButtonDown() && ball.IsInPaddle(pad1))
	{
		pad1.SetMiss(false);
		pad2.SetMiss(false);
	}

	userMouse.OverrideLastPosition(userMouse.GetCurrentPosition());
	userMouse.ReleaseLeftButton();
	glutSetCursor(GLUT_CURSOR_NONE);
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

GLuint vao;
GLuint indexBufferObject;
GLuint vertexBufferObject;


GLuint vertexBufferObjectBound;
GLuint indexBufferObjectBound;
GLuint vaoBound;


GLuint vertexBufferObjectPaddle;
GLuint indexBufferObjectPaddle;
GLuint vaoPaddle;

GLuint vertexBufferObjectBall;
GLuint indexBufferObjectBall;
GLuint vaoBall;

void InitializeVAOBound()
{
	glGenBuffers(1, &vertexBufferObjectBound);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectBound);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexDataBound), vertexDataBound, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObjectBound);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectBound);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexDataBound), indexDataBound, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoBound);
	glBindVertexArray(vaoBound);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVerticesBound;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectBound);
	glEnableVertexAttribArray(positionAttrib);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectBound);

	glBindVertexArray(0);
}

void InitializeVAOPaddle()
{
	glGenBuffers(1, &vertexBufferObjectPaddle);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectPaddle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexDataPaddle), vertexDataPaddle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObjectPaddle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectPaddle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexDataPaddle), indexDataPaddle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoPaddle);
	glBindVertexArray(vaoPaddle);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVerticesPaddle;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectPaddle);
	glEnableVertexAttribArray(positionAttrib);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectPaddle);

	glBindVertexArray(0);
}

void InitializeVAOBall()
{
	glGenBuffers(1, &vertexBufferObjectBall);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectBall);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObjectBall);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectBall);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoBall);
	glBindVertexArray(vaoBall);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectBall);
	glEnableVertexAttribArray(positionAttrib);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectBall);

	glBindVertexArray(0);
}

void InitializeVAO()
{
	InitializeVAOBound();
	InitializeVAOPaddle();
	InitializeVAOBall();
}

void InitPads()
{
	pad1.LockAndLoad();
	pad1.SetMiss(true);
	pad2.LockAndLoad();
	pad2.SetAI(true);
}

void Init()
{
	InitializeProgram();
	InitializeVAO();
	InitPads();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	glutPassiveMotionFunc(HandlePassiveMovement);
	glutMotionFunc(HandleActiveMovement);
	glutMouseFunc(HandleMouseButtons);
}

glm::mat4 transform;
glm::mat4 transformPad2;
glm::mat4 transformBound;
glm::mat4 transformBall;

void InitMatrices()
{
	transform = glm::mat4(1.0f);
	transformPad2 = glm::mat4(1.0f);
	transformBound = glm::mat4(1.0f);
	transformBall = glm::mat4(1.0f);
}

void RenderScene()
{
	pad1.Render(transform, theProgram, vaoPaddle, modelToCameraMatrixUnif);
	pad2.Render(transformPad2, theProgram, vaoPaddle, modelToCameraMatrixUnif);

	ball.Render(transformBall, theProgram, vaoBall, modelToCameraMatrixUnif);
	
	Boundary::Render(transformBound, theProgram, vaoBound, modelToCameraMatrixUnif);
}
void UpdateScene()
{
	if(ball.GetPosition().z <= -3.9f)
	{
		pad2.Update(ball.GetPosition());
	}
	ball.Update(pad1, true);
	ball.Update(pad2, false);
}

void Display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	InitMatrices();
	
	UpdateScene();
	RenderScene();

	HandleMouse();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(int w, int h)
{
	cameraToClipMatrix[0].x = fFrustumScale * (h / (float)w);
	cameraToClipMatrix[1].y = fFrustumScale;

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);

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
