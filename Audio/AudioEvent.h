#pragma once
#include "Event.h"
#include "AssetHandle.h"
#include "Sound.h"
EVENT(AudioEvent)
{
	AudioEvent()
	{
	};
	AudioEvent(AssetHandle<Sound> sound) : sound(sound)
	{
	};
	AssetHandle<Sound> sound;
};
