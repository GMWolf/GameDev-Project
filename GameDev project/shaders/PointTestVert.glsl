#version 330

layout (location = 0) in vec3 Position; 
layout (location = 1) in vec3 Colour;
layout (location = 2) in float Radius;

uniform mat4 view;

out Vertex {
	vec3 Colour;
	float Radius;
} OUT;

void main() {
	gl_Position = view * vec4(Position, 1.0);
	OUT.Colour = Colour;
	OUT.Radius = Radius;
}