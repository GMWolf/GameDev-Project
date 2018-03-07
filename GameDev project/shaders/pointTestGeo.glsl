#version 420 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

in Vertex{
	vec3 Colour;
	float Radius;
} IN[];

out Vertex {
	vec3 Colour;
} OUT;

void main() {
	for (int i = 0; i < gl_in.length(); i++) {
		OUT.Colour = IN[i].Colour;
		//OUT.Position = IN[i].Position;
		//OUT.Radius = IN[i].Radius;
		
		float r = IN[i].Radius;
		//top right 
		gl_Position = gl_in[i].gl_Position;
		//gl_Position.z -= r;4
		gl_Position.x += r;
		gl_Position.y += r;
		gl_Position = projection * gl_Position;
		EmitVertex();

		//top left
		gl_Position = gl_in[i].gl_Position;
		//gl_Position.z -= r;
		gl_Position.x -= r;
		gl_Position.y += r;
		gl_Position = projection * gl_Position;
		EmitVertex();

		//bottom right
		gl_Position = gl_in[i].gl_Position;
		//gl_Position.z -= r;
		gl_Position.x += r;
		gl_Position.y -= r;
		gl_Position = projection * gl_Position;
		EmitVertex();

		//bottom left
		gl_Position = gl_in[i].gl_Position;
		//gl_Position.z -= r;
		gl_Position.x -= r;
		gl_Position.y -= r;
		gl_Position = projection * gl_Position;
		EmitVertex();
		
		EndPrimitive();
	}
}