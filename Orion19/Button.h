#ifndef BUTTON_H
#define BUTTON_H

#include <string.h>

#include "IGameObject.h"

enum class E_BUTTON_STATES : Uint8
{
	E_BUTTON_CLICKED,
	E_BUTTON_HOVER,
	E_BUTTON_DEFAULT,
};

class Button : public IGameObject
{
	protected:
		std::string _string;
		E_BUTTON_STATES _state;

	public:
		Button();
		~Button();
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
		void SetText(std::string text);
		E_BUTTON_STATES GetState() { return _state; };
};

#endif