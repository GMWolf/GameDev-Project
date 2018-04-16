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

PlayerControlSystem::PlayerControlSystem():
	assets(assets), SpaceReleased(false),
	playerControled(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<PlayerControl, Transform>())), ui(nullptr),
	physics(nullptr)
{
}

PlayerControlSystem::~PlayerControlSystem()
{
}

void PlayerControlSystem::init()
{
	ui = ECS::SystemManager::getSystem<UISystem>();
	horizontal = ui->getInput("Horizontal");
	vertical = ui->getInput("Vertical");
	upDown = ui->getInput("UpDown");
	lookHorizontal = ui->getInput("LookHor");
	lookVertical = ui->getInput("LookVert");
	shoot = ui->getInput("Shoot");

	physics = ECS::SystemManager::getSystem<PhysicsSystem>();
	SpaceReleased = true;
}

void PlayerControlSystem::update()
{
	


	for(ECS::Entity e : playerControled)
	{
		Transform& t = e.get<Transform>();
		
		t.position += glm::vec3(t.rotation[0] * (float)wagl::DeltaTime::delta * 2.f) * (*horizontal)();
		
		t.position += glm::vec3(t.rotation[2] * (float)wagl::DeltaTime::delta * 2.f) * (*vertical)();

		t.position += glm::vec3(t.rotation[1] * (float)wagl::DeltaTime::delta * 2.f) * (*upDown)();
		
		t.rotation = glm::rotate(glm::mat4(1), -(*lookHorizontal)() / 1000, glm::vec3(0, 1, 0)) * t.rotation;
		
		t.rotation = glm::rotate(glm::mat4(1), (*lookVertical)() / 1000, glm::vec3(t.rotation[0])) * t.rotation;

		/*if ((*shoot)()) {
			if (SpaceReleased) {
				/*Entity e = Entity::create();
				e.add(Transform());
				e.get<Transform>().position = t.position;
				e.add(Velocity(t.rotation.forward * -5));
				e.add(PointLight(Vector3(0.25, 0.25, 1) , 5.f, 2.5));*/
				PhysicsSystem::Hit hit;
				/*physics->RayCastClosest(t.position, t.position + glm::vec3(t.rotation[2]) * 100.f, hit);
				if(hit.hasHit)
				{
					//glm::vec3 offset =glm::vec3( glm::inverse(hit.entity.get<Transform>().getMatrix()) * glm::vec4(hit.worldPos, 1.0));
					glm::vec3 offset = hit.worldPos - hit.entity.get<RigidBody>().getCenterOfMassPosition();
					PhysicsSystem::Impulse::Emit(hit.entity, +(glm::vec3(t.rotation[2]) * 2.f), offset);

					glm::vec3 pos = hit.worldPos + hit.normal * 0.05f;

					Entity light = Entity::create();
					light.add(Transform());
					light.get<Transform>().position = pos;
					glm::vec3 T = glm::cross(hit.normal, glm::vec3(0.0, 0.0, 1.0));
					light.get<Transform>().rotation = glm::lookAt(glm::vec3(0,0,0), T, hit.normal);
					light.get<Transform>().scale = glm::vec3(0.1);
					light.get<Transform>().setParent(hit.entity);
					light.add(MeshFilter(assets.renderMeshes.get("models/suzane.objm"), assets.materials.get("materials/MarbleRed.mat")));
					light.add(PointLight(glm::vec3(0.25, 0.25, 1), 10.f, 2.f));
					light.add(LightFade(10));
				}
			}
			SpaceReleased = false;
		} else
		{
			SpaceReleased = true;
		}*/

	}
}

void PlayerControlSystem::end()
{
}
