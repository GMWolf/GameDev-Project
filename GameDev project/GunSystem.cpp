#include "GunSystem.h"
#include "SubscriptionManager.h"
#include "Gun.h"
#include "Entity.h"
#include "DeltaTime.h"
#include "SystemManager.h"
#include "PhysicsSystem.h"
#include "MeshFilter.h"
#include "LightFade.h"
#include "Lights.h"
#include "AudioEvent.h"
#include <glm/gtc/random.hpp>
#include <Prefab.h>
#include "AssetsComponentLoader.h"
#include "VelocitySystem.h"


GunSystem::GunSystem(Assets& assets) :
	entities(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, Gun>())),
	ui(nullptr), physics(nullptr), shoot(nullptr),
	assets(assets)
{
}


GunSystem::~GunSystem()
{
}

void GunSystem::init()
{
	ECS::registerLoader<Gun>(new AssetsComponentLoader<Gun>(assets));

	ui = ECS::SystemManager::getSystem<UISystem>();
	physics = ECS::SystemManager::getSystem<PhysicsSystem>();

	shoot = ui->getInput("Shoot");

	
	/*ECS::Entity e = ECS::Entity::create(assets.get<ECS::Prefab>("prefabs/tortilla.json"));
	ECS::Entity::destroy(e);*/
}

void GunSystem::update()
{
	for(ECS::Entity e : entities)
	{
		Transform& t = e.get<Transform>();
		Gun& gun = e.get<Gun>();
		if (gun.coolDown > 0)
		{
			gun.coolDown -= wagl::DeltaTime::delta;
		}

		if ((*shoot)() && gun.coolDown <= 0)
		{
			gun.coolDown += 1 / gun.fireRate;

			AudioEvent::Emit(assets.get<Sound>("audio/Laser_Shoot2.wav"));

			ECS::Entity projectile = ECS::Entity::create(assets.resolve(gun.projectile));
			projectile.add(Velocity(t.getRotation()[2] * gun.velocity));
			projectile.get<Transform>().position = t.getPosition();



			//Do ray trace and entity spawn
			/*PhysicsSystem::Hit hit;
			physics->RayCastClosest(t.getPosition(), t.getPosition() + glm::vec3(t.getRotation()[2]) * 100.f, hit);
			if (hit.hasHit)
			{
				//glm::vec3 offset =glm::vec3( glm::inverse(hit.entity.get<Transform>().getMatrix()) * glm::vec4(hit.worldPos, 1.0));
				glm::vec3 pos = hit.worldPos + hit.normal * 0.01f;

				ECS::Entity tortilla = ECS::Entity::create(assets.resolve(assets.get<ECS::Prefab>("prefabs/tortilla.json")));
				tortilla.add(Transform());
				tortilla.get<Transform>().position = pos;
				glm::vec3 rand = glm::sphericalRand(1.0f);
				while (glm::dot(rand, hit.normal) > 0.9)
				{
					rand = glm::sphericalRand(1.0f);
				}
				glm::vec3 T = glm::normalize(glm::cross(hit.normal, rand));
				glm::vec3 N = glm::normalize(glm::cross(T, hit.normal));
				
				Transform& transform = tortilla.get<Transform>();
				transform.rotation[0] = glm::vec4(T, 0.0f);
				transform.rotation[1] = glm::vec4(hit.normal, 0.0f);
				transform.rotation[2] = glm::vec4(N, 0.0f);
				transform.scale = glm::vec3(0.25);
				transform.setParent(hit.entity);
				//tortilla.add(MeshFilter(assets.get<RenderMesh>("models/Circle.objm"), assets.get<Material>("materials/Tortilla.mat")));
				//tortilla.add(PointLight(glm::vec3(0.25, 0.25, 1), 10.f, 2.f));
				tortilla.add(LightFade(10));

				glm::vec3 offset = hit.worldPos - hit.entity.get<RigidBody>().getCenterOfMassPosition();
				PhysicsSystem::Impulse::Emit(hit.entity, +(glm::vec3(t.getRotation()[2]) * 2.f), offset);
			}*/
		}

		
	}
}

void GunSystem::end()
{
}
