#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram(Shader<GL_VERTEX_SHADER>& vertex, Shader<GL_FRAGMENT_SHADER>& fragment)
{
	vertexShader = vertex.glShader;
	fragmentShader = fragment.glShader;
	link();
	registerAttributes();
	registerUniforms();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(program);
}

const ShaderProgram::Attribute& ShaderProgram::GetAttribute(const std::string attributeName) const
{
	return attributes.at(attributeName);
}

bool ShaderProgram::hasAttribute(const std::string attribute) const
{
	return attributes.find(attribute) != attributes.end();
}

const ShaderProgram::Uniform& ShaderProgram::Getuniform(const std::string uniformName) const
{
	return uniforms.at(uniformName);
}


void ShaderProgram::use()
{
	glUseProgram(program);
}

void ShaderProgram::registerUniforms()
{
	const GLsizei bufSize = 32;

	int count;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

	GLchar name[bufSize];
	GLsizei length;
	GLsizei size;
	GLenum type;
	GLint location;

	for (int i = 0; i < count; i++) {
		
		glGetActiveUniform(program, i, bufSize, &length, &size, &type, name);

		location = glGetUniformLocation(program, name);
		uniforms[std::string(name)] = Uniform(location, type, size);
	}
}

void ShaderProgram::registerAttributes()
{
	const GLsizei bufSize = 32;

	int count;
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);

	GLchar name[bufSize];
	GLsizei length;
	GLsizei size;
	GLenum type;
	GLint location;

	for (int i = 0; i < count; i++) {
		glGetActiveAttrib(program, i, bufSize, &length, &size, &type, name);
		location = glGetAttribLocation(program, name);
		attributes[std::string(name)] = Attribute(location, type, size);
	}

}



void ShaderProgram::link()
{
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
}

