#include "GameManager.h"

// member function pointer

GameManager* GameManager::instance = nullptr;

GameManager::GameManager(void)
{
	_gameScore = 0;
	_lives = 3;
	_pickupSound.Load("sounds\\pickup.wav");
}


GameManager::~GameManager(void)
{
	for (unsigned int i = 0; i < playerList.size(); ++i) if (playerList.at(i) != nullptr) delete playerList.at(i);
	for (unsigned int i = 0; i < bulletList.size(); ++i) if (bulletList.at(i) != nullptr) delete bulletList.at(i);
	for (unsigned int i = 0; i < enemyList.size(); ++i) if (enemyList.at(i) != nullptr) delete enemyList.at(i);
	for (unsigned int i = 0; i < pickupList.size(); ++i) if (pickupList.at(i) != nullptr) delete pickupList.at(i);
	for (unsigned int i = 0; i < explosionList.size(); ++i) if (explosionList.at(i) != nullptr) delete explosionList.at(i);
	for (unsigned int i = 0; i < particleList.size(); ++i) if (particleList.at(i) != nullptr) delete particleList.at(i);
	for (unsigned int i = 0; i < timerList.size(); ++i) if (timerList.at(i) != nullptr) delete timerList.at(i);
	for (unsigned int i = 0; i < planetList.size(); ++i) if (planetList.at(i) != nullptr) delete planetList.at(i);
	GameManager::instance = nullptr;
}

GameManager* GameManager::ReturnInstance()
{
	if(instance == nullptr) instance = new GameManager;
	return instance;
}

