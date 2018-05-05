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
		Input* upDown = ui->getInput(pc.upDown);
		Input* lookHorizontal = ui->getInput(pc.lookHorizontal);
		Input* lookVertical = ui->getInput(pc.lookVertical);

		Transform& t = e.get<Transform>();
		
		t.position += glm::vec3(t.rotation[0] * (float)wagl::DeltaTime::delta) * (*horizontal)() * pc.speed;
		
		t.position += glm::vec3(t.rotation[2] * (float)wagl::DeltaTime::delta) * (*vertical)() * pc.speed;

		t.position += glm::vec3(t.rotation[1] * (float)wagl::DeltaTime::delta) * (*upDown)() * pc.speed;
		
		t.rotation = glm::rotate(glm::mat4(1), -(*lookHorizontal)() / 1000, glm::vec3(0, 1, 0)) * t.rotation;
		
		t.rotation = glm::rotate(glm::mat4(1), (*lookVertical)() / 1000, glm::vec3(t.rotation[0])) * t.rotation;

	}
}

void PlayerControlSystem::end()
{
}
