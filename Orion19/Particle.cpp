#include "Particle.h"

Particle::Particle()
{
	_coordsSet = false;
}

Particle::~Particle()
{

}

void Particle::Logic()
{
	if (_coordsSet == false)
	{
		for (int i = 0; i < MAX_PARTICLES; ++i)
		{
			_particles[i].UpdateAsset("img\\blueparticle.png");
			_particles[i].SetX(_sprite.GetX() + rand() % 2);
			_particles[i].SetY(_sprite.GetY() + rand() % 2);
		}
		_coordsSet = true;
	}
	
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		_particles[i].SetX(_particles[i].GetX() - rand() % 5);
		//_particles[i].SetY(_particles[i].GetY() - rand() % 2);
	}
	_sprite.SetX(_sprite.GetX() - 1);
}

void Particle::Render()
{
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		_particles[i].Render();
	}
}

void Particle::OnEvent(SDL_Event evt)
{

}