void GameManager::Logic()
{
	for (unsigned int i = 0; i < playerList.size(); ++i)
	{
		playerList.at(i)->Logic();
		
		for (unsigned int _i = 0; _i < bulletList.size(); ++_i)
		{
			if (bulletList.at(_i)->ReturnType() != (Uint8)BulletTypes::E_BULLET_TYPE_PLAYER)
			{
				if (playerList.at(i)->ReturnType() != (Uint8)E_PLAYER_STATES::E_STATE_SHIELD)
				{
					if (bulletList.at(_i)->ReturnSprite()->GetX() > playerList.at(i)->ReturnSprite()->GetX() && bulletList.at(_i)->ReturnSprite()->GetX() < playerList.at(i)->ReturnSprite()->GetX() + playerList.at(i)->ReturnSprite()->GetWidth())
					{
						if (bulletList.at(_i)->ReturnSprite()->GetY() > playerList.at(i)->ReturnSprite()->GetY() && bulletList.at(_i)->ReturnSprite()->GetY() < playerList.at(i)->ReturnSprite()->GetY() + playerList.at(i)->ReturnSprite()->GetHeight())
						{
							bulletList.at(_i)->SetAlive(false);
							delete bulletList.at(_i);
							bulletList.erase(bulletList.begin() + _i);
							_lives -= 1;
							playerList.at(i)->SetVelocity(0.0);
							KillAll();
							IGameObject* _cache = AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_EXPLOSION);
							_cache->ReturnSprite()->SetX(playerList.at(i)->ReturnSprite()->GetX());
							_cache->ReturnSprite()->SetY(playerList.at(i)->ReturnSprite()->GetY());
							
							
							/*playerList.at(i)->ReturnSprite()->SetX(0);
							playerList.at(i)->ReturnSprite()->SetY(300);
							*/
							playerList.at(i)->SetAlive(false);

							_gameScore -= 1;
						}
					}
				}
			}
		}
		
		if (playerList.at(i)->GetAlive() == false)
		{
			delete playerList.at(i);
			playerList.erase(playerList.begin() + i);
		}
	}

	for (unsigned int i = 0; i < explosionList.size(); ++i)
	{
		explosionList.at(i)->Logic();
		if (explosionList.at(i)->GetAlive() == false)
		{
			delete explosionList.at(i);
			explosionList.erase(explosionList.begin() + i);
		}
	}

	for (unsigned int i = 0; i < planetList.size(); ++i)
	{
		planetList.at(i)->Logic();
	}

	for (unsigned int i = 0; i < timerList.size(); ++i)
	{
		timerList.at(i)->Logic();
	}

	for(unsigned int i = 0; i < pickupList.size(); ++i)
	{
		pickupList.at(i)->Logic();

		int _screenWidth, _screenHeight;
		SDL_GetWindowSize(SDLFramework::ReturnWindow(), &_screenWidth, &_screenHeight);
		if (pickupList.at(i)->ReturnSprite()->GetX() < 0 || pickupList.at(i)->ReturnSprite()->GetY() < 0) pickupList.at(i)->SetAlive(false);


		for(unsigned int _i = 0; _i < playerList.size(); ++_i)
		{
			if (((pickupList.at(i)->ReturnSprite()->GetX() > playerList.at(_i)->ReturnSprite()->GetX() && pickupList.at(i)->ReturnSprite()->GetX() < playerList.at(_i)->ReturnSprite()->GetX() + playerList.at(_i)->ReturnSprite()->GetWidth()) || (pickupList.at(i)->ReturnSprite()->GetX() + pickupList.at(i)->ReturnSprite()->GetWidth() > playerList.at(_i)->ReturnSprite()->GetX() && pickupList.at(i)->ReturnSprite()->GetX() + pickupList.at(i)->ReturnSprite()->GetWidth() < playerList.at(_i)->ReturnSprite()->GetX() + playerList.at(_i)->ReturnSprite()->GetWidth())) && ((pickupList.at(i)->ReturnSprite()->GetY() > playerList.at(_i)->ReturnSprite()->GetY() && pickupList.at(i)->ReturnSprite()->GetY() < playerList.at(_i)->ReturnSprite()->GetY() + playerList.at(_i)->ReturnSprite()->GetHeight()) || (pickupList.at(i)->ReturnSprite()->GetY() + pickupList.at(i)->ReturnSprite()->GetHeight() > playerList.at(_i)->ReturnSprite()->GetY() && pickupList.at(i)->ReturnSprite()->GetY() + pickupList.at(i)->ReturnSprite()->GetHeight() < playerList.at(_i)->ReturnSprite()->GetY() + playerList.at(_i)->ReturnSprite()->GetHeight())))
			{
				pickupList.at(i)->SetAlive(false);
				playerList.at(_i)->OnPickupPickup(pickupList.at(i));
				_pickupSound.Play();
				switch(pickupList.at(i)->ReturnType())
				{
					case (Uint8)E_PICKUP_TYPES::E_TYPE_HEALTH:
					{
						++_lives;
						_gameScore += 1;
						break;
					}

					case (Uint8)E_PICKUP_TYPES::E_TYPE_MULTI_SHOOT:
					{
						playerList.at(_i)->SetState((Uint8)E_PLAYER_STATES::E_STATE_MULTI_SHOOT);
						_gameScore += 1;
						break;
					}

					case (Uint8)E_PICKUP_TYPES::E_TYPE_SHIELD:
					{
						playerList.at(_i)->SetState((Uint8)E_PLAYER_STATES::E_STATE_SHIELD);
						_gameScore += 1;
						break;
					}

					case (Uint8)E_PICKUP_TYPES::E_TYPE_SPEED:
					{
						playerList.at(_i)->SetState((Uint8)(E_PLAYER_STATES::E_STATE_SPEED));
						_gameScore += 1;
						break;
					}
				}
			}

			if(pickupList.at(i)->GetAlive() == false)
			{
				delete pickupList.at(i);
				pickupList.erase(pickupList.begin() + i);
			}
		}
	}

	for (unsigned int i = 0; i < bulletList.size(); ++i)
	{
		bulletList.at(i)->Logic();

		int _screenWidth, _screenHeight;
		SDL_GetWindowSize(SDLFramework::ReturnWindow(), &_screenWidth, &_screenHeight);
		if (bulletList.at(i)->ReturnSprite()->GetX() < 0 || bulletList.at(i)->ReturnSprite()->GetY() < 0 || bulletList.at(i)->ReturnSprite()->GetX() + bulletList.at(i)->ReturnSprite()->GetWidth() > _screenWidth || bulletList.at(i)->ReturnSprite()->GetY() + bulletList.at(i)->ReturnSprite()->GetHeight() > _screenHeight)
		{
			delete bulletList.at(i);
			bulletList.erase(bulletList.begin() + i);
		}
	}

	for (unsigned int i = 0; i < particleList.size(); ++i)
	{
		particleList.at(i)->Logic();

		if (particleList.at(i)->ReturnSprite()->GetX() < 0)
		{
			particleList.at(i)->SetAlive(false);
		}

		if (particleList.at(i)->GetAlive() == false)
		{
			delete particleList.at(i);
			particleList.erase(particleList.begin() + i);
		}
	}

	for(unsigned int i = 0; i < enemyList.size(); ++i)
	{
		enemyList.at(i)->Logic();

		/* Aim at player Logic */

		switch (enemyList.at(i)->ReturnType())
		{
			case (Uint8)E_ENEMY_TYPES::E_TYPE_RED: case (Uint8)E_ENEMY_TYPES::E_TYPE_MISSILE:
			{
				if (playerList.size() > 0)
				{
					double tmpX, tmpY, tmpAngle;
					tmpX = playerList.at(0)->ReturnSprite()->GetX() - enemyList.at(i)->ReturnSprite()->GetX();
					tmpY = playerList.at(0)->ReturnSprite()->GetY() - enemyList.at(i)->ReturnSprite()->GetY();
					tmpAngle = Utils::RadiansToDegrees(std::atan2(tmpY, tmpX));
					enemyList.at(i)->ReturnSprite()->SetAngle(tmpAngle);

					double x, y;
					x = enemyList.at(i)->ReturnSprite()->GetX();
					y = enemyList.at(i)->ReturnSprite()->GetY();

					Utils::GetXYInFrontOfPoint(x, y, tmpAngle, 2.0);
					enemyList.at(i)->ReturnSprite()->SetX(x);
					enemyList.at(i)->ReturnSprite()->SetY(y);
					break;
				}
			}

			case (Uint8)E_ENEMY_TYPES::E_TYPE_DRONE:
			{
				enemyList.at(i)->ReturnSprite()->SetX((float)(enemyList.at(i)->ReturnSprite()->GetX() - 3.5));
				break;
			}
		}

		for (unsigned int _i = 0; _i < bulletList.size(); ++_i)
		{
			if (bulletList.at(_i)->ReturnType() != (Uint8)BulletTypes::E_BULLET_TYPE_ENEMY)
			{
				if (((enemyList.at(i)->ReturnSprite()->GetX() > bulletList.at(_i)->ReturnSprite()->GetX() && enemyList.at(i)->ReturnSprite()->GetX() < bulletList.at(_i)->ReturnSprite()->GetX() + bulletList.at(_i)->ReturnSprite()->GetWidth()) || (enemyList.at(i)->ReturnSprite()->GetX() + enemyList.at(i)->ReturnSprite()->GetWidth() > bulletList.at(_i)->ReturnSprite()->GetX() && enemyList.at(i)->ReturnSprite()->GetX() + enemyList.at(i)->ReturnSprite()->GetWidth() < bulletList.at(_i)->ReturnSprite()->GetX() + bulletList.at(_i)->ReturnSprite()->GetWidth())) && ((enemyList.at(i)->ReturnSprite()->GetY() > bulletList.at(_i)->ReturnSprite()->GetY() && enemyList.at(i)->ReturnSprite()->GetY() < bulletList.at(_i)->ReturnSprite()->GetY() + bulletList.at(_i)->ReturnSprite()->GetHeight()) || (enemyList.at(i)->ReturnSprite()->GetY() + enemyList.at(i)->ReturnSprite()->GetHeight() > bulletList.at(_i)->ReturnSprite()->GetY() && enemyList.at(i)->ReturnSprite()->GetY() + enemyList.at(i)->ReturnSprite()->GetHeight() < bulletList.at(_i)->ReturnSprite()->GetY() + bulletList.at(_i)->ReturnSprite()->GetHeight())))
				{
					enemyList.at(i)->SetAlive(false);
					bulletList.at(_i)->SetAlive(false);
					delete bulletList.at(_i);
					bulletList.erase(bulletList.begin() + _i);
					_gameScore += 3;
					IGameObject* _cache = AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_EXPLOSION);
					_cache->ReturnSprite()->SetX(enemyList.at(i)->ReturnSprite()->GetX());
					_cache->ReturnSprite()->SetY(enemyList.at(i)->ReturnSprite()->GetY());
				}
			}
		}

		for (unsigned int _i = 0; _i < playerList.size(); ++_i)
		{
			if (((enemyList.at(i)->ReturnSprite()->GetX() > playerList.at(_i)->ReturnSprite()->GetX() && enemyList.at(i)->ReturnSprite()->GetX() < playerList.at(_i)->ReturnSprite()->GetX() + playerList.at(_i)->ReturnSprite()->GetWidth()) || (enemyList.at(i)->ReturnSprite()->GetX() + enemyList.at(i)->ReturnSprite()->GetWidth() > playerList.at(_i)->ReturnSprite()->GetX() && enemyList.at(i)->ReturnSprite()->GetX() + enemyList.at(i)->ReturnSprite()->GetWidth() < playerList.at(_i)->ReturnSprite()->GetX() + playerList.at(_i)->ReturnSprite()->GetWidth())) && ((enemyList.at(i)->ReturnSprite()->GetY() > playerList.at(_i)->ReturnSprite()->GetY() && enemyList.at(i)->ReturnSprite()->GetY() < playerList.at(_i)->ReturnSprite()->GetY() + playerList.at(_i)->ReturnSprite()->GetHeight()) || (enemyList.at(i)->ReturnSprite()->GetY() + enemyList.at(i)->ReturnSprite()->GetHeight() > playerList.at(_i)->ReturnSprite()->GetY() && enemyList.at(i)->ReturnSprite()->GetY() + enemyList.at(i)->ReturnSprite()->GetHeight() < playerList.at(_i)->ReturnSprite()->GetY() + playerList.at(_i)->ReturnSprite()->GetHeight())))
			{
				enemyList.at(i)->SetAlive(false);
				KillAll();
				IGameObject* _cache = AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_EXPLOSION);
				_cache->ReturnSprite()->SetX(playerList.at(_i)->ReturnSprite()->GetX());
				_cache->ReturnSprite()->SetY(playerList.at(_i)->ReturnSprite()->GetY());
				/*
				playerList.at(_i)->ReturnSprite()->SetX(0);
				playerList.at(_i)->ReturnSprite()->SetY(300);
				playerList.at(_i)->SetVelocity(0.0);
				*/

				playerList.at(_i)->SetAlive(false);
				_gameScore -= 1;
				--_lives;
			}
		}

		if (enemyList.at(i)->GetAlive() == false)
		{
			delete enemyList.at(i);
			enemyList.erase(enemyList.begin() + i);
		}
	}
}

