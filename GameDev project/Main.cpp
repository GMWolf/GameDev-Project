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
#include <AssetManager.h>
#include "VelocitySystem.h"
#include "Mesh.h"
#include "Assets.h"
#include "LightFlicker.h"
#include "LightFlickerSystem.h"
#include "UISystem.h"
#include <PhysicsSystem.h>
#include <PhysicsColliderSystem.h>
#include "GUISystem.h"
#include "TextComponent.h"
#include "LightFade.h"
#include "LightFadeSystem.h"
#include "GunSystem.h"
#include "Gun.h"
#include "SystemProfiler.h"
#include "AudioSystem.h"
#include <Prefab.h>
#include <PrefabLoader.h>
#include "ECS.h"
#include "CommonComponentLoader.h"
#include "AssetsComponentLoader.h"
#include "FPSCameraSystem.h"
using namespace ECS;

class Game : public wagl::ApplicationAdapter {

public:
	Game(int width, int height) : width(width), height(height)
	{
	}

	void render() override
	{
		SystemManager::update();
	}

	void init() override
	{	
		assets.registerLoader<Mesh>(new MeshLoader);
		assets.registerLoader<ECS::Prefab>(new PrefabLoader);

		ECS::registerLoader<Transform>(new CommonComponentLoader<Transform>);
		ECS::registerLoader<Rotate>(new CommonComponentLoader<Rotate>);
		ECS::registerLoader<BoxCollider>(new CommonComponentLoader<BoxCollider>);
		ECS::registerLoader<CapsuleCollider>(new CommonComponentLoader<CapsuleCollider>);
		ECS::registerLoader<RigidBodyProperties>(new CommonComponentLoader<RigidBodyProperties>);
		ECS::registerLoader<MeshCollider>(new AssetsComponentLoader<MeshCollider>(assets));
		ECS::registerLoader<Gun>(new CommonComponentLoader<Gun>);
		ECS::registerLoader<PlayerControl>(new CommonComponentLoader<PlayerControl>);
		ECS::registerLoader<Camera>(new CommonComponentLoader<Camera>);
		
		UISystem* ui = new UISystem(window, this);
		ui->addInput("LookHor", new MouseDeltaInput(true));
		ui->addInput("LookVert", new MouseDeltaInput(false));
		ui->addInput("Shoot", new ButtonInput(KEY_SPACE));

		SystemManager::addSystem(ui);
		SystemManager::addSystem(new PhysicsColliderSystem(assets));
		SystemManager::addSystem(new PhysicsSystem);
		SystemManager::addSystem(new FPSCameraSystem);
		SystemManager::addSystem(new PlayerControlSystem);
		SystemManager::addSystem(new GunSystem(assets));
		SystemManager::addSystem(new CameraTransformSystem);
		SystemManager::addSystem(new VelocitySystem);
		SystemManager::addSystem(new Renderer(width, height, assets));
		SystemManager::addSystem(new SystemProfiler);
		SystemManager::addSystem(new GUISystem(width, height, window));
		SystemManager::addSystem(new AudioSystem(assets));
		SystemManager::addSystem(new RotateSystem);
		SystemManager::addSystem(new LightFlickerSystem);
		SystemManager::addSystem(new LightFadeSystem);
		
		SystemManager::init();

		ECS::loadScene("prefabs/level.json");

		/*AssetHandle<RenderMesh> suzane = assets.get<RenderMesh>("models/suzane.objm");
		AssetHandle<RenderMesh> pillars = assets.get<RenderMesh>("models/pillars.objm");

		AssetHandle<Material> cobblestone = assets.get<Material>("materials/Cobblestone5.mat");
		AssetHandle<Material> damaged = assets.get<Material>("materials/Damaged.mat");
		AssetHandle<Material> sand = assets.get<Material>("materials/SandPebbles.mat");
		AssetHandle<Material> marble = assets.get<Material>("materials/MarbleRed.mat");*/

		/*Entity text = Entity::create();
		text.add(Transform());
		text.get<Transform>().position = glm::vec3(2, 2, 0);
		text.add(TextComponent("hello, world! This is some great text!"));*/

		Entity sun = Entity::create();
		sun.add(DirectionalLight(glm::vec3(0, -1, 0), glm::vec3(0.25, 0.25, 1), 1.f));

		Entity eLightA = Entity::create();
		eLightA.add(Transform());
		eLightA.get<Transform>().position = glm::vec3(0 , 1.5, 1.5);
		eLightA.add(PointLight(glm::vec3(0.75, 1, 1), 1, 25));

		Entity eLightsa = Entity::create();
		eLightsa.add(Transform());
		eLightsa.get<Transform>().position = glm::vec3(-1, -1, 0.5);
		eLightsa.add(PointLight(glm::vec3(1, 0, 0), 2, 3));

		Entity eLightsb = Entity::create();
		eLightsb.add(Transform());
		eLightsb.get<Transform>().position = glm::vec3(1, -1, 0.5);
		eLightsb.add(PointLight(glm::vec3(0, 0, 1), 2, 3));


		Entity floor = Entity::create();
		floor.add(Transform());
		floor.add(MeshFilter(assets.get<RenderMesh>("models/smoothCube.objm"), assets.get<Material>("materials/SandPebbles.mat")));
		Transform& ft = floor.get<Transform>();
		ft.scale = glm::vec3(10, 10, 10);
		ft.position = glm::vec3(0, -11, 0);
		floor.add(BoxCollider(glm::vec3(10, 10, 10)));

		for (int i = -5; i < 5; i++) {

			Entity lightLeft = Entity::create();
			lightLeft.add(Transform());
			lightLeft.get<Transform>().position = glm::vec3(-1, 3, -5 * i);
			lightLeft.add(PointLight(glm::vec3(1, 0.8, 0.1), 4, 4));
			lightLeft.add(lightFlicker( 3, 5, (rand() / (float)RAND_MAX) * 5, 0.1));

			Entity lightRight = Entity::create();
			lightRight.add(Transform());
			lightRight.get<Transform>().position = glm::vec3(1, 3, -5 * i);
			lightRight.add(PointLight(glm::vec3(1, 0.8, 0.1), 4, 4));
			lightRight.add(lightFlicker(3, 5, (rand() / (float) RAND_MAX) * 5, 0.1));
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