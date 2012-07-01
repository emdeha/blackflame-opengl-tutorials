
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Draw.h"
#include "Entities.h"
#include "Player.h"
#include "../Mouse/Mouse.h"
#include "../Camera/Camera.h"


#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


float g_fzNear = 1.0f;
float g_fzFar = 1000.0f;

ProgramData UniformColor;
ProgramData ObjectColor;
ProgramData UniformColorTint;

GLuint g_GlobalMatricesUBO;

static const int g_iGlobalMatricesBindingIndex = 0;

ProgramData LoadProgram(const std::string &strVertexShader, const std::string &strFragmentShader)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, strFragmentShader));

	ProgramData data;
	data.theProgram = Framework::CreateProgram(shaderList);
	data.modelToCameraMatrixUnif = glGetUniformLocation(data.theProgram, "modelToCameraMatrix");
	data.globalUniformBlockIndex = glGetUniformBlockIndex(data.theProgram, "GlobalMatrices");
	data.baseColorUnif = glGetUniformLocation(data.theProgram, "baseColor");

	glUniformBlockBinding(data.theProgram, data.globalUniformBlockIndex, g_iGlobalMatricesBindingIndex);

	return data;
}

void InitializeProgram()
{
	UniformColor = LoadProgram("\\shaders\\PosOnlyWorldTransformUBO.vert", "\\shaders\\ColorUniform.frag");
	ObjectColor = LoadProgram("\\shaders\\PosColorWorldTransformUBO.vert", "\\shaders\\ColorPassthrough.frag");
	UniformColorTint = LoadProgram("\\shaders\\PosColorWorldTransformUBO.vert", "\\shaders\\ColorMultUniform.frag");

	glGenBuffers(1, &g_GlobalMatricesUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, g_GlobalMatricesUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, g_iGlobalMatricesBindingIndex, g_GlobalMatricesUBO,
		0, sizeof(glm::mat4) * 2);
}

Framework::Mesh *g_pConeMesh = NULL;
Framework::Mesh *g_pCylinderMesh = NULL;
Framework::Mesh *g_pCubeTintMesh = NULL;
Framework::Mesh *g_pCubeColorMesh = NULL;
Framework::Mesh *g_pPlaneMesh = NULL;

Dynamic_Cylinder *g_treeVolumes = NULL;
Static_AABB g_parthenonBaseVolume = Static_AABB(glm::vec3(12.0f, 0.5f, 0.5f), 
												glm::vec3(28.0f, 0.5f, -20.5f));

#define COUNT 10
EntityTreasure littleTreasures[COUNT];

static glm::vec3 g_camTarget(0.0f, 2.0f, 0.0f);

//In spherical coordinates.
static glm::vec3 g_sphereCamRelPos(0.0f, 0.0f, 1.0f);

Mouse userMouse;
Camera userCamera(g_camTarget, g_sphereCamRelPos);
Player mainCharacter;

void HandleMouse()
{
	float deltaX = userMouse.GetCurrentPosition().x - userMouse.GetLastPosition().x;
	float deltaY = -(userMouse.GetCurrentPosition().y - userMouse.GetLastPosition().y);

	if(deltaX > 0.0)
	{
		mainCharacter.LookRight(deltaX);
	}
	else if(deltaX < 0.0)
	{
		mainCharacter.LookLeft(deltaX);
	}
	
	if(deltaY > 0.0)
	{
		mainCharacter.LookUp(deltaY);
	}
	else if(deltaY < 0.0)
	{
		mainCharacter.LookDown(deltaY);
	}
}

void HandlePassiveMovement(int x, int y)
{
	userMouse.SetCurrentPosition(glm::vec3((float)x, (float)y, 0.0f));
}
void HandleActiveMovement(int x, int y)
{
	userMouse.SetCurrentPosition(glm::vec3((float)x, (float)y, 0.0f));
}

void LoadCollisionVolumes()
{
	assert(ARRAY_COUNT(g_forest) > 0);
	int treeCount = ARRAY_COUNT(g_forest);

	g_treeVolumes = new Dynamic_Cylinder[treeCount];
	for(int tree = 0; tree < treeCount; tree++)
	{
		const TreeData &currTree = g_forest[tree];

		g_treeVolumes[tree].SetPosition(glm::vec3(currTree.fXPos, 0.0f, currTree.fZPos));
		g_treeVolumes[tree].SetHeight(currTree.fTrunkHeight);
		g_treeVolumes[tree].SetRadius(1.0f);
	}
}

