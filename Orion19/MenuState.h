#ifndef MENU_STATE
#define MENU_STATE

#include "IState.h"
#include "Map.h"
#include "Sprite.h"
#include "Button.h"
#include "StateManager.h"
#include "Sound.h"

class MenuState : public IState
{
	protected:
		Map _bg;
		Sprite _logo;
		Button _playButton;
		Button _creditsButton;
		Button _quitButton;
		Button _helpButton;
		Sound  _snd;
	
	public:
		MenuState();
		~MenuState();
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif