#version 330 

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 lPosition;
layout (location = 2) in vec3 Colour;
layout (location = 3) in float Radius;

/*uniform mat4 projection;
uniform mat4 view;*/
uniform mat4 MVP;

out Vertex	{
	vec3 Position;
	vec3 Colour;
	float Radius;
} OUT; 

void main()
{ 
   	gl_Position = MVP  * vec4((Position * Radius) + lPosition, 1.0);
	OUT.Position = lPosition;
	OUT.Colour = Colour;
	OUT.Radius = Radius;
} 