/*
						--------------------------------
									 Orion 19
								Battle for Sector 12
								  by Daniel Lowman
						--------------------------------

	Description:
		A 2D space shooter game written in C++ using SDL. This is the
		source file which essentially holds the 'core' game loop. Three
		actions get pushes to the current game state, the event, logic and rendering.
		Framerate limitation is also handled here.
*/

/* SDL Library Includes */
#include <SDL.h>

/* STL Includes */
#include <stdlib.h>
#include <time.h>

/* Core Includes */
#include "SDLFramework.h"
#include "StateManager.h"
#include "Utils.h"

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	SDLFramework::Init(SDL_INIT_EVERYTHING);
	SDLFramework::SetFPS(60);

	StateManager::ReturnInstance()->SetState(E_STATE_SPLASH);

	while(SDLFramework::IsRunning() == true)
	{
		SDLFramework::START_FRAME = SDL_GetTicks();
		
		/* Event Loop */
		while(SDL_PollEvent(&SDLFramework::evt))
		{
			StateManager::ReturnInstance()->OnEvent(SDLFramework::evt);
			if (SDLFramework::evt.type == SDL_QUIT) SDLFramework::Quit();
		}

		/* Logic */
		StateManager::ReturnInstance()->OnLogic();

		/* Renderer Update */
		SDL_RenderClear(SDLFramework::ReturnRenderer());
		StateManager::ReturnInstance()->OnRender();
		SDL_RenderPresent(SDLFramework::ReturnRenderer());

		SDLFramework::FRAME_DURATION = SDL_GetTicks() - SDLFramework::START_FRAME;
		if(SDLFramework::FRAME_DURATION < (1000 / SDLFramework::ReturnFPS())) SDL_Delay((1000 / SDLFramework::ReturnFPS()) - SDLFramework::FRAME_DURATION);
	}

	StateManager::ReturnInstance()->Quit();
	atexit(SDL_Quit);
	return 1;
}