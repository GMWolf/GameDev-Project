#version 330

in Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} IN;

layout (location = 0) out vec3 NormalOut;

//uniform sampler2D diffuseTex; 

void main() 
{
    //DiffuseOut = texture(diffuseTex, IN.TexCoord).xyz; 
    NormalOut = normalize(IN.Normal);
}