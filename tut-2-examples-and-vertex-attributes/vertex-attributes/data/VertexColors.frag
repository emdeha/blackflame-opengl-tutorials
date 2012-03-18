// The end fragment shader
#version 330

smooth in vec4 theColor;

out vec4 outputColor;

void main()
{	
	outputColor = theColor;
}


/*
// The fragment task shader. Uncomment it and comment the other.
#version 330

smooth in vec4 theColor;
smooth in vec4 theColorEnd;

out vec4 outputColor;

void main()
{	
	float lerpValue = gl_FragCoord.y / 500.0f;
	outputColor = mix(theColor, theColorEnd, lerpValue);
}
*/