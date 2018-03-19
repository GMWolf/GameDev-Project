#include "MovementSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "DeltaTime.h"
#include "Vector2.h"
#include <iostream>
#include "VelocitySystem.h"
#include "Lights.h"
#include "SystemManager.h"

PlayerControlSystem::PlayerControlSystem():
	playerControled(SubscriptionManager::getSubscription(Aspect::getAspect<PlayerControl, Transform>()))
{
}

PlayerControlSystem::~PlayerControlSystem()
{
}

void PlayerControlSystem::init()
{
	ui = SystemManager::getSystem<UISystem>();
	SpaceReleased = true;
}

void PlayerControlSystem::update()
{
	


	for(Entity e : playerControled)
	{
		Transform& t = e.get<Transform>();
		
		if (ui->getKey(UISystem::KEY_A)) {
			t.position += -(t.rotation.left * wagl::DeltaTime::delta * 2);
		}
		if (ui->getKey(UISystem::KEY_D)) {
			t.position += (t.rotation.left * wagl::DeltaTime::delta * 2);
		}
		if (ui->getKey(UISystem::KEY_LEFT_SHIFT)) {
			t.position += (t.rotation.up * wagl::DeltaTime::delta * 2);
		}
		if (ui->getKey(UISystem::KEY_LEFT_CTRL)) {
			t.position += -(t.rotation.up * wagl::DeltaTime::delta * 2);
		}
		if (ui->getKey(UISystem::KEY_W)) {
			t.position += -(t.rotation.forward * wagl::DeltaTime::delta * 2);
		}
		if (ui->getKey(UISystem::KEY_S)) {
			t.position += (t.rotation.forward * wagl::DeltaTime::delta * 2);
		}
		
		Vector2 diff = ui->getMouseDelta();
		t.rotation = Matrix4::Rotation(Vector3(0, 1, 0), -diff.x / 1000) * t.rotation;
		t.rotation = Matrix4::Rotation(t.rotation.left, -diff.y / 1000) * t.rotation;

		
		if (ui->getKey(UISystem::KEY_SPACE)) {
			if (SpaceReleased) {
				Entity e = Entity::create();
				e.add(Transform());
				e.get<Transform>().position = t.position;
				e.add(Velocity(t.rotation.forward * -2));
				e.add(PointLight(Vector3(0.25, 0.25, 1) , 5.f, 2.5));
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
