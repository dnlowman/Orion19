#include "StateManager.h"

StateManager* StateManager::instance = nullptr;

StateManager* StateManager::ReturnInstance()
{
	if(instance == nullptr) { instance = new StateManager(); }
	return instance;
}

StateManager::StateManager()
{
	state = nullptr;
}

StateManager::~StateManager() {}

void StateManager::Quit()
{
	if(instance != nullptr) { delete instance; }
	delete GameManager::ReturnInstance();
}

void StateManager::SetState(Uint32 newState)
{	
	if(state != nullptr)
	{
		delete state;
	}

	switch(newState)
	{
		case E_STATE_DEFAULT:
		{
			state = new DefaultState();
			break;
		}

		case E_STATE_SPLASH:
		{
			state = new SplashState();
			break;
		}

		case E_STATE_MAIN_MENU:
		{
			state = new MenuState();
			break;
		}

		case E_STATE_CREDITS:
		{
			state = new CreditsState();
			break;
		}

		case E_STATE_HELP:
		{
			state = new HelpState();
			break;
		}

		case E_STATE_GAME_OVER:
		{
			state = new GameOverState();
			break;
		}

		default:
		{
			state = new DefaultState();
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Orion 19 - Battle for Sector 12", "ERROR: That state does not exist, reverting to default!", NULL);	
			newState = E_STATE_DEFAULT;
			break;
		}
	}
	stateIdent = newState;
}

void StateManager::OnLogic()
{
	if(state != nullptr)
		state->OnLogic();
}

void StateManager::OnRender()
{
	if(state != nullptr)
		state->OnRender();
}

void StateManager::OnEvent(SDL_Event evt)
{
	if(state != nullptr)
		state->OnEvent(evt);
}