#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 interpColor;

//Task one:
//uniform mat4 modelToWorldMatrix;
//uniform mat4 worldToClipMatrix;

//Task two:
uniform mat4 modelToCameraMatrix;
uniform mat4 cameraToClipMatrix;

//Original:
//uniform mat4 modelToWorldMatrix;
//uniform mat4 worldToCameraMatrix;
//uniform mat4 cameraToClipMatrix;

void main()
{
	//Original:
	//vec4 temp = modelToWorldMatrix * position;
	//temp = worldToCameraMatrix * temp;
	//gl_Position = cameraToClipMatrix * temp;

	//Task one:
	//vec4 temp = modelToWorldMatrix * position;
	//gl_Position = worldToClipMatrix * temp;

	//Task two:
	vec4 temp = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * temp;


	interpColor = color;
}
