#version 330

layout (location = 0) out vec3 FragOut;

in Vertex {
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec3 Bitangent;
	vec2 TexCoord;
} IN;

uniform vec2 screenSize;
uniform sampler2D diffuseTex;
uniform sampler2D lightTex;
uniform sampler2D alphaTex;
uniform bool useAlpha; //Dynamicallyuniform, hopefully

void main() 
{

	if (useAlpha) {
		float alpha = texture(alphaTex, IN.TexCoord).r;
		if (alpha < 0.1f) {
			discard;
		}
	}

	vec2 texCoord = gl_FragCoord.xy / screenSize;
	
	vec4 light = texture(lightTex, texCoord);
	vec3 diffuse = texture(diffuseTex, IN.TexCoord).xyz;
	
	FragOut = (diffuse * light.rgb) + (light.a * vec3(1.0f, 1.0f, 1.0f));
	//FragOut = vec3(0.5, 0.5, 0.5);
}