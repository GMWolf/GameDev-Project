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
uniform bool flipNormals;

void main() 
{

	mat3 TBN = mat3(IN.Tangent, IN.Bitangent, IN.Normal);
	
	
	vec3 normal = normalize(texture(normalTex, IN.TexCoord).rgb * 2.0 - 1.0);
	if (flipNormals) { //Dynamically uniform
		normal *= vec3(1, -1, 1);
	}
	
    NROut.xyz = TBN * normal;
	NROut.a = texture(roughnessTex, IN.TexCoord).r;
}