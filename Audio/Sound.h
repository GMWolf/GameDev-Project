#pragma once
#include <fmod.hpp>

class Sound
{
	friend class AudioSystem;
	friend class SoundLoader;
public:

private:
	FMOD::Sound* fmodSound = nullptr;
};
