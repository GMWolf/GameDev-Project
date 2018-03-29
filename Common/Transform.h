#pragma once
#include <Component.h>
#include <Matrix4.h>
#include <Entity.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


COMPONENT(Transform, 128) {

	Transform() : rotation(glm::mat4(1)), position(0,0,0), scale(1,1,1), parent(-1){
	}

	Transform(Entity parent) : rotation(glm::mat4(1)),  position(0, 0, 0), scale(1, 1, 1), parent(parent) {
	}


	glm::mat4 rotation;
	glm::vec3 position;
	glm::vec3 scale;

	Entity parent;

	const glm::mat4 getMatrix() const
	{
		glm::mat4 mat = glm::scale(glm::translate(glm::mat4(1), position) * rotation, scale);
		return mat;
	}

	void load(const nlohmann::json& j)
	{
		position.x = j["position"]["x"].get<float>();
		position.y = j["position"]["y"].get<float>();
		position.z = j["position"]["z"].get<float>();
	}


};