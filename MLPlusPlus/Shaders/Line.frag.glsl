#version 460 core

layout (location = 0) out vec4 outColour;

in vec4 vColour;

void main()
{
	outColour = vColour;
}
