#include "Texture.h"

Texture::Texture()
{
	_texture = nullptr;
	_position.x = _offset.x = 0;
	_position.y = _offset.y = 0;
	_position.h = _offset.h = 0;
	_position.w = _offset.w = 0;
	_angle = 0;
	SetAlpha(_alpha);
	_lastTick = SDL_GetTicks();
}

Texture::~Texture()
{
	SDL_DestroyTexture(_texture);
}

bool Texture::UpdateSurface(std::string file)
{
	Surface tmpSurface;
	if(tmpSurface.LoadImage(file) == false) return false;
	_texture = SDL_CreateTextureFromSurface(SDLFramework::ReturnRenderer(), tmpSurface.ReturnSurface());
	_position.w = _offset.w = tmpSurface.ReturnSurface()->w;
	_position.h = _offset.h = tmpSurface.ReturnSurface()->h;
	return true;
}

bool Texture::UpdateAsset(std::string file)
{
	if(AssetManager::ReturnInstance()->ReturnPreloadedSurface(file) == nullptr)
	{
		AssetManager::ReturnInstance()->PreloadImage(file);
		if (AssetManager::ReturnInstance()->ReturnPreloadedSurface(file) == nullptr) return false;
	}
	_texture = SDL_CreateTextureFromSurface(SDLFramework::ReturnRenderer(), AssetManager::ReturnInstance()->ReturnPreloadedSurface(file)->ReturnSurface());
	_position.w = _offset.w = AssetManager::ReturnInstance()->ReturnPreloadedSurface(file)->ReturnSurface()->w;
	_position.h = _offset.h = AssetManager::ReturnInstance()->ReturnPreloadedSurface(file)->ReturnSurface()->h;
	return true;
}

bool Texture::UpdateText(std::string text, Uint8 alpha, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Color col;
	col.a = alpha;
	col.r = red;
	col.b = blue;
	col.g = green;
	SDL_Surface* surface;
	surface = TTF_RenderText_Solid(SDLFramework::ReturnFont(), text.c_str(), col);
	_texture = SDL_CreateTextureFromSurface(SDLFramework::ReturnRenderer(), surface);
	_position.w = _offset.w = surface->w;
	_position.h = _offset.h = surface->h;
	return true;
}

void Texture::SetX(double x)
{
	_x = x;
}

void Texture::SetY(double y)
{
	_y = y;
}

void Texture::SetWidth(int width)
{
	_position.w = width;
}

void Texture::SetHeight(int height)
{
	_position.h = height;
}

void Texture::SetOffsetX(int x)
{
	_offset.x = x;
}

void Texture::SetOffsetY(int y)
{
	_offset.y = y;
}

void Texture::SetOffsetWidth(int width)
{
	_offset.w = width;
}

void Texture::SetOffsetHeight(int height)
{
	_offset.h = height;
}

void Texture::SetAngle(double angle)
{
	_angle = angle;
}

void Texture::IncrementAngle()
{
	_angle += 1;
	if(_angle > 360) _angle = 0;
}

void Texture::DecrementAngle()
{
	_angle -= 1;
	if(_angle < 0) _angle = 360;
}

void Texture::SetAlpha(Uint8 alpha)
{
	_alpha = alpha;
	SDL_SetTextureAlphaMod(_texture, _alpha);
}

double Texture::GetX() const
{
	return _x;
}

double Texture::GetY() const
{
	return _y;
}

int Texture::GetWidth() const
{
	return _position.w;
}

int Texture::GetHeight() const
{
	return _position.h;
}

int Texture::GetOffsetX() const
{
	return _offset.x;
}

int Texture::GetOffsetY() const
{
	return _offset.y;
}

int Texture::GetOffsetWidth() const
{
	return _offset.w;
}

int Texture::GetOffsetHeight() const
{
	return _offset.h;
}

double Texture::GetAngle() const
{
	return _angle;
}

Uint8 Texture::GetAlpha() const
{
	return _alpha;
}

void Texture::Render()
{
	double tmpAngle = _angle;
	double minus = 90.0;
	tmpAngle += minus;
	if(tmpAngle > 360)
	{
		minus += _angle;
		tmpAngle = 0.0 + minus;
	}

	_position.x = (int)(_x + 0.5);
	_position.y = (int)(_y + 0.5);
	SDL_RenderCopyEx(SDLFramework::ReturnRenderer(), _texture, &_offset, &_position, tmpAngle, NULL, SDL_FLIP_NONE);
}

void Texture::Logic()
{
	switch (_state)
	{
		case TextureStates::E_TEXTURE_STATE_FADE_IN:
		{
			if (SDL_GetTicks() > _lastTick + (_fadeDuration / 255))
			{
				if (GetAlpha() != 255)
				{
					SetAlpha(GetAlpha() + 1);
					_lastTick = SDL_GetTicks();
				}
				else _state = TextureStates::E_TEXTURE_STATE_DEFAULT;
			}
			break;
		}

		case TextureStates::E_TEXTURE_STATE_FADE_OUT:
		{
			if (SDL_GetTicks() > _lastTick + (_fadeDuration / 255))
			{
				if (GetAlpha() != 0)
				{
					SetAlpha(GetAlpha() - 1);
					_lastTick = SDL_GetTicks();
				}
				else _state = TextureStates::E_TEXTURE_STATE_DEFAULT;
			}
			break;
		}
	}
}

void Texture::FadeIn(int duration)
{
	_state = TextureStates::E_TEXTURE_STATE_FADE_IN;
	_fadeDuration = duration;
}

void Texture::FadeOut(int duration)
{
	_state = TextureStates::E_TEXTURE_STATE_FADE_OUT;
	_fadeDuration = duration;
}