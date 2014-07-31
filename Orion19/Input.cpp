#include "Input.h"

Input::~Input() {}

void Input::OnEvent(SDL_Event evt)
{	
	switch(evt.type)
	{
		case SDL_QUIT:
		{
			OnWindowClose();
			break;
		}

		case SDL_KEYDOWN:
		{
			OnKeyboardKeyDown(evt.key.keysym);
			break;
		}

		case SDL_KEYUP:
		{
			OnKeyboardKeyUp(evt.key.keysym);
			break;
		}
	}
}

void Input::OnWindowClose()
{
	SDLFramework::Quit();
}

void Input::OnKeyboardKeyDown(SDL_Keysym keysym)
{
	if(keys[keysym.sym] != true) keys[keysym.sym] = true;
}

void Input::OnKeyboardKeyUp(SDL_Keysym keysym)
{
	if(keys[keysym.sym] != false) keys[keysym.sym] = false;
}