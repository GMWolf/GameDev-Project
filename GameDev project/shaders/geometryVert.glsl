#version 330 

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 MVP;
uniform mat4 model;

out Vertex	{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec3 Bitangent;
	vec2 TexCoord;
} OUT; 

void main()
{ 
    gl_Position = MVP * vec4(position, 1.0);
	OUT.Position = (model * vec4(position, 1.0)).xyz;
    OUT.TexCoord = texCoord;
    OUT.Normal = (model * vec4(normalize(normal), 0.0)).xyz;
	OUT.Tangent = (model * vec4(normalize(tangent), 0.0)).xyz;
	OUT.Bitangent = (model * vec4(normalize(bitangent), 0.0)).xyz;
}