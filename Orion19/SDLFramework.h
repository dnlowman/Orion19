#ifndef SDL_FRAMEWORK_H
#define SDL_FRAMEWORK_H

/* Library Includes */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/* Core Includes */
#include <iostream>

/* Return Bitmask */
enum
{
	E_SDL_FRAMEWORK_ERROR_WINDOW,
	E_SDL_FRAMEWORK_RENDERER,
	E_SDL_FRAMEWORK_INIT,
	E_SDL_WR_CREATE_ERROR,
	E_SDL_IMAGE_ERROR,
	E_SDL_TTF_ERROR,
};

class SDLFramework
{
	protected:
		/* Variables */
		static SDL_Window* window;
		static SDL_Renderer* renderer;
		static bool isRunning;
		static int FRAMES_PER_SECOND;
		static TTF_Font* espFont;

	public:
		/* Variables */
		static SDL_Event evt;
		static int START_FRAME;
		static int FRAME_DURATION;

		/* Methods */
		static SDL_Window* ReturnWindow();
		static SDL_Renderer* ReturnRenderer();
		static Uint32 Init(Uint32 flags);
		static bool IsRunning();
		static void Quit();
		static void SetFPS(int fps);
		static int ReturnFPS();
		static TTF_Font* ReturnFont();
};

#endif