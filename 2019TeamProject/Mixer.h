#pragma once
#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif
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
