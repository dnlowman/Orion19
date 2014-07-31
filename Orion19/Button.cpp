#include "Button.h"

Button::Button()
{
	_sprite.SetAngle(-90);
	_string = "NO TEXT SET";
	_sprite.UpdateText(_string.c_str(), 255, 255, 255, 255);
	_state = E_BUTTON_STATES::E_BUTTON_DEFAULT;
}

Button::~Button()
{

}

void Button::Logic()
{

}

void Button::Render()
{
	_sprite.Render();
}

void Button::OnEvent(SDL_Event evt)
{
	if (evt.motion.x > _sprite.GetX() && evt.motion.x < _sprite.GetX() + _sprite.GetWidth() &&
		evt.motion.y > _sprite.GetY() && evt.motion.y < _sprite.GetY() + _sprite.GetHeight())
	{
		if (evt.type == SDL_MOUSEBUTTONDOWN && evt.button.button == SDL_BUTTON_LEFT)
		{
			_sprite.UpdateText(_string.c_str(), 255, 217, 138, 82);
			_state = E_BUTTON_STATES::E_BUTTON_CLICKED;
		}
		else
		{
			_sprite.UpdateText(_string.c_str(), 255, 168, 77, 77);
			_state = E_BUTTON_STATES::E_BUTTON_HOVER;
		}
	}
	else
	{
		_sprite.UpdateText(_string.c_str(), 255, 255, 255, 255);
		_state = E_BUTTON_STATES::E_BUTTON_DEFAULT;
	}
}

void Button::SetText(std::string text)
{
	_string = text;
	_sprite.UpdateText(_string.c_str(), 255, 255, 255, 255);
}