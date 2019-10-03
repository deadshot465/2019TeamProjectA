#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include "Helper.h"

class Mixer
{
private:
	inline static const std::string SFX_SCREAM = "sfx/132106__sironboy__woman-scream.wav";

	std::unordered_map<SoundList, Mix_Music*> m_soundMapping;

public:
	Mixer();
	~Mixer();

	void PlaySound(SoundList sound, int loops = 0);
};