void GameManager::Render()
{
	// Draws in order...
	for (unsigned int i = 0; i < planetList.size(); ++i) if (planetList.at(i) != nullptr) planetList.at(i)->Render();
	for (unsigned int i = 0; i < particleList.size(); ++i) if (particleList.at(i) != nullptr) particleList.at(i)->Render();
	for (unsigned int i = 0; i < bulletList.size(); ++i) if (bulletList.at(i) != nullptr) bulletList.at(i)->Render();
	for (unsigned int i = 0; i < playerList.size(); ++i) if (playerList.at(i) != nullptr) playerList.at(i)->Render();
	for (unsigned int i = 0; i < enemyList.size(); ++i) if (enemyList.at(i) != nullptr) enemyList.at(i)->Render();
	for (unsigned int i = 0; i < pickupList.size(); ++i) if (pickupList.at(i) != nullptr) pickupList.at(i)->Render();
	for (unsigned int i = 0; i < explosionList.size(); ++i) if (explosionList.at(i) != nullptr) explosionList.at(i)->Render();
}

void GameManager::OnEvent(SDL_Event evt)
{
	for (unsigned int i = 0; i < playerList.size(); ++i) if (playerList.at(i) != nullptr) playerList.at(i)->OnEvent(evt);
	for (unsigned int i = 0; i < bulletList.size(); ++i) if (bulletList.at(i) != nullptr) bulletList.at(i)->OnEvent(evt);
	for (unsigned int i = 0; i < enemyList.size(); ++i) if (enemyList.at(i) != nullptr) enemyList.at(i)->OnEvent(evt);
	for (unsigned int i = 0; i < pickupList.size(); ++i) if (pickupList.at(i) != nullptr) pickupList.at(i)->OnEvent(evt);
	for (unsigned int i = 0; i < explosionList.size(); ++i) if (explosionList.at(i) != nullptr) explosionList.at(i)->OnEvent(evt);
	for (unsigned int i = 0; i < particleList.size(); ++i) if (particleList.at(i) != nullptr) particleList.at(i)->OnEvent(evt);
	for (unsigned int i = 0; i < planetList.size(); ++i) if (planetList.at(i) != nullptr) planetList.at(i)->OnEvent(evt);
}

