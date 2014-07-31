#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>

#include "AssetManager.h"

class Sound
{
	protected:
		Mix_Chunk* snd;
		int		   channel;

	public:
			Sound(void);
			~Sound(void);
			void Play(int loop = 0);
			void Load(std::string file);
			void Stop();
};

#endif