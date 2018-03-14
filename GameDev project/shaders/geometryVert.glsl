#version 330 

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;



out Vertex	{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec3 Bitangent;
	vec2 TexCoord;
} OUT; 

uniform mat4 MVP;
uniform mat4 model;

void main()
{ 
    gl_Position = MVP * vec4(position, 1.0);
	OUT.Position = (model * vec4(position, 1.0)).xyz;
    OUT.TexCoord = texCoord;
    OUT.Normal = normalize((model * vec4(normalize(normal), 0.0)).xyz);
	OUT.Tangent = normalize((model * vec4(normalize(tangent), 0.0)).xyz);
	OUT.Bitangent = normalize((model * vec4(normalize(bitangent), 0.0)).xyz);
}