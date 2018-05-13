#pragma once
#include <Component.h>
#include <Entity.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "ECS.h"

COMPONENT(Transform, 128) {

	Transform() : rotation(glm::mat4(1)), position(0,0,0), scale(1,1,1), parent(-1){
	}

	Transform(ECS::Entity parent) : rotation(glm::mat4(1)),  position(0, 0, 0), scale(1, 1, 1), parent(parent) {
	}

	glm::mat4 rotation;
	glm::vec3 position;
	glm::vec3 scale;

	ECS::Entity parent;

	const glm::mat4 getMatrix() const
	{
		glm::mat4 mat = glm::scale(glm::translate(glm::mat4(1), position) * rotation, scale);
		if (parent.getId() != -1 && parent.has<Transform>())
		{
			return parent.get<Transform>().getMatrix()*mat;
		}
		
		return mat;
	}

	const glm::vec3 getPosition() const
	{
		if (parent.getId() != -1 && parent.has<Transform>())
		{
			return parent.get<Transform>().getMatrix() * glm::vec4(position, 1.0);
		}
		return position;
	}

	const glm::mat4 getRotation() const
	{
		if (parent.getId() != -1 && parent.has<Transform>())
		{
			return parent.get<Transform>().getRotation() * rotation;
		}
		return rotation;
	}

	void setParent(ECS::Entity entity, bool relativePosition = true)
	{
		parent = entity;
		if (parent.has<Transform>())
		{
			Transform& t = parent.get<Transform>();
			/*glm::mat4 newmat = getMatrix() * glm::inverse(t.getMatrix()) ;
			glm::tquat<float> rot;
			glm::vec3 skew;
			glm::vec4 persp;
			glm::decompose(newmat, scale, rot, position, skew, persp);
			rotation = glm::mat4(rot);*/
			glm::mat4 invT = glm::inverse(t.getMatrix());
			
			position = invT * glm::vec4(position, 1);
			rotation = glm::inverse(t.getRotation()) * rotation;
			scale /= t.scale;
		}
	}

	void load(const nlohmann::json& j)
	{
		position.x = j["position"][0].get<float>();
		position.y = j["position"][1].get<float>();
		position.z = j["position"][2].get<float>();

		if (j.find("parent") != j.end())
		{
			parent = ECS::getLoadGroup().getEntity(j["parent"]);
			std::cout << "got a parent! " << parent.getId() << std::endl;
		}

		if (j.find("scale") != j.end())
		{
			scale.x = j["scale"][0];
			scale.y = j["scale"][1];
			scale.z = j["scale"][2];
		}
	}


};