void LoadTreasureEntities()
{
	for(int i = 0; i < COUNT; i++)
	{
		littleTreasures[i].SetPoints(rand() % 10);
		littleTreasures[i].LoadMesh("\\objects\\UnitCubeTint.xml");
		littleTreasures[i].AttachCollisionVolume(1.0f, 1.0f);
		littleTreasures[i].Spawn(g_parthenonBaseVolume, 
								 g_treeVolumes, ARRAY_COUNT(g_forest),
								 mainCharacter.GetCollisionVolume()); 
	}
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();

	try
	{
		g_pConeMesh = new Framework::Mesh("\\objects\\UnitConeTint.xml");
		g_pCylinderMesh = new Framework::Mesh("\\objects\\UnitCylinderTint.xml");
		g_pCubeTintMesh = new Framework::Mesh("\\objects\\UnitCubeTint.xml");
		g_pCubeColorMesh = new Framework::Mesh("\\objects\\UnitCubeColor.xml");
		g_pPlaneMesh = new Framework::Mesh("\\objects\\UnitPlane.xml");
	}
	catch(std::exception &except)
	{
		printf("%s\n", except.what());
		throw;
	}

	LoadCollisionVolumes();

	mainCharacter.AttachCamera(userCamera);
	mainCharacter.AttachCollisionVolume_Cylinder();
	
	LoadTreasureEntities();

 	glutPassiveMotionFunc(HandlePassiveMovement);
	glutMotionFunc(HandleActiveMovement);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_DEPTH_CLAMP);
}

glutil::MatrixStack g_camMatrix;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(g_pConeMesh && g_pCylinderMesh && g_pCubeTintMesh && g_pCubeColorMesh && g_pPlaneMesh)
	{
		g_camMatrix.SetMatrix(mainCharacter.AcquireCamera().CalcLookAtMatrix());

		glutil::MatrixStack modelMatrix;

		//Render the ground plane.
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.ApplyMatrix(g_camMatrix.Top());

			modelMatrix.Scale(glm::vec3(100.0f, 1.0f, 100.0f));

			glUseProgram(UniformColor.theProgram);
			glUniformMatrix4fv(UniformColor.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
			glUniform4f(UniformColor.baseColorUnif, 0.302f, 0.416f, 0.0589f, 1.0f);
			g_pPlaneMesh->Render();
			glUseProgram(0);
		}

		//Draw the trees
		DrawForest(UniformColorTint, modelMatrix, g_camMatrix);

		//Draw the building.
		{
			glutil::PushStack push(modelMatrix);
			modelMatrix.ApplyMatrix(g_camMatrix.Top());

			modelMatrix.Translate(glm::vec3(20.0f, 0.0f, -10.0f));

			DrawParthenon(UniformColorTint, ObjectColor, modelMatrix);
		}

		//Draw the treasure
		for(int i = 0; i < COUNT; i++)
		{
			if(littleTreasures[i].IsRemoved() == false)
			{
				glutil::PushStack push(modelMatrix);
				modelMatrix.ApplyMatrix(g_camMatrix.Top());
			
				littleTreasures[i].Update();
				littleTreasures[i].Render(UniformColorTint, modelMatrix);
			}
			else
			{
				littleTreasures[i].Spawn(g_parthenonBaseVolume, g_treeVolumes, ARRAY_COUNT(g_forest), mainCharacter.GetCollisionVolume()); 
			}
		}
	}

	HandleMouse();

	glutPostRedisplay();
	glutSwapBuffers();

	userMouse.OverrideLastPosition(userMouse.GetCurrentPosition());
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(45.0f, (w / (float)h), g_fzNear, g_fzFar);

	glBindBuffer(GL_UNIFORM_BUFFER, g_GlobalMatricesUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(persMatrix.Top()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glutPostRedisplay();
}

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		delete g_pConeMesh;
		g_pConeMesh = NULL;
		delete g_pCylinderMesh;
		g_pCylinderMesh = NULL;
		delete g_pCubeTintMesh;
		g_pCubeTintMesh = NULL;
		delete g_pCubeColorMesh;
		g_pCubeColorMesh = NULL;
		delete g_pPlaneMesh;
		g_pPlaneMesh = NULL;
		glutLeaveMainLoop();
		return;
	case 'w':
		mainCharacter.MoveForward(0.5f, g_treeVolumes, ARRAY_COUNT(g_forest), 
													   g_parthenonBaseVolume);
		for(int i = 0; i < COUNT; i++)
		{
			littleTreasures[i].DetectCollisions(mainCharacter.GetCollisionVolume());
		}
		break;
	case 's':
		mainCharacter.MoveBackward(0.5f, g_treeVolumes, ARRAY_COUNT(g_forest), 
														g_parthenonBaseVolume);
		for(int i = 0; i < COUNT; i++)
		{
			littleTreasures[i].DetectCollisions(mainCharacter.GetCollisionVolume());
		}
		break;
	case 'a':
		mainCharacter.MoveLeft(0.5f, g_treeVolumes, ARRAY_COUNT(g_forest),
													g_parthenonBaseVolume);
		for(int i = 0; i < COUNT; i++)
		{
			littleTreasures[i].DetectCollisions(mainCharacter.GetCollisionVolume());
		}
		break;
	case 'd':
		mainCharacter.MoveRight(0.5f, g_treeVolumes, ARRAY_COUNT(g_forest), 
													 g_parthenonBaseVolume);
		for(int i = 0; i < COUNT; i++)
		{
			littleTreasures[i].DetectCollisions(mainCharacter.GetCollisionVolume());
		}
		break;
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}