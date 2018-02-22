#version 330 

in vec3 position;
in vec3 normal;
in vec2 texCoord;

uniform mat4 MVP;
//uniform mat4 World;

out Vertex	{
	vec3 Normal;
	vec2 TexCoord;
} OUT; 

void main()
{ 
    gl_Position = MVP * vec4(position, 1.0);
    OUT.TexCoord = texCoord;
    OUT.Normal = (/*World **/ vec4(normal, 0.0)).xyz;
}