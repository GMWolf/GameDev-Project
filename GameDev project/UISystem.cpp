#include "UISystem.h"



UISystem::UISystem(GLFWwindow* window, wagl::ApplicationAdapter* app) : window(window), app(app)
{
}


UISystem::~UISystem()
{
}

void UISystem::init()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	mousePrevious.x = mx;
	mousePrevious.y = my;
}

void UISystem::update()
{
	if (glfwGetKey(window, KEY_ESCAPE))
	{
		app->ShouldClose = true;
	}

	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	mousePos.x = mx;
	mousePos.y = my;

	mouseDelta = mousePos - mousePrevious;
	mousePrevious = mousePos;
}

void UISystem::end()
{
}

bool UISystem::getKey(keys key) const
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

glm::vec2 UISystem::getMousePos() const
{
	return mousePos;
}

glm::vec2 UISystem::getMouseDelta() const
{
	return mouseDelta;
}
