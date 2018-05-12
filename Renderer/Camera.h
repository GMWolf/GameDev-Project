#pragma once
#include <Vector3.h>
#include <Matrix4.h>
#include <Component.h>
#include <glm/mat4x4.hpp>

COMPONENT(Camera, 1, 8)
{
	glm::mat4 view;
	glm::mat4 invView;

	void load(const nlohmann::json& j)
	{
	}
};