#version 330

layout (location = 0) out vec3 FragOut;

in Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} IN;

uniform vec2 screenSize;

uniform sampler2D diffuseTex;
uniform sampler2D lightTex;

void main() 
{

	vec2 texCoord = gl_FragCoord.xy / screenSize;
	
	vec3 light = texture(lightTex, texCoord).xyz;
	vec3 diffuse = texture(diffuseTex, IN.TexCoord).xyz;
	
	FragOut = diffuse * light;
	//FragOut = vec3(0.5, 0.5, 0.5);
}