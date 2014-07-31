#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <algorithm>
#include <math.h>

#include "IGameObject.h"
#include "Utils.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Explosion.h"
#include "Particle.h"
#include "Timer.h"
#include "Sound.h"
#include "Planet.h"

enum class E_GAME_OBJECTS : Uint8
{
	E_GAME_OBJECT_PLAYER,
	E_GAME_OBJECT_BULLET,
	E_GAME_OBJECT_ENEMY,
	E_GAME_OBJECT_PICKUP,
	E_GAME_OBJECT_EXPLOSION,
	E_GAME_OBJECT_PARTICLE,
	E_GAME_OBJECT_TIMER,
	E_GAME_OBJECT_PLANET,
};

enum class E_COLLISION_METHODS : Uint8
{
	E_COLLISION_BOX_BOX,
	E_COLLISION_CIRCLE_CIRCLE,
	E_COLLISION_CIRCLE_BOX,
	E_COLLISION_BOX_CIRCLE,
};

class GameManager
{
	protected:
		/* Variables */
		static GameManager* instance;
		std::vector<IGameObject*> playerList;
		std::vector<IGameObject*> bulletList;
		std::vector<IGameObject*> enemyList;
		std::vector<IGameObject*> pickupList;
		std::vector<IGameObject*> explosionList;
		std::vector<IGameObject*> particleList;
		std::vector<IGameObject*> timerList;
		std::vector<IGameObject*> planetList;
		int _gameScore;
		int _lives;
		Sound _pickupSound;

		/* Methods */
		GameManager();

	public:
		/* Methods */
		~GameManager();
		static GameManager* ReturnInstance();
		void Logic();
		void Render();
		IGameObject* AddGameObject(E_GAME_OBJECTS type);
		//void RemoveGameObject();
		void OnEvent(SDL_Event evt);
		IGameObject* IsObjectColliding(IGameObject* object, E_COLLISION_METHODS method, Uint8 exclude);
		void SetScore(int score) { _gameScore = score; };
		int GetScore() const { return _gameScore; };
		void SetLives(int value) { _lives = value; };
		int  GetLives() const { return _lives; };
		Uint32 GetPlayers() const { return playerList.size(); };
		void KillAll();

};

#endif