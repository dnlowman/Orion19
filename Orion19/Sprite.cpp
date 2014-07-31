#include "Sprite.h"

Sprite::Sprite()
{
	Texture::Texture();
	_state = SpriteStates::E_STATE_DEFAULT;
	_lastTick = 0;
	_fadeDuration = 0;
}

Sprite::~Sprite()
{
	Texture::~Texture();
}

void Sprite::Update()
{
	switch(_state)
	{
		case SpriteStates::E_STATE_FADE_IN:
		{
			if(SDL_GetTicks() > _lastTick + (_fadeDuration / 255))
			{
				if(GetAlpha() != 255)
				{
					SetAlpha(GetAlpha() + 1);
					_lastTick = SDL_GetTicks();
				}
				else _state = SpriteStates::E_STATE_DEFAULT;
			}
			break;
		}

		case SpriteStates::E_STATE_FADE_OUT:
		{
			if(SDL_GetTicks() > _lastTick + (_fadeDuration / 255))
			{
				if(GetAlpha() != 0)
				{
					SetAlpha(GetAlpha() - 1);
					_lastTick = SDL_GetTicks();
				}
				else _state = SpriteStates::E_STATE_DEFAULT;
			}
			break;
		}
	}
}

void Sprite::FadeIn(int time)
{
	_state = SpriteStates::E_STATE_FADE_IN;
	_fadeDuration = time;
	SetAlpha(0);
	_lastTick = SDL_GetTicks();
	std::cout<<"Fade In!\n";
}

void Sprite::FadeOut(int time)
{
	_state = SpriteStates::E_STATE_FADE_IN;
	_fadeDuration = time;
	SetAlpha(255);
	_lastTick = SDL_GetTicks();
}