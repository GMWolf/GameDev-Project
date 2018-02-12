#version 150 core

in Vertex {
	vec4 colour;
	vec2 Texcoord;
} IN;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, IN.Texcoord) * IN.colour;
}