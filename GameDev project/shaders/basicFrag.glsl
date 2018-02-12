#version 150 core

in Vertex {
	vec4 colour;
	vec2 Texcoord;
} IN;

out vec4 outColor;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	vec4 t0 = texture(tex, IN.Texcoord);
	vec4 t1 = texture(tex2, IN.Texcoord);
    outColor = mix(t0, t1, 0.5f) * IN.colour;
}