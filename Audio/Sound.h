#pragma once
#include <fmod.hpp>

class Sound
{
	friend class AudioSystem;
public:

private:
	FMOD::Sound* fmodSound = nullptr;
};
