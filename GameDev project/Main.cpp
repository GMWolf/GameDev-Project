#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glfwApplication.h>
#include <ApplicationAdapter.h>
#include <string>
#include <Renderer.h>
#include <SystemManager.h>
#include <Transform.h>
#include <MeshFilter.h>
#include <MeshLoader.h>
#include <Mesh.h>
#include <Entity.h>
#include <Lights.h>

class Game : public ApplicationAdapter{

public:
	Game(int width, int height) : width(width), height(height), suzane(nullptr)
	{
	}

	void render() override
	{
		SystemManager::update();
	}

	void init() override
	{

		suzane = MeshLoader::LoadObj("models/suzane.obj");

		SystemManager::addSystem(new Renderer(window, width, height));
		SystemManager::init();

		Entity eSuzane = Entity::create();
		eSuzane.add(Transform());
		eSuzane.add(MeshFilter(suzane));
		eSuzane.get<MeshFilter>().mesh = suzane;

		Entity eSuzane2 = Entity::create();
		eSuzane2.add(Transform());
		eSuzane2.get<Transform>().position = Vector3(-2, -1, -1).xyz;
		eSuzane2.add(MeshFilter(suzane));
		eSuzane2.get<MeshFilter>().mesh = suzane;

		Entity eLightA = Entity::create();
		eLightA.add(Transform());
		eLightA.get<Transform>().position = Vector3(1, 1, 1).xyz;
		eLightA.add(PointLight(Vector3(0.25, 0.25, 1), 2));

		Entity eLightB = Entity::create();
		eLightB.add(Transform());
		eLightB.get<Transform>().position = Vector3(-1, -0.25, 0).xyz;
		eLightB.add(PointLight(Vector3(1, 0.25, 0.25), 2));

	}

	void end() override
	{
		SystemManager::end();
	}


	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override
	{

	}
private:
	int width;
	int height;

	Mesh* suzane;

};

int main(void) {

	glfwConfiguration config;
	config.title = "yo!";
	config.width = 1280;
	config.height = 720;

	//Game game;
	Game game(config.width, config.height);
	glfwApplication app(game, config);
	app.init();

	return 0;
}