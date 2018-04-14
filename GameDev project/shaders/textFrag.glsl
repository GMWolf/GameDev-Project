#version 330

layout (location = 0) out vec4 OUT;

uniform sampler2D tex;

in Vertex {
	vec2 UV;
} IN;


void main() 
{
	OUT = texture(tex, IN.UV);
}