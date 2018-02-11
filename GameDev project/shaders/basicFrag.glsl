#version 150 core

in Vertex {
	vec4 colour;
} IN;

out vec4 outColor;

void main()
{
    outColor = IN.colour;
}