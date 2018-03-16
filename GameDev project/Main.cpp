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
#include "Mesh.h"
#include "Assets.h"
#include "LightWave.h"
#include "LightWaveSystem.h"

class Game : public wagl::ApplicationAdapter{

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
		AssetHandle<Mesh> suzane = assets.meshs.get("models/suzane.objm");
		Mesh cubeMesh(Mesh::Cube(Vector3(1, 1, 1)));
		AssetHandle<Mesh> cube = assets.meshs.manage(cubeMesh, "cube");
		AssetHandle<Mesh> pillars = assets.meshs.get("models/pillars.objm");

		AssetHandle<Material> cobblestone = assets.materials.get("materials/Cobblestone5.mat");
		AssetHandle<Material> damaged = assets.materials.get("materials/Damaged.mat");
		AssetHandle<Material> sand = assets.materials.get("materials/SandPebbles.mat");
		AssetHandle<Material> marble = assets.materials.get("materials/MarbleRed.mat");
		
		SystemManager::addSystem(new PlayerControlSystem(window));
		SystemManager::addSystem(new CameraTransformSystem());
		SystemManager::addSystem(new VelocitySystem());
		SystemManager::addSystem(new Renderer(width, height));
		SystemManager::addSystem(new RotateSystem());
		SystemManager::addSystem(new LightWaveSystem());
		SystemManager::init();


		Entity eSuzane = Entity::create();
		eSuzane.add(Transform());
		eSuzane.get<Transform>().position = Vector3(1, 0, 0);
		eSuzane.add(MeshFilter(suzane, cobblestone));

		Entity eSuzane2 = Entity::create();
		eSuzane2.add(Transform());
		eSuzane2.get<Transform>().position = Vector3(-1, 0, 0);
		eSuzane2.add(MeshFilter(suzane, damaged));
		eSuzane2.add(Rotate(0.01));

		Entity eLightA = Entity::create();
		eLightA.add(Transform());
		eLightA.get<Transform>().position = Vector3(0 , 1.5, 1.5);
		eLightA.add(PointLight(Vector3(0.75, 1, 1), 1, 25));

		Entity eLightsa = Entity::create();
		eLightsa.add(Transform());
		eLightsa.get<Transform>().position = Vector3(-1, -1, 0.5);
		eLightsa.add(PointLight(Vector3(1, 0, 0), 2, 3));

		Entity eLightsb = Entity::create();
		eLightsb.add(Transform());
		eLightsb.get<Transform>().position = Vector3(1, -1, 0.5);
		eLightsb.add(PointLight(Vector3(0, 0, 1), 2, 3));

		Entity camera = Entity::create();
		camera.add(Transform());
		camera.add(Camera());
		camera.add(PlayerControl());

		Entity floor = Entity::create();
		floor.add(Transform());
		floor.add(MeshFilter(cube, sand));
		Transform& ft = floor.get<Transform>();
		ft.scale = Vector3(20, 20, 20);
		ft.position = Vector3(0, -11, 0);

		for (int i = -5; i < 5; i++) {
			Entity e = Entity::create();
			e.add(Transform());
			e.get<Transform>().position = Vector3(0,  -1, -5 * i);
			e.add(MeshFilter(pillars, marble));

			Entity lightLeft = Entity::create();
			lightLeft.add(Transform());
			lightLeft.get<Transform>().position = Vector3(-1, 3, -5 * i);
			lightLeft.add(PointLight(Vector3(1, 0.8, 0.1), 4, 4));
			lightLeft.add(lightWave( 3, 5, (rand() / (float)RAND_MAX), 0.1));

			Entity lightRight = Entity::create();
			lightRight.add(Transform());
			lightRight.get<Transform>().position = Vector3(1, 3, -5 * i);
			lightRight.add(PointLight(Vector3(1, 0.8, 0.1), 4, 4));
			lightLeft.add(lightWave(3, 5, (rand() / (float) RAND_MAX), 0.1));
		}


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

	Assets assets;
};

int main(void) {
	wagl::glfwConfiguration config;
	config.title = "yo!";
	config.width = 1280;
	config.height = 720;

	//Game game;
	Game game(config.width, config.height);
	wagl::glfwApplication app(game, config);
	app.init();

	return 0;
}