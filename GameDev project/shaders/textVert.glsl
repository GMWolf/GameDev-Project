#version 330 

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 UV;

uniform mat4 MVP;

out Vertex	{
	vec2 UV;
} OUT; 

void main()
{ 
   	gl_Position = MVP  * vec4(Position, 0, 1);
	OUT.UV = UV;
} 