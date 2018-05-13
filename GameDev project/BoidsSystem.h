#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
COMPONENT(Boid, 64)
{
	float separationRadius;
	float separationFactor;

	float cohesionRadius;
	float cohesionFactor;

	float alignmentRadius;
	float alignmentFactor;

	float maxVelocity;
	void load(const nlohmann::json& j)
	{
		separationRadius = j["separation radius"];
		separationFactor = j["separation factor"];
		cohesionRadius = j["cohesion radius"];
		cohesionFactor = j["cohesion factor"];
		alignmentRadius = j["alignment radius"];
		alignmentFactor = j["alignment factor"];
		maxVelocity = j["max velocity"];
	}
};

class BoidsSystem : public ECS::System
{
public:
	BoidsSystem();
	~BoidsSystem();
	void init() override;
	void update() override;
	void end() override;

private:
	ECS::EntitySubscription& boids;
	
};

