#pragma once
#include <VertexArray.h>
#include <VertexFormat.h>
#include <VertexBuffer.h>
#include <vector>
#include <Vector3.h>
#include <glm/detail/type_vec3.hpp>

class LightMesh
{
public:
	LightMesh();
	~LightMesh();

	void draw();

	void addLight(const glm::vec3& position, const glm::vec3& colour, float radius);
	void clear();

private:
	std::vector<glm::vec3> positions{};
	std::vector<glm::vec3> colours{};
	std::vector<float> radii{};
	std::vector<int> elements{};

	

	wagl::VertexBuffer instancePos_vb;
	wagl::VertexBuffer instanceCol_vb;
	wagl::VertexBuffer instanceR_vb;
	wagl::VertexBuffer sphere_vb;
	unsigned int sphereElementCount;

	GLuint va;

	int lightCount;



	void generateSphereMesh();

	void updateBuffers();

	bool dirty;

	static const wagl::VertexFormat sphere_format;
};

