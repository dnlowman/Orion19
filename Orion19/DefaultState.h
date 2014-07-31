#ifndef DEFAULT_STATE
#define DEFAULT_STATE

#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>

#include "IState.h"
#include "Sprite.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Map.h"
#include "Explosion.h"
#include "Particle.h"
#include "Button.h"
#include "StateManager.h"
#include "Sound.h"
#include "Timer.h"

class DefaultState : public IState
{
	protected:
		Sprite lives;
		Sprite score;
		Sprite _gameOver;
		Map bg;
		Uint32 _enemyLastSpawn;
		Uint32 _pickupLastSpawn;
		Uint32 _planetLastSpawn;
		Sprite _pausedText;
		bool   _paused;
		Button _quitButton;
		Sound _snd;
		Timer respawnTimer;

	public:
		DefaultState();
		~DefaultState();
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif