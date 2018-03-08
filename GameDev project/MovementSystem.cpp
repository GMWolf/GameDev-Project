#include "MovementSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "DeltaTime.h"
#include "Vector2.h"
#include <iostream>

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
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	mousePrevious = Vector2(xpos, ypos);
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
			t.position += -(t.rotation.left * DeltaTime::delta * 2);
		}
		bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		if (right) {
			t.position += (t.rotation.left * DeltaTime::delta * 2);
		}
		bool up = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (up) {
			t.position += (t.rotation.up * DeltaTime::delta * 2);
		}
		bool down = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
		if (down) {
			t.position += -(t.rotation.up * DeltaTime::delta * 2);
		}
		bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		if (forward) {
			t.position += -(t.rotation.forward * DeltaTime::delta * 2);
		}
		bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		if (backward) {
			t.position += (t.rotation.forward * DeltaTime::delta * 2);
		}
		
		t.rotation = Matrix4::Rotation(Vector3(0, 1, 0), -diff.x / 1000) * t.rotation;
		t.rotation = Matrix4::Rotation(t.rotation.left, -diff.y / 1000) * t.rotation;

	}
}

void PlayerControlSystem::end()
{
}
