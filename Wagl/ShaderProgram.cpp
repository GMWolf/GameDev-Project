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

	int samplerId = 0;
	for (int i = 0; i < count; i++) {
		glGetActiveUniform(program, i, bufSize, &length, &size, &type, name);

		std::string strname(name);

		location = glGetUniformLocation(program, name);
		uniforms[strname] = Uniform(program, location, type, size);
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

bool ShaderProgram::isSamplerType(GLenum type)
{
	switch (type) {
	case GL_SAMPLER_1D:
	case GL_SAMPLER_2D:
	case GL_SAMPLER_3D:
	case GL_SAMPLER_CUBE:
	case GL_SAMPLER_1D_SHADOW:
	case GL_SAMPLER_2D_SHADOW:
	case GL_SAMPLER_CUBE_SHADOW:
		return true;
	}

	return false;
}

void ShaderProgram::Uniform::operator=(GLint rhs) const
{
	if (type != GL_INT && !isSamplerType(type)) {
		std::cout << "Cannot assign GLint to uniform" << std::endl;
		return;
	}
	glProgramUniform1i(program, location, rhs);
}

void ShaderProgram::Uniform::operator=(GLuint rhs) const
{
	if (type != GL_UNSIGNED_INT && !isSamplerType(type)) {
		std::cout << "Cannot assign uint to uniform" << std::endl;
		return;
	}
	glProgramUniform1ui(program, location, rhs);
}



void ShaderProgram::Uniform::operator=(const Vector3& rhs) const
{
	if (type != GL_FLOAT_VEC3) {
		std::cout << "Cannot assign Vector3 to uniform" << std::endl;
		return;
	}
	glProgramUniform3f(program, location, rhs.x, rhs.y, rhs.z);
}

void ShaderProgram::Uniform::operator=(const Vector2& rhs) const
{
	if (type != GL_FLOAT_VEC2) {
		std::cout << "Cannot assign Vector2 to uniform" << std::endl;
		return;
	}
	glProgramUniform2f(program, location, rhs.x, rhs.y);
}


void ShaderProgram::Uniform::operator=(const GLfloat rhs) const
{
	if (type != GL_FLOAT) {
		return;
	}
	glProgramUniform1f(program, location, rhs);
}

