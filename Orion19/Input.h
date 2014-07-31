#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <iostream>
#include <map>

#include "SDLFramework.h"

class Input
{
	public:
		std::map<int, bool> keys;
		virtual ~Input(void);
		virtual void OnWindowClose();
		virtual void OnKeyboardKeyDown(SDL_Keysym keysym);
		virtual void OnKeyboardKeyUp(SDL_Keysym keysym);
		virtual void OnEvent(SDL_Event evt);
};

#endif