// The end vertex shader
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

void main()
{
	gl_Position = position;
	theColor = color;
}


/*
// The task vertex shader. Uncomment it and comment the other.
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;
smooth out vec4 theColorEnd;

void main()
{
	gl_Position = position;
	theColor = color;
	theColorEnd = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
*/