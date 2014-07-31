#ifndef PLANET_H
#define PLANET_H

#include <stdlib.h>
#include <string>

#include "IGameObject.h"
#include "Sprite.h"

class Planet : public IGameObject
{
	protected:
		Sprite _img;

	public:
		Planet();
		~Planet();
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
};

#endif