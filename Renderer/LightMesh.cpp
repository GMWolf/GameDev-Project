#include "stdafx.h"
#include "LightMesh.h"
#include "VBBuilder.h"
#include "Icosphere.h"


LightMesh::LightMesh() : instancePos_vb({ { GL_FLOAT, 3, "position" } }, GL_STREAM_DRAW),
						 instanceCol_vb({ {GL_FLOAT, 3, "colour"} }, GL_STREAM_DRAW),
						 instanceR_vb({ { GL_FLOAT, 1, "radius" } }, GL_STREAM_DRAW),
						 sphere_vb(LightMesh::sphere_format, GL_STATIC_DRAW)
{
	generateSphereMesh();

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);

	sphere_vb.bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	instancePos_vb.bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	instanceCol_vb.bind();
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	instanceR_vb.bind();
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(3);

	sphere_vb.bind();


	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);

	updateBuffers();
}


LightMesh::~LightMesh()
{
}

void LightMesh::draw()
{
	updateBuffers();
	glBindVertexArray(va);
	//glDrawElements(GL_POINTS, elements.size(), GL_UNSIGNED_INT, (void*)0);
	glDrawElementsInstanced(GL_TRIANGLES, sphereElementCount, GL_UNSIGNED_INT, (void*)0, lightCount);
	glBindVertexArray(0);
}

void LightMesh::addLight(const glm::vec3& position, const glm::vec3& colour, const float radius)
{
	positions.push_back(position);
	colours.push_back(colour);
	radii.push_back(radius);
	elements.push_back(lightCount);
	lightCount++;
	dirty = true;
}

void LightMesh::clear()
{
	positions.clear();
	colours.clear();
	radii.clear();
	elements.clear();
	lightCount = 0;
	dirty = true;
}


void LightMesh::generateSphereMesh()
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> elements;

	Icosphere::generate(1, elements, vertices);

	sphere_vb.setVertexData(vertices.size(), vertices.data());
	sphere_vb.setElementsData(elements.size(), elements.data());

	sphereElementCount = elements.size();
}

void LightMesh::updateBuffers()
{
	if (!dirty) return;

	instancePos_vb.setVertexData(positions.size(), positions.data());
	instanceCol_vb.setVertexData(colours.size(), colours.data());
	instanceR_vb.setVertexData(radii.size(), radii.data());
	
	dirty = false;
}

const wagl::VertexFormat LightMesh::sphere_format = {
	{ GL_FLOAT, 3, "position" }
};