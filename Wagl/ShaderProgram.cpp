#include "ShaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.inl>

wagl::ShaderProgram::Uniform wagl::ShaderProgram::Uniform::invalid = Uniform(-1, -1, -1, -1);

wagl::ShaderProgram::ShaderProgram(Shader<GL_VERTEX_SHADER>* vertex, Shader<GL_FRAGMENT_SHADER>* fragment) : ShaderProgram(vertex, nullptr, fragment)
{
}

wagl::ShaderProgram::ShaderProgram(Shader<35633>* vertex, Shader<36313>* geometry, Shader<35632>* fragment)
{
	vertexShader = vertex->glShader;
	fragmentShader = fragment->glShader;
	geometryShader = geometry == nullptr ? 0 : geometry->glShader;

	link();
	registerAttributes();
	registerUniforms();
}

wagl::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(program);
}

const wagl::ShaderProgram::Attribute& wagl::ShaderProgram::GetAttribute(const int attributeIndex) const
{
	return attributes.at(attributeIndex);
}

const wagl::ShaderProgram::Attribute & wagl::ShaderProgram::GetAttribute(const std::string name) const
{
	return GetAttribute(attributeIndexMap.at(name));
}

bool wagl::ShaderProgram::hasAttribute(const std::string attribute) const
{
	return attributeIndexMap.find(attribute) != attributeIndexMap.end();
}

const wagl::ShaderProgram::Uniform& wagl::ShaderProgram::Getuniform(const std::string uniformName) const
{
	if (uniforms.find(uniformName) == uniforms.end())
	{
		std::cout << "Could not find uniform " << uniformName << std::endl;
		return Uniform::invalid;
	}
	return uniforms.at(uniformName);
}


void wagl::ShaderProgram::use()
{
	glUseProgram(program);
}

void wagl::ShaderProgram::registerUniforms()
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

void wagl::ShaderProgram::registerAttributes()
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



void wagl::ShaderProgram::link()
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

bool wagl::ShaderProgram::isSamplerType(GLenum type)
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

wagl::ShaderProgram::Uniform::Uniform(GLuint program, GLint location, GLenum type, GLsizei size): program(program),
                                                                                            location(location),
                                                                                            type(type), size(size)
{
}

void wagl::ShaderProgram::Uniform::operator=(bool rhs) const
{
	if (location == -1) return;
	if(type != GL_BOOL)
	{
		std::cout << "Cannot assign GLboolean to uniform" << std::endl;
		return;
	}
	glProgramUniform1i(program, location, rhs);
}

void wagl::ShaderProgram::Uniform::operator=(GLint rhs) const
{
	if (location == -1) return;
	if (type != GL_INT && !isSamplerType(type)) {
		std::cout << "Cannot assign GLint to uniform" << std::endl;
		return;
	}
	glProgramUniform1i(program, location, rhs);
}

void wagl::ShaderProgram::Uniform::operator=(GLuint rhs) const
{
	if (location == -1) return;
	if (type != GL_UNSIGNED_INT && !isSamplerType(type)) {
		std::cout << "Cannot assign uint to uniform" << std::endl;
		return;
	}
	glProgramUniform1ui(program, location, rhs);
}



void wagl::ShaderProgram::Uniform::operator=(const glm::vec3& rhs) const
{
	if (location == -1) return;
	if (type != GL_FLOAT_VEC3) {
		std::cout << "Cannot assign vec3 to uniform" << std::endl;
		return;
	}
	glProgramUniform3f(program, location, rhs.x, rhs.y, rhs.z);
}

void wagl::ShaderProgram::Uniform::operator=(const glm::vec2& rhs) const
{
	if (location == -1) return;
	if (type != GL_FLOAT_VEC2) {
		std::cout << "Cannot assign vec2 to uniform" << std::endl;
		return;
	}
	glProgramUniform2f(program, location, rhs.x, rhs.y);
}

void wagl::ShaderProgram::Uniform::operator=(const glm::mat4 & rhs) const
{
	if (location == -1) return;
	if (type != GL_FLOAT_MAT4) {
		std::cout << "Cannot assign mat4 to uniform" << std::endl;
		return;
	}
	glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, glm::value_ptr(rhs));
}


void wagl::ShaderProgram::Uniform::operator=(const GLfloat rhs) const
{
	if (location == -1) return;
	if (type != GL_FLOAT) {
		return;
	}
	glProgramUniform1f(program, location, rhs);
}

