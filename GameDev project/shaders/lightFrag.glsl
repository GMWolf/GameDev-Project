#version 330


layout (location = 0) out vec4 LightOut;

uniform vec2 screenSize;
uniform mat4 invView;
uniform mat4 invProjection;


uniform sampler2D depthTex;
uniform sampler2D NRTex;

in Vertex {
	vec3 Position;
    vec3 Colour;
	float Radius;
} IN;

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
	
	
	vec3 lightDir = IN.Position - worldVertPos.xyz;
	float lightDist = length(lightDir);
	
	lightDir /= lightDist;
	
	float apparentLight = (IN.Radius - lightDist) / IN.Radius;
	
	float diffuseIntensity = (apparentLight * max(dot(lightDir, normal), 0.0f))  ;
	
	if (diffuseIntensity <= 0.01f) {
		discard;
	}
	
	vec3 diffuse = IN.Colour * diffuseIntensity;
	
	//phong
	vec3 reflectDir = reflect(-lightDir, normal);
	float specAngle = max(dot(reflectDir, normalize(-viewVertPos.xyz)), 0.0f);
	float specular = pow(specAngle, 4.f) * apparentLight / (8.f * roughness);
	
	
	
	LightOut = vec4(clamp(diffuse, 0.f, 1.0f), specular);
	//LightOut = vec3(geoPosition.xyz);
}