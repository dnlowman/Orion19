#ifndef TEXTURE_H
#define TEXTURE_H

/* STL Includes */
#include <string>

/* SDL Includes */
#include <SDL.h>
#include <SDL_ttf.h>

/* Local Includes */
#include "Surface.h"
#include "SDLFramework.h"
#include "AssetManager.h"

enum class TextureStates : Uint8
{
	E_TEXTURE_STATE_DEFAULT,
	E_TEXTURE_STATE_FADE_IN,
	E_TEXTURE_STATE_FADE_OUT,
};

class Texture
{
protected:
	SDL_Texture*	_texture;
	SDL_Rect		_position;
	SDL_Rect		_offset;
	double			_angle;
	Uint8			_alpha;
	TextureStates   _state;
	Uint32			_lastTick;
	int				_fadeDuration;
	double			_x;
	double			_y;

public:
	Texture();
	~Texture();
	bool UpdateSurface(std::string file);
	bool UpdateAsset(std::string file);
	bool UpdateText(std::string text, Uint8 alpha, Uint8 red, Uint8 green, Uint8 blue);
	void SetX(double x);
	void SetY(double y);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetOffsetX(int x);
	void SetOffsetY(int y);
	void SetOffsetWidth(int width);
	void SetOffsetHeight(int height);
	void SetAngle(double angle);
	void IncrementAngle();
	void DecrementAngle();
	void SetAlpha(Uint8 alpha);
	double GetX() const;
	double GetY() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetOffsetX() const;
	int GetOffsetY() const;
	int GetOffsetWidth() const;
	int GetOffsetHeight() const;
	double GetAngle() const;
	Uint8 GetAlpha() const;
	void Render();
	void Logic();
	void FadeIn(int duration);
	void FadeOut(int duration);
	TextureStates ReturnState() const { return _state; };
	SDL_Texture* ReturnSDLTexture() const { return _texture; };
	SDL_Rect*    ReturnSDLRect() { return &_position; };
};

#endif