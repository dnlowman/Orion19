/*
	Class:
		SDLFramework

	Description:
		This is a static class for the framework, provide initialisation and shutdown functions
		along with a few additional features including frame rate.
*/

#include "SDLFramework.h"

/* Static Variable Initialization */
SDL_Window* SDLFramework::window = nullptr;
SDL_Renderer* SDLFramework::renderer = nullptr;
SDL_Event SDLFramework::evt;
bool SDLFramework::isRunning = false;
int SDLFramework::FRAMES_PER_SECOND = 60;
int SDLFramework::START_FRAME = 0;
int SDLFramework::FRAME_DURATION = 0;
TTF_Font* SDLFramework::espFont;

Uint32 SDLFramework::Init(Uint32 flags)
{
	Uint32 ticks = SDL_GetTicks();
	std::printf("\n[DEBUG]: SDLFramework::Init - Called with the flags: %i", flags);
	
	if(SDL_Init(flags) == 0)
	{
		if(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer) == -1)
		{
			std::printf("\n[DEBUG]: SDLFramework::Init - SDL_CreateWindowAndRenderer error: %s", SDL_GetError());
			return E_SDL_WR_CREATE_ERROR;
		}

		if(window == nullptr || renderer == nullptr)
		{
			std::printf("\n[DEBUG]: SDLFramework::Init - WINDOW / RENDERER error.", SDL_GetError());

			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Orion 19 - ERROR", "There was an issue creating the window and renderer", NULL);
			return E_SDL_FRAMEWORK_ERROR_WINDOW | E_SDL_FRAMEWORK_RENDERER;
		}

		/* SDL Image */

		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		if((IMG_Init(flags) & flags) != flags)
		{
			std::printf("\n[DEBUG]: SDLFramework::Init - IMG_Init() ERROR!");

			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Orion 19 - ERROR", "There was an issue with SDL_IMG!", NULL);
			return E_SDL_IMAGE_ERROR;
		}

		/* End of SDL Image */

		if(TTF_Init() == -1)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Orion 19 - ERROR", "There was an issue with SDL_TTF!", NULL);
			return E_SDL_TTF_ERROR;
		}
		else
		{
			espFont = TTF_OpenFont("fonts/esp.ttf", 30);
		}

		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

		std::printf("\n[DEBUG]: SDLFramework::Init - Completed took %i", SDL_GetTicks() - ticks);

		SDL_SetWindowTitle(window, "Orion 19 - Battle for Sector 12");
		isRunning = true;
		return true;
	}
	else
	{
		SDL_ShowSimpleMessageBox(E_SDL_FRAMEWORK_ERROR_WINDOW, "Orion 19 - ERROR", SDL_GetError(), NULL);
		return E_SDL_FRAMEWORK_INIT;
	}
}

void SDLFramework::SetFPS(int fps)
{
	FRAMES_PER_SECOND = fps;
}

int SDLFramework::ReturnFPS()
{
	return FRAMES_PER_SECOND;
}

void SDLFramework::Quit()
{
	isRunning = false;
}

bool SDLFramework::IsRunning()
{
	return isRunning;
}

SDL_Window* SDLFramework::ReturnWindow()
{
	return window;
}

SDL_Renderer* SDLFramework::ReturnRenderer()
{
	return renderer;
}

TTF_Font* SDLFramework::ReturnFont()
{
	return espFont;
}