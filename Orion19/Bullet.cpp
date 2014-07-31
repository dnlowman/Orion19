/*
	Class:
		Bullet

	Description:
		This class is designed for handling bullets within the game, there's two types
		player and enemy, having the two allows me to distinguish when to check for
		collision.
*/

#include "Bullet.h"

Bullet::Bullet()
{
	_alive = true;
	_sprite.UpdateAsset("img\\bullet.png");
	_velocity = 5.0;
}

Bullet::~Bullet()
{
}

void Bullet::Logic()
{
	_velocity += (double)0.1;
	
	double tmpX, tmpY;
	
	if(_velocity > 0.0 || _velocity < 0.0)
	{
		tmpX = _sprite.GetX();
		tmpY = _sprite.GetY();
		Utils::GetXYInFrontOfPoint(tmpX, tmpY, (double)_sprite.GetAngle(), _velocity);
		_sprite.SetX(tmpX);
		_sprite.SetY(tmpY);
	}
}

void Bullet::Render()
{
	_sprite.Render();
}

void Bullet::OnEvent(SDL_Event evt)
{

}

void Bullet::SetType(Uint8 type)
{
	_type = type;
	switch ((BulletTypes)type)
	{
		case BulletTypes::E_BULLET_TYPE_ENEMY:
		{
			_sprite.UpdateAsset("img\\enemyBullet.png");
			break;
		}

		case BulletTypes::E_BULLET_TYPE_PLAYER:
		{
			_sprite.UpdateAsset("img\\bullet.png");
			break;
		}
	}
}