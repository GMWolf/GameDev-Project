#pragma once
#include <System.h>
#include <fmod.hpp>
#include <string>
#include "Sound.h"
#include <AssetLoader.h>
#include "Assets.h"
#include "EntityEvents.h"
#include "AudioEvent.h"

class SoundLoader : public AssetLoader
{
public:
	SoundLoader(FMOD::System* system);;

	bool load(std::string file, void* location) override;

private:
	FMOD::System* system;
};

class AudioSystem : public ECS::System
{
public:
	AudioSystem(Assets& assets);
	~AudioSystem();
	void init() override;
	void update() override;
	void end() override;

private:
	FMOD::System* system;
	SoundLoader* soundLoader;
	Assets& assets;

	FMOD::Channel *channel = nullptr;

	ECS::EventQueue<AudioEvent> audioEvents;
};

