#ifdef FRAMEWORK_EXPORTS
#define FRAMEWORK_API __declspec(dllexport)
#else
#define FRAMEWORK_API __declspec(dllimport)
#endif

#pragma once

#include <vector>
#include <string>

#include <glload/gl_3_3.h>
#include <glload/gll.hpp>
#include <glutil/Shader.h>
#include <gl/freeglut.h>

#define ARRAY_COUNT(array)(sizeof(array) / (sizeof(array[0]) * (sizeof(array) != sizeof(void*) || sizeof(array[0]) <= sizeof(void))))

namespace Framework
{
	float DegreesToRadians(float angle_degs);

	GLuint CreateShader(GLenum shaderType, 
		const std::string &shaderFileName, const std::string &shaderName);
	GLuint LoadShader(GLenum shaderType, const std::string &shaderFileName);

	// Will "delete" the shaders given.
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);

	// Will find a file with the given base file name, eiter in the local directory or the global one.
	// If it doesn't, it will throw a std::runtime_error.
	std::string FindFile(const std::string &baseName);
}