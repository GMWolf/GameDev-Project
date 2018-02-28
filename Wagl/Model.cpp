#include "Model.h"
#include <iostream>
Model::Model(VertexBuffer * mesh, ShaderProgram * shader)
	:mesh(mesh), shader(shader), attribsBounded(false)
{
	glGenVertexArrays(1, &vao);
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vao);
}

void Model::setMesh(VertexBuffer * newMesh)
{
	mesh = newMesh;
	attribsBounded = false;
}

void Model::setShader(ShaderProgram * newShader)
{
	shader = newShader;
	attribsBounded = false;
}

void Model::bindAttributes()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	int stride = mesh->format.getStride();

	for (int i = 0; i < mesh->format.attributes.size(); i++) {
		VertexAttribute vertAttrib = mesh->format.attributes[i];

		if (shader->hasAttribute(vertAttrib.alias)) {
			ShaderProgram::Attribute shdAttrib = shader->GetAttribute(vertAttrib.alias);

			//Only required that size be the same.
			//That is because glVertexAttribPointer and glGetActiveAttrib do not use same type.
			//Why, ogl? why must you be like that?

			if (vertAttrib.size() != shdAttrib.size * GetGLTypeSize(shdAttrib.type)) {
				std::cout << "Attribute " << vertAttrib.alias << " Size mismatch. Could not be bound" << std::endl;
				
			}
			else {

				GLint location = shdAttrib.location;
				int offset = mesh->format.getOffset(i);
				glVertexAttribPointer(location, vertAttrib.elementCount, vertAttrib.type, GL_FALSE, stride, (void*)offset);
				glEnableVertexAttribArray(location);
			}
		}
	}

	glBindVertexArray(0);

	attribsBounded = true;
}


void Model::draw()
{
	if (!attribsBounded) {
		bindAttributes();
	}
	shader->use();
	glBindVertexArray(vao);
	
	glDrawElements(GL_TRIANGLES, mesh->vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

