#ifndef STATE_MANAGER
#define STATE_MANAGER

/* Library Includes */
#include <SDL.h>

/* Core Includes */
#include "IState.h"
#include "DefaultState.h"
#include "GameManager.h"
#include "SplashState.h"
#include "MenuState.h"
#include "CreditsState.h"
#include "HelpState.h"
#include "GameOverState.h"

enum
{
	E_STATE_DEFAULT,
	E_STATE_SPLASH,
	E_STATE_GAME,
	E_STATE_LOAD,
	E_STATE_MAIN_MENU,
	E_STATE_CREDITS,
	E_STATE_HELP,
	E_STATE_GAME_OVER,
};

class StateManager
{
	protected:
		/* Variables */
		static StateManager* instance;
		IState* state;
		Uint32 stateIdent;

		/* Methods */
		StateManager();

	public:
		/* Methods */
		~StateManager(void);
		static StateManager* ReturnInstance();
		static void Quit();
		IState* ReturnState() { return state; }
		void SetState(Uint32 newState);
		void OnLogic();
		void OnRender();
		void OnEvent(SDL_Event evt);
};

#endif