#include "MovementSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "DeltaTime.h"
#include <iostream>
#include "VelocitySystem.h"
#include "Lights.h"
#include "SystemManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MeshFilter.h"
#include "LightFade.h"
#include "ECS.h"
#include "CommonComponentLoader.h"

PlayerControlSystem::PlayerControlSystem():
	playerControled(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<PlayerControl, Transform>())), ui(nullptr),
	physics(nullptr)
{
}

PlayerControlSystem::~PlayerControlSystem()
{
}

void PlayerControlSystem::init()
{
	ECS::registerLoader<PlayerControl>(new CommonComponentLoader<PlayerControl>());
	ui = ECS::SystemManager::getSystem<UISystem>();

	physics = ECS::SystemManager::getSystem<PhysicsSystem>();
	SpaceReleased = true;
}

void PlayerControlSystem::update()
{

	for(ECS::Entity e : playerControled)
	{
		PlayerControl& pc = e.get<PlayerControl>();
		
		Input* horizontal = ui->getInput(pc.horizontal);
		Input* vertical = ui->getInput(pc.vertical);

		Transform& t = e.get<Transform>();
		btRigidBody* rb = e.get<RigidBody>().rigidBody;

		glm::vec3 force;
		force += glm::vec3(t.rotation[2]) * (*vertical)() * 10.f;
		force += glm::vec3(t.rotation[0]) * (*horizontal)() * 10.f;
		rb->applyCentralForce(btVector3(force.x, force.y, force.z));
		rb->setFriction(1.f);

		/*Transform& t = e.get<Transform>();
		
		t.position += glm::vec3(t.rotation[0] * (float)wagl::DeltaTime::delta) * (*horizontal)() * pc.speed;
		
		t.position += glm::vec3(t.rotation[2] * (float)wagl::DeltaTime::delta) * (*vertical)() * pc.speed;

		float u = wagl::DeltaTime::delta * (*upDown)() * pc.speed;
		
		t.rotation = glm::rotate(glm::mat4(1), -(*lookHorizontal)() / 1000, glm::vec3(0, 1, 0)) * t.rotation;
		
		t.rotation = glm::rotate(glm::mat4(1), (*lookVertical)() / 1000, glm::vec3(t.rotation[0])) * t.rotation;*/


		/*PhysicsSystem::Hit hit;
		glm::vec3 feet(t.position.x, t.position.y, l.y());
		physics->RayCastClosest(feet, feet - glm::vec3(0, 0.1, 0), hit);

		if (!hit.hasHit)
		{
			t.position -= glm::vec3(0, u, 0);
		}*/

	}
}

void PlayerControlSystem::end()
{
}
