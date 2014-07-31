#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>

#include "IGameObject.h"
#include "Sprite.h"

#define MAX_PARTICLES 5

class Particle : public IGameObject
{
	protected:
		Sprite _particles[MAX_PARTICLES];
		bool   _coordsSet;

	public:
		Particle();
		~Particle();
	    void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
};

#endif