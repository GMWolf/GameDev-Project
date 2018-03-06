#version 330


layout (location = 0) out vec3 LightOut;

uniform vec3 lightPos;
uniform float intensity;

uniform vec2 screenSize;

uniform sampler2D positionTex;
uniform sampler2D normalTex; 

void main() 
{

	vec2 texCoord = gl_FragCoord.xy / screenSize;
	vec3 position = texture(positionTex, texCoord).xyz;
	vec3 normal = normalize(texture(normalTex, texCoord).xyz);
	
	
	vec3 lightDir = lightPos - position;
	float lightDist = length(lightDir);
	lightDir /= lightDist;
	
	vec3 light = vec3(intensity * dot(lightDir, normal) * (1/(lightDist*lightDist)));
	LightOut = light;
}