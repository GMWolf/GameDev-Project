#version 150 core

in vec3 position;
in vec2 texCoord;
in vec4 colour;


out Vertex	{
	vec4 colour;
	vec2 Texcoord;
} OUT;

void main()
{
    gl_Position = vec4(position, 1.0);
	OUT.colour = colour;
	OUT.Texcoord = texCoord;
}