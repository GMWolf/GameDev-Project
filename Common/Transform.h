#pragma once
#include <Component.h>
#include <Matrix4.h>
#include <Entity.h>


COMPONENT(Transform, 128) {

	Transform() : rotation(Matrix4::Identity()), position(0,0,0), scale(1,1,1), parent(-1){
	}

	Transform(Entity parent) : rotation(Matrix4::Identity()),  position(0, 0, 0), scale(1, 1, 1), parent(parent) {
	}


	Matrix4 rotation;
	Vector3 position;
	Vector3 scale;

	Entity parent;

	const Matrix4 getMatrix() const
	{
		Matrix4 mat = rotation;
		mat.items[0] *= scale.x;
		mat.items[5] *= scale.y;
		mat.items[10] *= scale.z;
		mat.position = position.xyz;
		return mat;
	}

	void load(const nlohmann::json& j)
	{
		position.x = j["position"]["x"].get<float>();
		position.y = j["position"]["y"].get<float>();
		position.z = j["position"]["z"].get<float>();
	}


};