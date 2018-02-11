#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(Shader<GL_VERTEX_SHADER>& vertex, Shader<GL_FRAGMENT_SHADER>& fragment)
{
	vertexShader = vertex.glShader;
	fragmentShader = fragment.glShader;
	link();
}


ShaderProgram::~ShaderProgram()
{
}

int ShaderProgram::GetAttributeLocation(std::string attribute)
{
	return glGetAttribLocation(program, attribute.c_str());
}

void ShaderProgram::use()
{
	glUseProgram(program);
}

void ShaderProgram::link()
{
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);
}
