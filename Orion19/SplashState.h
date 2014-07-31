#ifndef SPLASH_STATE
#define SPLASH_STATE

#include <iostream>

#include "IState.h"
#include "Texture.h"
#include "SDLFramework.h"
#include "StateManager.h"
#include "Sound.h"
#include "AssetManager.h"

enum
{
	E_SPLASH_STATE_CH_INTRO,
	E_SPLASH_STATE_CH_OUTRO,
	E_SPLASH_STATE_COM_INTRO,
	E_SPLASH_STATE_COM_OUTRO,
	E_SPLASH_STATE_LOGO_INTRO,
	E_SPLASH_STATE_LOGO_OUTRO,
};

class SplashState : public IState
{
	protected:
		/* Variables */
		Texture gameLogo;
		Texture codeheads;
		Texture comlogo;
		int splashState;
		Sound snd;

	public:
		/* Methods */
		SplashState();
		~SplashState();
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif