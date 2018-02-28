#include "Model.h"
#include <iostream>
Model::Model(VertexBuffer * vb, ShaderProgram * shader)
	:vb(vb), shader(shader), attribsBounded(false)
{
	glGenVertexArrays(1, &vao);
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vao);
}

void Model::setMesh(VertexBuffer * newVb)
{
	vb = newVb;
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
	/*glBindBuffer(GL_ARRAY_BUFFER, vb->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vb->ebo);*/
	vb->bind();
	int stride = vb->format.getStride();

	for (int i = 0; i < vb->format.attributes.size(); i++) {
		VertexAttribute vertAttrib = vb->format.attributes[i];
		
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
				int offset = vb->format.getOffset(i);
				std::cout << location << std::endl;
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
	glDrawElements(GL_TRIANGLES, vb->vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

