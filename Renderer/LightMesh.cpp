#include "stdafx.h"
#include "LightMesh.h"
#include "VBBuilder.h"


LightMesh::LightMesh() : vb(format, GL_STATIC_DRAW),
                         va(vb), vertexCount(0), dirty(true)
{
	updateBuffers();
}


LightMesh::~LightMesh()
{
}

void LightMesh::draw()
{
	updateBuffers();
	va.bind();
	glDrawElements(GL_POINTS, elements.size(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_POINTS, 0, vertexCount);
	wagl::VertexArray::unbind();
}

void LightMesh::addLight(const Vector3& position, const Vector3& colour, const float radius)
{
	positions.push_back(position);
	colours.push_back(colour);
	radii.push_back(radius);
	elements.push_back(vertexCount);
	vertexCount++;
	dirty = true;
}

void LightMesh::clear()
{
	positions.clear();
	colours.clear();
	radii.clear();
	elements.clear();
	vertexCount = 0;
	dirty = true;
}

void LightMesh::updateBuffers()
{
	if (!dirty) return;

	wagl::VBBuilder builder(format);
	builder.set(0, positions);
	builder.set(1, colours);
	builder.set(2, radii);
	builder.setElems(elements);
	builder.update(vb);
	
	dirty = false;
}


const wagl::VertexFormat LightMesh::format = {
	{GL_FLOAT, 3, "position"},
	{GL_FLOAT, 3, "colour"},
	{GL_FLOAT, 1, "radius"}
};
