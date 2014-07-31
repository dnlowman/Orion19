#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "IGameObject.h"
#include "Sprite.h"

class Map : public IGameObject
{
	protected:
		Sprite tile;

	public:
		Map();
		~Map();
		void Render();
		void Logic();
		void OnEvent(SDL_Event evt);
};

#endif