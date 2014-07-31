#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>

#include "IGameObject.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Utils.h"
#include "Sound.h"

enum class E_PLAYER_STATES
{
	E_STATE_MULTI_SHOOT,
	E_STATE_SPEED,
	E_STATE_SHIELD,
};

class Player : public IGameObject
{
	protected:
		double _tmpAngle;
		unsigned int   _lastShoot;
		Sound shoot;

	public:
		Player();
		~Player();
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
};

#endif