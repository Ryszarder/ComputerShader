#version 450

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Velocity;
layout (location = 2) in vec4 Colour;
//layout (location = 3) in float Alpha;

out vec4 vertColour;
//out float vertAlpha;

uniform mat4 mvpMatrix;

void main()
{
	//vertAlpha = Alpha;
	vertColour = Colour;
	gl_Position = mvpMatrix * Position;
}