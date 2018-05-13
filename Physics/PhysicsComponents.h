#pragma once
#include <Component.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <glm/glm.hpp>
#include <AssetHandle.h>
#include "Mesh.h"
#include <Assets.h>

COMPONENT(BoxCollider, 1)
{
	BoxCollider() : halfSides(1, 1, 1)
	{
	}

	BoxCollider(glm::vec3 hs) : halfSides(hs)
	{
	}

	glm::vec3 halfSides;

	void load(const nlohmann::json& j)
	{
		halfSides.x = j["sides"][0].get<float>();
		halfSides.y = j["sides"][1].get<float>();
		halfSides.z = j["sides"][2].get<float>();
	}
};

COMPONENT(SphereCollider, 1)
{
	SphereCollider() : radius(1)
	{
	}

	SphereCollider(float r) : radius(r)
	{
	}

	float radius;
};

COMPONENT(CapsuleCollider, 1)
{
	CapsuleCollider() : radius(1) , height(2)
	{
	}

	CapsuleCollider(float r, float height) : radius(r), height(height)
	{
	}


	void load(const nlohmann::json& j)
	{
		height = j["height"].get<float>();
		radius = j["radius"].get<float>();
	}

	float height;
	float radius;
};

COMPONENT(MeshCollider, 1)
{
	
	MeshCollider() : concave(false)
	{
	}
	MeshCollider(AssetHandle<Mesh> mesh) : concave(false), mesh(mesh)
	{
		
	}

	void load(const nlohmann::json& json, Assets& assets) {
		mesh = assets.get<Mesh>(json["mesh"].get<std::string>());
	}

	AssetHandle<Mesh> mesh;
	bool concave;
};

COMPONENT(Collider, 16)
{

	Collider() : collisionShape(nullptr)
	{
	}

	Collider(btCollisionShape* s) : collisionShape(s)
	{
	}

	btCollisionShape* collisionShape;

};

COMPONENT(RigidBodyProperties, 16)
{
	RigidBodyProperties() : mass(1), angularFactor(1,1,1) {}

	RigidBodyProperties(float mass) : mass(mass), angularFactor(1,1,1) {}

	float mass;
	glm::vec3 angularFactor;
	

	void load(const nlohmann::json& j)
	{
		mass = j["mass"].get<float>();
		if (j.find("angular factor") != j.end())
		{
			angularFactor[0] = j["angular factor"][0].get<float>();
			angularFactor[1] = j["angular factor"][1].get<float>();
			angularFactor[2] = j["angular factor"][2].get<float>();
		}
	}
};

COMPONENT(Kinematic, 1)
{
	Kinematic(): kinematic(true)
	{
	} ;
	bool kinematic;
};

COMPONENT(RigidBody, 16)
{

	RigidBody() : rigidBody(nullptr)
	{
	}

	RigidBody(btRigidBody* r) : rigidBody(r)
	{
	}

	btRigidBody* rigidBody;

	glm::vec3 getCenterOfMassPosition()
	{
		auto& com = rigidBody->getCenterOfMassPosition();
		return glm::vec3(com.x(), com.y(), com.z());
	}
};
