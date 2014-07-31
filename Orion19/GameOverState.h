#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <string>
#include <sstream>

#include "IState.h"
#include "Sprite.h"
#include "Button.h"
#include "StateManager.h"
#include "GameManager.h"

class GameOverState : public IState
{
	protected:
		Sprite _gameOverText;
		Sprite _score;
		Button _playAgain;
		Button _quit;

	public:
		GameOverState();
		~GameOverState();
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif