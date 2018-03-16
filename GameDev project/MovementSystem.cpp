#include "MovementSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "DeltaTime.h"
#include "Vector2.h"
#include <iostream>
#include "VelocitySystem.h"
#include "Lights.h"

PlayerControlSystem::PlayerControlSystem(GLFWwindow* window):
	playerControled(SubscriptionManager::getSubscription(Aspect::getAspect<PlayerControl, Transform>())), 
	window(window)
{
}

PlayerControlSystem::~PlayerControlSystem()
{
}

void PlayerControlSystem::init()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	mousePrevious = Vector2(xpos, ypos);
	SpaceReleased = true;
}

void PlayerControlSystem::update()
{
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	const Vector2 cursorPos(xpos, ypos);

	const Vector2 diff = cursorPos - mousePrevious;
	mousePrevious = cursorPos;


	for(Entity e : playerControled)
	{
		Transform& t = e.get<Transform>();
		
		bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		if (left) {
			t.position += -(t.rotation.left * wagl::DeltaTime::delta * 2);
		}
		bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		if (right) {
			t.position += (t.rotation.left * wagl::DeltaTime::delta * 2);
		}
		bool up = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
		if (up) {
			t.position += (t.rotation.up * wagl::DeltaTime::delta * 2);
		}
		bool down = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
		if (down) {
			t.position += -(t.rotation.up * wagl::DeltaTime::delta * 2);
		}
		bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		if (forward) {
			t.position += -(t.rotation.forward * wagl::DeltaTime::delta * 2);
		}
		bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		if (backward) {
			t.position += (t.rotation.forward * wagl::DeltaTime::delta * 2);
		}
		
		t.rotation = Matrix4::Rotation(Vector3(0, 1, 0), -diff.x / 1000) * t.rotation;
		t.rotation = Matrix4::Rotation(t.rotation.left, -diff.y / 1000) * t.rotation;

		bool shoot = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (shoot) {
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
