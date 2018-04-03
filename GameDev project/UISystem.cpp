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

	for(Input* input : inputs)
	{
		input->update(*this);
	}
}

void UISystem::end()
{
}

bool UISystem::getKey(Keys key) const
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

Input& UISystem::getInput(std::string name)
{
	return *inputsByname[name];
}

void UISystem::addInput(std::string name, Input* input)
{
	inputs.push_back(input);
	inputsByname.insert({ name, input });
}

AxisInput::AxisInput(Keys positive, Keys negative, float acc, float rest): positiveKey(positive), negativeKey(negative),
                                                                           acc(acc), restitution(rest)
{
}

float AxisInput::operator()()
{
	return value;
}

void AxisInput::update(UISystem& ui)
{
	int i = ui.getKey(positiveKey) - ui.getKey(negativeKey);
	if (i != 0)
	{
		value += acc * i;
	}
	else
	{
		value -= min(sgn(value) * restitution, value);
	}

	value = clamp(value, 0.f, 1.f);
}

ButtonInput::ButtonInput(Keys key): key(key)
{
}

float ButtonInput::operator()()
{
	return value;
}

void ButtonInput::update(UISystem& ui)
{
	value = ui.getKey(key);
}
