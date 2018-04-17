#pragma once
#include <fmod.hpp>

class Sound
{
	friend class AudioSystem;
	friend class SoundLoader;

private:
	FMOD::Sound* fmodSound = nullptr;
};
