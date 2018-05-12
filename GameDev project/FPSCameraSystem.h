#pragma once
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "System.h"
#include "UISystem.h"

COMPONENT(FPSCamera, 1, 24)
{
	std::string horizontal;
	std::string vertical;

	void load(const nlohmann::json& j)
	{
		horizontal = j["horizontal"].get<std::string>();
		vertical = j["vertical"].get<std::string>();

		if (j.find("body") != j.end())
		{
			body = ECS::getLoadGroup().getEntity(j["body"]);
		}
	}

	ECS::Entity body;
};

class FPSCameraSystem : public ECS::System
{
public:
	FPSCameraSystem();
	~FPSCameraSystem();
	void init() override;
	void update() override;
	void end() override;

private:
	ECS::EntitySubscription& entities;
	UISystem* uisystem;
};

