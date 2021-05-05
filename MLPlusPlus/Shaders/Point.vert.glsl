#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 colour;

out vec4 vColour;

uniform mat4 uProj = mat4(1.0f);

void main()
{
	gl_Position = uProj * vec4(pos, 0.0f, 1.0f);
	vColour = colour;
}