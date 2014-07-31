#ifndef HELP_STATE_H
#define HELP_STATE_H

#include "IState.h"
#include "Sprite.h"
#include "Button.h"
#include "StateManager.h"

class HelpState : public IState
{
	protected:
		Sprite _help;
		Button _goBack;

	public:
		HelpState();
		~HelpState();
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif