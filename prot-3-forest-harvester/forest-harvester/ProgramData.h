#ifndef PROGRAM_DATA
#define PROGRAM_DATA

#include <glload/gl_3_3.h>
#include <glutil/glutil.h>
#include <GL/freeglut.h>

struct ProgramData
{
	GLuint theProgram;
	GLuint globalUniformBlockIndex;
	GLuint modelToCameraMatrixUnif;
	GLuint baseColorUnif;
};

#endif