#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram(Shader<GL_VERTEX_SHADER>* vertex, Shader<GL_FRAGMENT_SHADER>* fragment) : ShaderProgram(vertex, nullptr, fragment)
{
}

ShaderProgram::ShaderProgram(Shader<35633>* vertex, Shader<36313>* geometry, Shader<35632>* fragment)
{
	vertexShader = vertex->glShader;
	fragmentShader = fragment->glShader;
	geometryShader = geometry == nullptr ? 0 : geometry->glShader;

	link();
	registerAttributes();
	registerUniforms();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(program);
}

const ShaderProgram::Attribute& ShaderProgram::GetAttribute(const int attributeIndex) const
{
	return attributes.at(attributeIndex);
}

const ShaderProgram::Attribute & ShaderProgram::GetAttribute(const std::string name) const
{
	return GetAttribute(attributeIndexMap.at(name));
}

bool ShaderProgram::hasAttribute(const std::string attribute) const
{
	return attributeIndexMap.find(attribute) != attributeIndexMap.end();
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

	for (int i = 0; i < count; i++) {
		glGetActiveUniform(program, i, bufSize, &length, &size, &type, name);

		std::string strname(name);

		const GLint location = glGetUniformLocation(program, name);
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
		attributes.emplace_back(location, type, size);
		attributeIndexMap[std::string(name)] = i;
	}

}



void ShaderProgram::link()
{
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	if (geometryShader) glAttachShader(program, geometryShader);


	glBindFragDataLocation(program, 0, "outColor");
	glLinkProgram(program);

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	if (geometryShader) glDetachShader(program, geometryShader);
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

	default: return false;
	}
}

ShaderProgram::Uniform::Uniform(GLuint program, GLint location, GLenum type, GLsizei size): program(program),
                                                                                            location(location),
                                                                                            type(type), size(size)
{
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

void ShaderProgram::Uniform::operator=(const Matrix4 & rhs) const
{
	if (type != GL_FLOAT_MAT4) {
		std::cout << "Cannot assign Matrix to uniform" << std::endl;
		return;
	}
	glProgramUniformMatrix4fv(program, location, 1, false, rhs.items);
}


void ShaderProgram::Uniform::operator=(const GLfloat rhs) const
{
	if (type != GL_FLOAT) {
		return;
	}
	glProgramUniform1f(program, location, rhs);
}

