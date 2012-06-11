#ifndef DRAW_H
#define DRAW_H

#include <glload/gl_3_3.h>
#include <glutil/glutil.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"

extern Framework::Mesh *g_pConeMesh;
extern Framework::Mesh *g_pCylinderMesh;
extern Framework::Mesh *g_pCubeTintMesh;
extern Framework::Mesh *g_pCubeColorMesh;
extern Framework::Mesh *g_pPlaneMesh;


struct ProgramData
{
	GLuint theProgram;
	GLuint globalUniformBlockIndex;
	GLuint modelToCameraMatrixUnif;
	GLuint baseColorUnif;
	GLuint thing;
};


extern void DrawTree(ProgramData data, glutil::MatrixStack &modelMatrix, float fTrunkHeight = 2.0f, float fConeHeight = 3.0f);
extern void DrawForest(ProgramData data, glutil::MatrixStack &modelMatrix, glutil::MatrixStack camMatrix);


extern void DrawColumn(ProgramData dataColorTint, glutil::MatrixStack &modelMatrix, float fHeight = 5.0f);
extern void DrawParthenon(ProgramData data, ProgramData dataObject, glutil::MatrixStack &modelMatrix);


#endif