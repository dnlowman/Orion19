/*
	Class:
		AssetManager

	Description:
		This is an asset manager which is designed to preload files into memory to prevent
		runtime loading. Other classes can request preloaded files for use.
*/

#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (std::map<std::string, Surface*>::iterator i = surfaces.begin(); i != surfaces.end(); ++i) delete i->second;
	surfaces.clear();
	for(std::map<std::string, Mix_Chunk*>::iterator i = sounds.begin(); i != sounds.end(); ++i) delete i->second;
	sounds.clear();
	instance = nullptr;
}

AssetManager* AssetManager::ReturnInstance()
{
	if(instance == nullptr) instance = new AssetManager;
	return instance;
}

bool AssetManager::PreloadImage(const std::string file)
{
	Surface preCache;
	if(preCache.LoadImage(file) != false)
	{
		surfaces[file] = new Surface;
		surfaces[file]->LoadImage(file);
		return true;
	}
	return false;
}

Surface* AssetManager::ReturnPreloadedSurface(std::string file)
{
	if (surfaces.find(file) == surfaces.end()) return nullptr;
	else return surfaces[file];
}

bool AssetManager::PreloadSound(const std::string sound)
{
	if(sounds[sound] == nullptr)
	{
		sounds[sound] = new Mix_Chunk;
		sounds[sound] = Mix_LoadWAV(sound.c_str());
		return true;
	}
	return false;
}

Mix_Chunk* AssetManager::ReturnPreloadedSound(std::string file)
{
	return sounds[file];
}