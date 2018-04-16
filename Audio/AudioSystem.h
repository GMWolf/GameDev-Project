#pragma once
#include <System.h>
#include <fmod.hpp>
#include <string>
#include "Sound.h"

class AudioSystem : public ECS::System
{
public:
	AudioSystem();
	~AudioSystem();
	void init() override;
	void update() override;
	void end() override;

	void loadSound(std::string file, Sound& snd);

private:
	FMOD::System* system;
};

