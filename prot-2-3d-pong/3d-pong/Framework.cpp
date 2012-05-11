#include "Framework.h"

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string.h>

#ifdef WIN32
#define LOCAL_FILE_DIR "data\\"
#define GLOBAL_FILE_DIR "..\\data\\"
#endif //WIN32

#ifdef LOAD_X11
#define LOCAL_FILE_DIR "data/"
#define GLOBAL_FILE_DIR "../data/"
#endif //LOAD_X11

#ifdef LOAD_X11
#define APIENTRY
#endif

namespace Framework
{
	GLuint LoadShader(GLenum shaderType, const std::string &shaderFileName)
	{
		std::string fileName = FindFile(shaderFileName);
		std::ifstream shaderFile(fileName.c_str());
		std::stringstream shaderData;
		shaderData<<shaderFile.rdbuf();
		shaderFile.close();

		try
		{
			return glutil::CompileShader(shaderType, shaderData.str());
		}
		catch(std::exception &ex)
		{
			fprintf(stderr, "%s\n", ex.what());
			throw;
		}
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
	{
		try
		{
			return glutil::LinkProgram(shaderList);
		}
		catch(std::exception &ex)
		{
			fprintf(stderr, "%s\n", ex.what());
			throw;
		}

		std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
	}

	float DegreesToRadians(float angle_degs)
	{
		const float degsToRads = 3.14159f * 2.0f / 360.0f;
		return angle_degs * degsToRads;
	}

	std::string FindFile(const std::string &baseName)
	{
		std::string fileName = LOCAL_FILE_DIR + baseName;
		std::ifstream testFile(fileName.c_str());
		if(testFile.is_open())
			return fileName;

		fileName = GLOBAL_FILE_DIR + baseName;
		testFile.open(fileName.c_str());
		if(testFile.is_open())
			return fileName;

		throw std::runtime_error("Could not find the file " + baseName);
	}
}


void Init();
void Display();
void Reshape(int width, int height);
void Keyboard(unsigned char key, int x, int y);

unsigned int Defaults(unsigned int DisplayMode, int &width, int &height);


void APIENTRY DebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
						const GLchar *message, GLvoid *userParameter)
{
	std::string sourceName;
	switch(source)
	{
	case GL_DEBUG_SOURCE_API_ARB: sourceName = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: sourceName = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: sourceName = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: sourceName = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION_ARB: sourceName = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER_ARB: sourceName = "Other"; break;
	}

	std::string errorType;
	switch(type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB: errorType = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: errorType = "Deprecated Functionality"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: errorType = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB: errorType = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: errorType = "Performance"; break;
	case GL_DEBUG_TYPE_OTHER_ARB: errorType = "Other"; break;
	}

	std::string typeSeverity;
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB: typeSeverity = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: typeSeverity = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW_ARB: typeSeverity = "Low"; break;
	}

	printf("%s from %s, \t%s priority\nMessage: %s\n", 
		   errorType.c_str(), sourceName.c_str(), typeSeverity.c_str(), message);
}

void InitializeWindow(int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("OpenGL");
}

void InitializeGL()
{
	int width = 800;
	int height = 500;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
	displayMode = Defaults(displayMode, width, height);

	glutInitDisplayMode(displayMode);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	InitializeWindow(width, height);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	glload::LoadFunctions();

	if(glext_ARB_debug_output)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(DebugFunc, (void*)15);
	}
}

void RegisterCallbacks()
{
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
}

void GetScreenResolution(int &horizontal, int &vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}

char* MakeGameModeString()
{
	DEVMODE *devMode = new DEVMODE;
	devMode->dmSize = sizeof(DEVMODE);
	devMode->dmDriverExtra = 0;

	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, devMode); 

	int freq = devMode->dmDisplayFrequency;

	int horizontal = 0;
	int vertical = 0;
	GetScreenResolution(horizontal, vertical);

	char *chHorizontal = new char;
	char *chVertical = new char;
	char *chFreq = new char;

	itoa(horizontal, chHorizontal, 10);
	itoa(vertical, chVertical, 10);
	itoa(freq, chFreq, 10);

	char *gameModeString = new char;
	strcpy(gameModeString, chHorizontal);
	strcat(gameModeString, "x");
	strcat(gameModeString, chVertical);
	strcat(gameModeString, ":32@");
	strcat(gameModeString, chFreq);

	return gameModeString;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	InitializeGL();

	std::printf(MakeGameModeString());

	//glutGameModeString(MakeGameModeString());
	//glutEnterGameMode();
	
	Init();
	RegisterCallbacks();

	glutMainLoop();

	return 0;
}