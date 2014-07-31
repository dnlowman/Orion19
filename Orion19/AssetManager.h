#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <map>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

#include "Surface.h"
#include "Sound.h"

class AssetManager
{
	protected:
		/* Variables */
		static AssetManager* instance;
		std::map<std::string, Surface*> surfaces;
		std::map<std::string, Mix_Chunk*> sounds;

		/* Methods */
		AssetManager();

	public:
		/* Methods */
		~AssetManager();
		static AssetManager* ReturnInstance();
		bool PreloadImage(const std::string file);
		Surface* ReturnPreloadedSurface(std::string file);
		bool PreloadSound(const std::string sound);
		Mix_Chunk* ReturnPreloadedSound(std::string file);
};

#endif