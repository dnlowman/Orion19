#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"

enum class SpriteStates : Uint8
{
	E_STATE_DEFAULT,
	E_STATE_FADE_IN,
	E_STATE_FADE_OUT,
};

class Sprite : public Texture
{
	protected:
		SpriteStates _state;
		Uint32 _lastTick;
		int _fadeDuration;

	public:
		Sprite();
		~Sprite();
		Texture* ReturnTexture();
		void Update();
		void FadeIn(int time);
		void FadeOut(int time);
};

#endif