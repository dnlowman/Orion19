#include "Sound.h"

Sound::Sound(void)
{
	snd = nullptr;
}


Sound::~Sound(void)
{
}

void Sound::Play(int loop)
{
	channel = Mix_PlayChannel(-1, snd, loop);
}

void Sound::Load(std::string file)
{
	Mix_Chunk* sound = AssetManager::ReturnInstance()->ReturnPreloadedSound(file);
	if(sound == nullptr) AssetManager::ReturnInstance()->PreloadSound(file);
	snd = AssetManager::ReturnInstance()->ReturnPreloadedSound(file);
}

void Sound::Stop()
{
	Mix_HaltChannel(channel);
}