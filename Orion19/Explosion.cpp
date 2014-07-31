#include "Explosion.h"

Explosion::Explosion()
{
	_sprite.UpdateAsset("img\\explosions.png");
	_sprite.SetAngle(-90);
	_sprite.SetHeight(90);
	_sprite.SetWidth(90);
	_sprite.SetOffsetHeight(90);
	_sprite.SetOffsetWidth(90);
	_sprite.SetOffsetX(0);
	_lastTick = SDL_GetTicks();
	_sound.Load("sounds\\explosion.wav");
	_sound.Play();
	_alive = true;
}


Explosion::~Explosion()
{
}

void Explosion::Logic()
{
	if (SDL_GetTicks() > _lastTick + 100)
	{
		if (_sprite.GetOffsetY() >= 300) _alive = false;
		
		if (_sprite.GetOffsetX() >= 300)
		{
			_sprite.SetOffsetY(_sprite.GetOffsetY() + 100);
			_sprite.SetOffsetX(0);
		}
		_sprite.SetOffsetX(_sprite.GetOffsetX() + 100);
		_lastTick = SDL_GetTicks();
	}
}

void Explosion::Render()
{
	_sprite.Render();
}

void Explosion::OnEvent(SDL_Event evt)
{

}