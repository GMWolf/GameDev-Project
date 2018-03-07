#version 330
out vec4 out_color;

in Vertex {
    vec3 Colour;
} IN;
void main() {
	out_color = vec4(IN.Colour, 1.0);
}