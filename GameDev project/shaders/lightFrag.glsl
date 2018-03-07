#version 330


layout (location = 0) out vec3 LightOut;

uniform vec2 screenSize;
uniform mat4 invView;
uniform mat4 invProjection;


uniform sampler2D depthTex;
uniform sampler2D normalTex;

in Vertex {
	vec3 Position;
    vec3 Colour;
	float Radius;
} IN;

vec3 WorldPosFromDepth(float depth, vec2 texCoord) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(texCoord * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    // Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    vec4 worldSpacePosition = invView * viewSpacePosition;

    return worldSpacePosition.xyz;
}

void main() 
{

	vec2 texCoord = gl_FragCoord.xy / screenSize;
	//vec3 geoPosition = texture(positionTex, texCoord).xyz;
	float depth = texture(depthTex, texCoord).r;
	vec3 geoPosition = WorldPosFromDepth(depth, texCoord);
	vec3 normal = normalize(texture(normalTex, texCoord).xyz);
	
	
	vec3 lightDir = IN.Position - geoPosition;
	float lightDist = length(lightDir);
	lightDir /= lightDist;
	
	float intensity = (IN.Radius - lightDist) / IN.Radius;
	
	if (intensity < 0.01) {
		discard;
	}
	
	vec3 light = IN.Colour * intensity * dot(lightDir, normal);
	LightOut = light;
	//LightOut = vec3(geoPosition.xyz);
}