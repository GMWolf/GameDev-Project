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

#include "RotateSystem.h"
#include "CameraTransformSystem.h"
#include "Camera.h"
#include "MovementSystem.h"
#include "../Assets/AssetManager.h"
#include "VelocitySystem.h"

class Game : public ApplicationAdapter{

public:
	Game(int width, int height) : width(width), height(height)
	{
	}

	void render() override
	{
		SystemManager::update();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			ShouldClose = true;
		}

	}

	void init() override
	{
		Mesh* suzane = assetManager.getMesh("models/suzane.obj");
		Mesh* cube = new Mesh(Mesh::Cube(Vector3(1, 1, 1)));
		assetManager.manage("cube", cube);

		Texture* cobble1 = assetManager.getTexture("textures/texture.jpg");
		Texture* cobble2 = assetManager.getTexture("textures/Cobblestone5_albedo.tga");


		SystemManager::addSystem(new PlayerControlSystem(window));
		SystemManager::addSystem(new CameraTransformSystem());
		SystemManager::addSystem(new VelocitySystem());
		SystemManager::addSystem(new Renderer(width, height));
		SystemManager::addSystem(new RotateSystem());
		SystemManager::init();

		Entity eSuzane = Entity::create();
		eSuzane.add(Transform());
		eSuzane.get<Transform>().position = Vector3(1, 0, 0);
		eSuzane.add(MeshFilter(suzane, cobble1));

		Entity eSuzane2 = Entity::create();
		eSuzane2.add(Transform());
		eSuzane2.get<Transform>().position = Vector3(-1, 0, 0);
		eSuzane2.add(MeshFilter(suzane, cobble2));
		eSuzane2.add(Rotate(0.01));

		Entity eLightA = Entity::create();
		eLightA.add(Transform());
		eLightA.get<Transform>().position = Vector3(0 , 1.5, 1.5);
		eLightA.add(PointLight(Vector3(0.75, 1, 1)*1, 25));

		Entity eLightsa = Entity::create();
		eLightsa.add(Transform());
		eLightsa.get<Transform>().position = Vector3(-1, -1, 0.5);
		eLightsa.add(PointLight(Vector3(1, 0, 0), 3));

		Entity eLightsb = Entity::create();
		eLightsb.add(Transform());
		eLightsb.get<Transform>().position = Vector3(1, -1, 0.5);
		eLightsb.add(PointLight(Vector3(0, 0, 1), 3));

		Entity camera = Entity::create();
		camera.add(Transform());
		camera.add(Camera());
		camera.add(PlayerControl());

		Entity floor = Entity::create();
		floor.add(Transform());
		floor.add(MeshFilter(cube, cobble2));
		Transform& ft = floor.get<Transform>();
		ft.scale = Vector3(100, 0.1, 100);
		ft.position = Vector3(0, -1, 0);

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

	AssetManager assetManager;
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