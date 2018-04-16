#include "AudioSystem.h"
#include <cstddef>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <fmod_common.h>

SoundLoader::SoundLoader(FMOD::System* system): system(system)
{
}

void SoundLoader::load(std::string file, void* location)
{
	Sound* snd = new (location) Sound;
	system->createSound(file.c_str(), FMOD_DEFAULT, 0, &snd->fmodSound);
}

AudioSystem::AudioSystem(Assets& assets): system(nullptr),
assets(assets)
{
}


AudioSystem::~AudioSystem()
{
}

void AudioSystem::init()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result) << std::endl;
		enabled = false;
		return;
	}

	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result) << std::endl;
		enabled = false;
		return;
	}

	FMOD::Channel    *channel = nullptr;

	soundLoader = new SoundLoader(system);
	assets.registerLoader<Sound>(soundLoader);

	FMOD::Sound* sound;
	system->createSound("audio/Laser_Shoot.wav", FMOD_DEFAULT, 0, &sound);
	system->playSound(sound, 0, false, &channel);
}

void AudioSystem::update()
{
}

void AudioSystem::end()
{
	delete soundLoader;
}