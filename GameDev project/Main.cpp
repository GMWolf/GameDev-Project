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

		/*
		//Print Component IDs
		std::cout << "Transform " << Transform::componentId << std::endl;
		std::cout << "Velocity " << Velocity::componentId << std::endl;
		std::cout << "LightWave " << lightFlicker::componentId << std::endl;
		std::cout << "PointLight " << PointLight::componentId << std::endl;
		std::cout << "MeshFilter " << MeshFilter::componentId << std::endl;
		std::cout << "Camera " << Camera::componentId << std::endl;
		std::cout << "PlayerControl " << PlayerControl::componentId << std::endl;
		std::cout << "Rotate  " << Rotate::componentId << std::endl;
		*/

		AssetHandle<RenderMesh> suzane = assets.renderMeshes.get("models/suzane.objm");
		Mesh cubeMesh(Mesh::Cube(glm::vec3(1, 1, 1)));
		assets.meshes.manage(cubeMesh, "cube");
		AssetHandle<RenderMesh> cube = assets.renderMeshes.get("cube");
		AssetHandle<RenderMesh> pillars = assets.renderMeshes.get("models/pillars.objm");

		AssetHandle<Material> cobblestone = assets.materials.get("materials/Cobblestone5.mat");
		AssetHandle<Material> damaged = assets.materials.get("materials/Damaged.mat");
		AssetHandle<Material> sand = assets.materials.get("materials/SandPebbles.mat");
		AssetHandle<Material> marble = assets.materials.get("materials/MarbleRed.mat");
		
		UISystem* ui = new UISystem(window, this);
		/*ui->addInput("horizontal", new AxisInput(KEY_A, KEY_D, 4, 6));
		ui->addInput("vertical", new AxisInput(KEY_W, KEY_S, 4, 6));
		ui->addInput("UpDown", new AxisInput(KEY_LEFT_SHIFT, KEY_LEFT_CTRL, 3, 3));*/
		ui->addInput("LookHor", new MouseDeltaInput(true));
		ui->addInput("LookVert", new MouseDeltaInput(false));
		ui->addInput("Shoot", new ButtonInput(KEY_SPACE));

		SystemManager::addSystem(ui);
		SystemManager::addSystem(new PhysicsColliderSystem);
		SystemManager::addSystem(new PhysicsSystem);
		SystemManager::addSystem(new PlayerControlSystem);
		SystemManager::addSystem(new GunSystem(assets));
		SystemManager::addSystem(new CameraTransformSystem);
		SystemManager::addSystem(new VelocitySystem);
		SystemManager::addSystem(new Renderer(width, height));
		SystemManager::addSystem(new SystemProfiler);
		SystemManager::addSystem(new GUISystem(width, height, window));
		SystemManager::addSystem(new AudioSystem);
		SystemManager::addSystem(new RotateSystem);
		SystemManager::addSystem(new LightFlickerSystem);
		SystemManager::addSystem(new LightFadeSystem);
		
		SystemManager::init();

		/*Entity text = Entity::create();
		text.add(Transform());
		text.get<Transform>().position = glm::vec3(2, 2, 0);
		text.add(TextComponent("hello, world! This is some great text!"));*/


		Entity sun = Entity::create();
		sun.add(DirectionalLight(glm::vec3(0, 1, 0), glm::vec3(0.25, 0.25, 1), 0.2));

		Entity eSuzane = Entity::create();
		eSuzane.add(Transform());
		eSuzane.get<Transform>().position = glm::vec3(1, 0, 0);
		eSuzane.add(MeshFilter(suzane, cobblestone));

		Entity eSuzane2 = Entity::create();
		eSuzane2.add(Transform());
		eSuzane2.get<Transform>().position = glm::vec3(-1, 0, 0);
		eSuzane2.add(MeshFilter(suzane, damaged));
		eSuzane2.add(Rotate(0.01));

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

		Entity camera = Entity::create();
		camera.add(Transform());
		camera.add(Camera());
		camera.add(PlayerControl());
		camera.add(Gun(5));
		//camera.add(MeshFilter(suzane, sand));

		Entity floor = Entity::create();
		floor.add(Transform());
		floor.add(MeshFilter(assets.renderMeshes.get("models/smoothCube.objm"), sand));
		Transform& ft = floor.get<Transform>();
		ft.scale = glm::vec3(10, 10, 10);
		ft.position = glm::vec3(0, -11, 0);
		floor.add(BoxCollider(glm::vec3(10, 10, 10)));

		for (int i = -5; i < 5; i++) {
			Entity e = Entity::create();
			e.add(Transform());
			e.get<Transform>().position = glm::vec3(0,  -1, -5 * i);
			e.add(MeshFilter(pillars, marble));

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

		Entity blockA = Entity::create();
		blockA.add(Transform());
		blockA.get<Transform>().position = glm::vec3(0, 5, -3);
		blockA.add(MeshFilter(assets.renderMeshes.get("models/smoothCube.objm"), marble));
		blockA.add(BoxCollider(glm::vec3(1, 1, 1)));
		blockA.add(RigidBodyProperties(1));

		Entity blockB = Entity::create();
		blockB.add(Transform());
		blockB.get<Transform>().position = glm::vec3(1.2, 7, -3);
		blockB.add(MeshFilter(assets.renderMeshes.get("models/smoothCube.objm"), marble));
		blockB.add(BoxCollider(glm::vec3(1, 1, 1)));
		blockB.add(RigidBodyProperties(1));

		Entity blockC = Entity::create();
		blockC.add(Transform());
		blockC.get<Transform>().position = glm::vec3(0.1, 9, -3);
		blockC.add(MeshFilter(assets.renderMeshes.get("models/smoothCube.objm"), marble));
		blockC.add(BoxCollider(glm::vec3(1, 1, 1)));
		blockC.add(RigidBodyProperties(1));
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