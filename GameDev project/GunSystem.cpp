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


GunSystem::GunSystem(Assets& assets) :
	entities(SubscriptionManager::getSubscription(Aspect::getAspect<Transform, Gun>())),
	ui(nullptr), physics(nullptr), shoot(nullptr),
	assets(assets)
{
}


GunSystem::~GunSystem()
{
}

void GunSystem::init()
{
	ui = SystemManager::getSystem<UISystem>();
	physics = SystemManager::getSystem<PhysicsSystem>();

	shoot = ui->getInput("Shoot");
}

void GunSystem::update()
{
	for(Entity e : entities)
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

			PhysicsSystem::Hit hit;
			physics->RayCastClosest(t.position, t.position + glm::vec3(t.rotation[2]) * 100.f, hit);
			if (hit.hasHit)
			{
				//glm::vec3 offset =glm::vec3( glm::inverse(hit.entity.get<Transform>().getMatrix()) * glm::vec4(hit.worldPos, 1.0));
				glm::vec3 offset = hit.worldPos - hit.entity.get<RigidBody>().getCenterOfMassPosition();
				PhysicsSystem::Impulse::Emit(hit.entity, +(glm::vec3(t.rotation[2]) * 2.f), offset);

				glm::vec3 pos = hit.worldPos + hit.normal * 0.05f;

				Entity light = Entity::create();
				light.add(Transform());
				light.get<Transform>().position = pos;
				glm::vec3 T = glm::cross(hit.normal, glm::vec3(0.0, 0.0, 1.0));
				light.get<Transform>().rotation = glm::lookAt(glm::vec3(0, 0, 0), T, hit.normal);
				light.get<Transform>().scale = glm::vec3(0.1);
				light.get<Transform>().setParent(hit.entity);
				light.add(MeshFilter(assets.renderMeshes.get("models/suzane.objm"), assets.materials.get("materials/MarbleRed.mat")));
				light.add(PointLight(glm::vec3(0.25, 0.25, 1), 10.f, 2.f));
				light.add(LightFade(10));
			}
		}

		
	}
}

void GunSystem::end()
{
}