IGameObject* GameManager::AddGameObject(E_GAME_OBJECTS type)
{
	switch(type)
	{
		case E_GAME_OBJECTS::E_GAME_OBJECT_PLAYER:
		{
			playerList.push_back(new Player);
			return playerList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_BULLET:
		{
			bulletList.push_back(new Bullet);
			return bulletList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_ENEMY:
		{
			int _rand = rand() % 3 + 1;
			switch (_rand)
			{
				case 1:
				{
					enemyList.push_back(new Enemy(E_ENEMY_TYPES::E_TYPE_DRONE));
					break;
				}

				case 2:
				{
					enemyList.push_back(new Enemy(E_ENEMY_TYPES::E_TYPE_RED));
					break;
				}
				case 3:
				{
					enemyList.push_back(new Enemy(E_ENEMY_TYPES::E_TYPE_MISSILE));
					break;
				}
			}
			return enemyList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_PICKUP:
		{
			int _rand = rand() % 3;
			pickupList.push_back(new Pickup((E_PICKUP_TYPES)_rand));
			return pickupList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_EXPLOSION:
		{
			explosionList.push_back(new Explosion);
			return explosionList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_PARTICLE:
		{
			particleList.push_back(new Particle);
			return particleList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_TIMER:
		{
			timerList.push_back(new Timer);
			return timerList.back();
		}

		case E_GAME_OBJECTS::E_GAME_OBJECT_PLANET:
		{
			planetList.push_back(new Planet);
			return planetList.back();
		}
	}
	return nullptr;
}

void GameManager::KillAll()
{
	for (unsigned int i = 0; i < bulletList.size(); ++i) if (bulletList.at(i) != nullptr) bulletList.at(i)->SetAlive(false);
	for (unsigned int i = 0; i < enemyList.size(); ++i) if (enemyList.at(i) != nullptr) enemyList.at(i)->SetAlive(false);
	for (unsigned int i = 0; i < pickupList.size(); ++i) if (pickupList.at(i) != nullptr) pickupList.at(i)->SetAlive(false);
	for (unsigned int i = 0; i < explosionList.size(); ++i) if (explosionList.at(i) != nullptr) explosionList.at(i)->SetAlive(false);
	for (unsigned int i = 0; i < particleList.size(); ++i) if (particleList.at(i) != nullptr) particleList.at(i)->SetAlive(false);
	for (unsigned int i = 0; i < timerList.size(); ++i) if (timerList.at(i) != nullptr) timerList.at(i)->SetAlive(false);
}