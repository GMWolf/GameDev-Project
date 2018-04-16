#pragma once
#include "../ECS/System.h"

class AudioSystem : public ECS::System
{
public:
	AudioSystem();
	~AudioSystem();
	void init() override;
	void update() override;
	void end() override;
};

