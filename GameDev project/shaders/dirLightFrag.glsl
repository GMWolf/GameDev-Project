#version 330

layout (location = 0) out vec4 LightOut;

uniform vec2 screenSize;
uniform mat4 invView;
uniform mat4 invProjection;

uniform vec3 colour;
uniform vec3 lightDir;

uniform sampler2D depthTex;
uniform sampler2D NRTex;


vec4 ViewPosFromDepth(float depth, vec2 texCoord) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(texCoord * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    // Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    //vec4 worldSpacePosition = invView * viewSpacePosition;

    return viewSpacePosition;
}

void main() 
{
	vec2 texCoord = gl_FragCoord.xy / screenSize;
	float depth = texture(depthTex, texCoord).r;
	vec4 viewVertPos = ViewPosFromDepth(depth, texCoord);
	vec4 worldVertPos = invView * viewVertPos;
	vec4 NR = texture(NRTex, texCoord);
	vec3 normal = normalize(NR.xyz);
	float roughness = NR.a;
	
	

	float diffuseIntensity = (max(dot(lightDir, normal), 0.0f))  ;
	
	if (diffuseIntensity <= 0.01f) {
		discard;
	}
	
	vec3 diffuse = colour * diffuseIntensity;
	
	//phong
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAngle = max(dot(reflectDir, normalize(-viewVertPos.xyz)), 0.0f);
	float specular = pow(specAngle, 4.f) / (8.f * roughness);
	
	
	
	LightOut = vec4(clamp(diffuse, 0.f, 1.0f), specular);
}