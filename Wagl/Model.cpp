#include "Model.h"

Model::Model(Mesh * mesh, ShaderProgram * shader)
	:mesh(mesh), shader(shader), attribsBounded(false)
{
	glGenVertexArrays(1, &vao);
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vao);
}

void Model::setMesh(Mesh * newMesh)
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
		VertexAttribute attribute = mesh->format.attributes[i];
		GLint attribPos = shader->GetAttributeLocation(attribute.alias);
		int offset = mesh->format.getOffset(i);
		glVertexAttribPointer(attribPos, attribute.elementCount, attribute.type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(attribPos);
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
	//
	glDrawElements(GL_TRIANGLES, mesh->vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
