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

PlayerControlSystem::PlayerControlSystem(Assets& assets):
	assets(assets), SpaceReleased(false),
	playerControled(SubscriptionManager::getSubscription(Aspect::getAspect<PlayerControl, Transform>())), ui(nullptr),
	physics(nullptr)
{
}

PlayerControlSystem::~PlayerControlSystem()
{
}

void PlayerControlSystem::init()
{
	ui = SystemManager::getSystem<UISystem>();
	physics = SystemManager::getSystem<PhysicsSystem>();
	SpaceReleased = true;
}

void PlayerControlSystem::update()
{
	


	for(Entity e : playerControled)
	{
		Transform& t = e.get<Transform>();
		
		if (ui->getKey(UISystem::KEY_A)) {
			t.position += glm::vec3(t.rotation[0] * (float)wagl::DeltaTime::delta * 2.f);
		}
		if (ui->getKey(UISystem::KEY_D)) {
			t.position += -glm::vec3(t.rotation[0] * (float)wagl::DeltaTime::delta * 2.f);
		}
		if (ui->getKey(UISystem::KEY_LEFT_SHIFT)) {
			t.position += glm::vec3(t.rotation[1] * (float)wagl::DeltaTime::delta * 2.f);
		}
		if (ui->getKey(UISystem::KEY_LEFT_CTRL)) {
			t.position += -glm::vec3(t.rotation[1] * (float)wagl::DeltaTime::delta * 2.f);
		}
		if (ui->getKey(UISystem::KEY_W)) {
			t.position += glm::vec3(t.rotation[2] * (float)wagl::DeltaTime::delta * 2.f);
		}
		if (ui->getKey(UISystem::KEY_S)) {
			t.position += -glm::vec3(t.rotation[2] * (float)wagl::DeltaTime::delta * 2.f);
		}
		
		glm::vec2 diff = ui->getMouseDelta();
		t.rotation = glm::rotate(glm::mat4(1), -diff.x / 1000, glm::vec3(0, 1, 0)) * t.rotation;
		t.rotation = glm::rotate(glm::mat4(1), diff.y / 1000, glm::vec3(t.rotation[0])) * t.rotation;

		
		if (ui->getKey(UISystem::KEY_SPACE)) {
			if (SpaceReleased) {
				/*Entity e = Entity::create();
				e.add(Transform());
				e.get<Transform>().position = t.position;
				e.add(Velocity(t.rotation.forward * -5));
				e.add(PointLight(Vector3(0.25, 0.25, 1) , 5.f, 2.5));*/
				PhysicsSystem::Hit hit;
				physics->RayCastClosest(t.position, t.position + glm::vec3(t.rotation[2]) * 100.f, hit);
				if(hit.hasHit)
				{
					std::cout << "HIT!" << std::endl;
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
					light.add(MeshFilter(assets.meshs.get("models/suzane.objm"), assets.materials.get("materials/MarbleRed.mat")));
					light.add(PointLight(glm::vec3(0.25, 0.25, 1), 5.f, 2.f));
				}
			}
			SpaceReleased = false;
		} else
		{
			SpaceReleased = true;
		}

	}
}

void PlayerControlSystem::end()
{
}
