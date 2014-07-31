/*
	Class:
		Default State

	Description:
		This is the main game state, the majority of the games logic is scripted here.
*/

#include "DefaultState.h"

DefaultState::DefaultState()
{
	GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_PLAYER);
	score.UpdateText("Score: 0", 255, 255, 255, 255);
	score.SetX(300);
	score.SetY(20);
	score.SetAngle(-90);
	_pausedText.UpdateText("PAUSED", 255, 255, 255, 255);
	_pausedText.SetAngle(-90);
	_pausedText.SetX(400 - (_pausedText.GetWidth() / 2));
	_pausedText.SetY(300);
	lives.UpdateText("Lives: 10", 255, 255, 255, 255);
	lives.SetX(10);
	lives.SetY(20);
	lives.SetAngle(-90);
	_quitButton.SetText("Quit");
	_quitButton.SetX(400 - (_quitButton.ReturnSprite()->GetWidth() / 2));
	_quitButton.SetY(420);
	_enemyLastSpawn = SDL_GetTicks();
	_pickupLastSpawn = SDL_GetTicks();
	_planetLastSpawn = SDL_GetTicks();
	_gameOver.UpdateText("Game Over", 255, 255, 255, 255);
	_gameOver.SetX(400 - (_gameOver.GetWidth() / 2));
	_gameOver.SetY(400);
	_gameOver.SetAngle(-90);
	_paused = false;
	_snd.Load("sounds\\dss.wav");
	_snd.Play(1);

	respawnTimer.SetType((Uint8)E_TIMER_TYPE::E_TIMER_COUNT_DOWN);
	respawnTimer.SetSeconds(1000);
	respawnTimer.SetFrame(5);
	respawnTimer.SetX(200);
	respawnTimer.SetY(300 - (respawnTimer.ReturnSprite()->GetHeight()));
}

DefaultState::~DefaultState()
{
	_snd.Stop();
}

void DefaultState::OnLogic()
{	
	if (GameManager::ReturnInstance()->GetLives() != 0)
	{
		std::ostringstream _format;
		if (!_paused)
		{
			bg.Logic();
			if (GameManager::ReturnInstance()->GetPlayers() == 0)
			{
				respawnTimer.Logic();
				if (respawnTimer.GetFrame() == 0)
				{
					GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_PLAYER);
					respawnTimer.SetFrame(5);
				}
			}

			GameManager::ReturnInstance()->Logic();
			_format << "Score: " << GameManager::ReturnInstance()->GetScore();
			score.UpdateText(_format.str().c_str(), 255, 255, 255, 255);
			_format.str("");
			_format.clear();
			_format << "Lives: " << GameManager::ReturnInstance()->GetLives();
			lives.UpdateText(_format.str().c_str(), 255, 255, 255, 255);

			
			if (SDL_GetTicks() > _enemyLastSpawn + 3000)
			{
				IGameObject* _cache = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_ENEMY);
				_enemyLastSpawn = SDL_GetTicks();
			}

			if (SDL_GetTicks() > _pickupLastSpawn + 5000)
			{
				IGameObject* _cache = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_PICKUP);
				_pickupLastSpawn = SDL_GetTicks();
			}

			if (SDL_GetTicks() > _planetLastSpawn + 15000)
			{
				GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_PLANET);
				_planetLastSpawn = SDL_GetTicks();
			}
			
		}
		else
		{
			if (_quitButton.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED)
			{
				delete GameManager::ReturnInstance();
				StateManager::ReturnInstance()->SetState(E_STATE_MAIN_MENU);
			}
		}
	}
}

void DefaultState::OnRender()
{
	bg.Render();
	GameManager::ReturnInstance()->Render();
	score.Render();
	lives.Render();

	if (GameManager::ReturnInstance()->GetPlayers() == 0) respawnTimer.Render();

	if (_paused)
	{
		_pausedText.Render();
		_quitButton.Render();
	}

	if (GameManager::ReturnInstance()->GetLives() == 0)
	{
		_gameOver.Render();
		StateManager::ReturnInstance()->SetState(E_STATE_GAME_OVER);
	}
}

void DefaultState::OnEvent(SDL_Event evt)
{
	Input::OnEvent(evt); // State wide input...
	GameManager::ReturnInstance()->OnEvent(evt); // Object wide input...
	
	if (GameManager::ReturnInstance()->GetLives() != 0)
	{
		if (evt.key.keysym.sym == SDLK_ESCAPE)
		{
			switch (evt.type)
			{
				case SDL_KEYUP:
				{
					if (_paused != true) _paused = true;
					else _paused = false;
					break;
				}
			}
		}
	}
	if (_paused) _quitButton.OnEvent(evt);
}