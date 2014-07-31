#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

#include "IGameObject.h"
#include "GameManager.h"
#include "Sound.h"

enum class E_ENEMY_TYPES : Uint8
{
	E_TYPE_RED,
	E_TYPE_DRONE,
	E_TYPE_MISSILE,
};

class Enemy : public IGameObject
{
	protected:
		unsigned int _lastShoot;
		Sound _shoot;

	public:
		Enemy(E_ENEMY_TYPES type);
		~Enemy();
		void Logic();
		void Render();
		void OnEvent(SDL_Event sdl);
		double GetVelocity();
};

#endif