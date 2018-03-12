#version 330

in Vertex {
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec3 Bitangent;
	vec2 TexCoord;
} IN;

layout (location = 0) out vec3 NormalOut;

uniform sampler2D normalTex; 

void main() 
{

	mat3 TBN = mat3(IN.Tangent, IN.Bitangent, IN.Normal);
	
    //DiffuseOut = texture(diffuseTex, IN.TexCoord).xyz; 
    NormalOut = TBN * normalize(texture(normalTex, IN.TexCoord).rgb * 2.0 - 1.0);
	//NormalOut = normalize(IN.Tangent);
}