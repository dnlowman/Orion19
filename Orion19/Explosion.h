#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "IGameObject.h"
#include "Sound.h"

class Explosion : public IGameObject
{
	protected:
		Uint32 _lastTick;
		Sound  _sound;

	public:
		Explosion();
		~Explosion();
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
};

#endif