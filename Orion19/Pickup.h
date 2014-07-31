#ifndef PICKUP_H
#define PICKUP_H

#include <stdlib.h>

#include "IGameObject.h"
#include "Sound.h"

enum class E_PICKUP_TYPES : Uint8
{
	E_TYPE_HEALTH,
	E_TYPE_SPEED,
	E_TYPE_MULTI_SHOOT,
	E_TYPE_SHIELD,
};


class Pickup : public IGameObject
{
	public:
		Pickup(E_PICKUP_TYPES type);
		~Pickup(void);
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
};

#endif