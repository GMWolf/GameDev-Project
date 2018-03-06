#version 330 

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 MVP;
//uniform mat4 World;

out Vertex	{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} OUT; 

void main()
{ 
    gl_Position = MVP * vec4(position, 1.0);
	OUT.Position = position;
    OUT.TexCoord = texCoord;
    OUT.Normal = (/*World **/ vec4(normal, 0.0)).xyz;
}