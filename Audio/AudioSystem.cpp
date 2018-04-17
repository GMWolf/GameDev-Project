#include "AudioSystem.h"
#include <cstddef>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <fmod_common.h>
#include "AudioEvent.h"

SoundLoader::SoundLoader(FMOD::System* system): system(system)
{
}

bool SoundLoader::load(std::string file, void* location)
{
	FMOD_RESULT result;
	Sound* snd = new (location) Sound;
	result = system->createSound(file.c_str(), FMOD_DEFAULT, 0, &snd->fmodSound);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD eroor!" << result << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	return true;
}

AudioSystem::AudioSystem(Assets& assets): system(nullptr), soundLoader(nullptr),
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

	

	soundLoader = new SoundLoader(system);
	assets.registerLoader<Sound>(soundLoader);
}

void AudioSystem::update()
{

	while(!audioEvents.empty())
	{
		AudioEvent& ae = audioEvents.front();
	
		Sound& snd = assets.resolve(ae.sound);

		system->playSound(snd.fmodSound, 0, false, &channel);

		audioEvents.pop();
	}

	system->update();

}

void AudioSystem::end()
{
	delete soundLoader;
}