#version 330


layout (location = 0) out vec3 LightOut;

uniform vec2 screenSize;
uniform mat4 view;

uniform sampler2D positionTex;
uniform sampler2D depthTex;
uniform sampler2D normalTex;

in Vertex {
	vec3 Position;
    vec3 Colour;
	float Radius;
} IN;

void main() 
{

	vec2 texCoord = gl_FragCoord.xy / screenSize;
	vec3 geoPosition = texture(positionTex, texCoord).xyz;
	vec3 normal = normalize(texture(normalTex, texCoord).xyz);
	
	
	vec3 lightDir = IN.Position - geoPosition;
	float lightDist = length(lightDir);
	lightDir /= lightDist;
	
	vec3 light = IN.Colour * (1 - lightDist) * dot(lightDir, normal);
	LightOut = light;
	//LightOut = vec3(1,1,1);
}