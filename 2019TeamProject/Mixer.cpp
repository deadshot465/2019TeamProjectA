#include "Mixer.h"

Mixer::Mixer()
{
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD);
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);

	m_soundMapping.insert(std::pair<SoundList, Mix_Music*>
		(SoundList::Scream, Mix_LoadMUS(SFX_SCREAM.c_str())));
}

Mixer::~Mixer()
{
	for (auto& pair : m_soundMapping) {
		Mix_FreeMusic(pair.second);
	}

	Mix_CloseAudio();
	Mix_Quit();
}

void Mixer::PlaySound(SoundList sound, int loops)
{
	auto res = Mix_PlayMusic(m_soundMapping[sound], loops);
}
