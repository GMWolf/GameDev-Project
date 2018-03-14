#version 330

in Vertex {
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec3 Bitangent;
	vec2 TexCoord;
} IN;

layout (location = 0) out vec4 NROut;

uniform sampler2D normalTex; 
uniform sampler2D roughnessTex;

void main() 
{

	mat3 TBN = mat3(IN.Tangent, IN.Bitangent, IN.Normal);
	
    //DiffuseOut = texture(diffuseTex, IN.TexCoord).xyz; 
    NROut.xyz = TBN * normalize(texture(normalTex, IN.TexCoord).rgb * 2.0 - 1.0);
	NROut.a = texture(roughnessTex, IN.TexCoord).r;
	//NormalOut = normalize(IN.Tangent);
}