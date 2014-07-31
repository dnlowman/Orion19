#ifndef CREDITS_H
#define CREDITS_H

#include "IState.h"
#include "Sprite.h"
#include "Button.h"
#include "StateManager.h"

class CreditsState : public IState
{
	protected:
		Sprite _credits;
		Button _backButton;

	public:
		CreditsState();
		~CreditsState();
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif