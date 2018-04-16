#pragma once
#include "System.h"
#include "ApplicationAdapter.h"
#include <glm/detail/type_vec2.hpp>
#include <vector>
#include <set>
#include <unordered_map>
#include "json.hpp"
#include <wincon.h>


class UISystem;

enum Keys
{
	KEY_A = GLFW_KEY_A,
	KEY_B = GLFW_KEY_B,
	KEY_C = GLFW_KEY_C,
	KEY_D = GLFW_KEY_D,
	KEY_E = GLFW_KEY_E,
	KEY_F = GLFW_KEY_F,
	KEY_G = GLFW_KEY_G,
	KEY_H = GLFW_KEY_H,
	KEY_I = GLFW_KEY_I,
	KEY_J = GLFW_KEY_J,
	KEY_K = GLFW_KEY_K,
	KEY_L = GLFW_KEY_L,
	KEY_M = GLFW_KEY_L,
	KEY_N = GLFW_KEY_N,
	KEY_O = GLFW_KEY_O,
	KEY_P = GLFW_KEY_P,
	KEY_Q = GLFW_KEY_Q,
	KEY_R = GLFW_KEY_R,
	KEY_S = GLFW_KEY_S,
	KEY_T = GLFW_KEY_T,
	KEY_U = GLFW_KEY_U,
	KEY_V = GLFW_KEY_V,
	KEY_W = GLFW_KEY_W,
	KEY_X = GLFW_KEY_X,
	KEY_Y = GLFW_KEY_Y,
	KEY_Z = GLFW_KEY_Z,
	KEY_ESCAPE = GLFW_KEY_ESCAPE,
	KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
	KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
	KEY_LEFT_CTRL = GLFW_KEY_LEFT_CONTROL,
	KEY_RIGHT_CTRL = GLFW_KEY_RIGHT_CONTROL,
	KEY_UP = GLFW_KEY_UP,
	KEY_DOWN = GLFW_KEY_DOWN,
	KEY_LEFT = GLFW_KEY_LEFT,
	KEY_RIGHT = GLFW_KEY_RIGHT,
	KEY_SPACE = GLFW_KEY_SPACE,
	KEY_ALT = GLFW_KEY_LEFT_ALT,
	KEY_GRAVE = GLFW_KEY_GRAVE_ACCENT
};
//const std::unordered_map<std::string, Keys> keysByName;

class Input
{
public:
	virtual ~Input() = default;
	virtual float operator()() = 0;

	virtual void update(UISystem& ui, float dt) = 0;
};

class UISystem : public ECS::System
{
public:

	UISystem(GLFWwindow* window, wagl::ApplicationAdapter* app);
	~UISystem();
	void init() override;
	void update() override;
	void end() override;

	bool getKey(Keys key) const;

	glm::vec2 getMousePos() const;
	glm::vec2 getMouseDelta() const;

	Input* getInput(std::string name);
	void addInput(std::string name, Input* input);
	void addInput(nlohmann::json& js);
	bool hasInput(std::string name);

private:

	void loadInputs(std::string file);

	GLFWwindow * window;
	wagl::ApplicationAdapter* app;
	glm::vec2 mousePrevious;
	glm::vec2 mousePos;
	glm::vec2 mouseDelta;

	std::vector<Input*> inputs;
	std::unordered_map<std::string, Input*> inputsByname;
};

class DummyInput : public Input
{
public:
	float operator()() override;
	void update(UISystem& ui, float dt) override;
};

class AxisInput : public Input
{
public:

	AxisInput(Keys positive, Keys negative, float acc, float rest);
	AxisInput(nlohmann::json js);

	float operator()() override;;

	void update(UISystem& ui, float dt) override;

private:
	float value = 0;
	Keys positiveKey;
	Keys negativeKey;
	float acceleration;
	float restitution;
};

class ButtonInput : public Input
{
public:

	ButtonInput(Keys key);

	float operator()() override;

	void update(UISystem& ui, float dt) override;

private:
	Keys key;
	int value = 0;
};

class MouseDeltaInput : public Input
{
public:
	MouseDeltaInput(bool hor);

	float operator()() override;

	void update(UISystem& ui, float dt) override;
private:
	bool horizontal; //true for horizontal mouse delta, false for vertical
	float value = 0;
};

class MultiplexedInput : public Input
{
public:
	MultiplexedInput(std::initializer_list<Input*> ins);;

	MultiplexedInput(UISystem& ui, nlohmann::json& js);

	float operator()() override;

	void update(UISystem& ui, float dt) override;

private:
	std::vector<Input*> inputs;
	float value = 0;
};