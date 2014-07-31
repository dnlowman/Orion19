#include "Enemy.h"

Enemy::Enemy(E_ENEMY_TYPES type)
{
	srand((unsigned int)time(NULL));
	SetAlive(true);
	
	_type = (Uint8)type;
	switch(type)
	{
		case E_ENEMY_TYPES::E_TYPE_RED:
		{
			_sprite.UpdateAsset("img\\enemy.png");
			_lastShoot = SDL_GetTicks();
			_velocity = 0.0;
			break;
		}

		case E_ENEMY_TYPES::E_TYPE_DRONE:
		{
			_sprite.UpdateAsset("img\\drone.png");
			_lastShoot = SDL_GetTicks();
			_velocity = 0.0;
			break;
		}
		
		case E_ENEMY_TYPES::E_TYPE_MISSILE:
		{
			_sprite.UpdateAsset("img\\missileEnemy.png");
			_lastShoot = SDL_GetTicks();
			_velocity = 0.0;
			break;
		}
	}

	_sprite.SetX(900);
	_sprite.SetAngle(-180);
	_sprite.SetY((float)(rand() % 600 + 1));
	_shoot.Load("phaser.wav");
}

Enemy::~Enemy()
{

}

void Enemy::Logic()
{
	double tmpX, tmpY;
	
	switch(_type)
	{
		case (Uint8)E_ENEMY_TYPES::E_TYPE_RED:
		{										 
			if(SDL_GetTicks() > _lastShoot + 2500)
			{
		
				IGameObject* bullet = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_BULLET);
				bullet->SetType((Uint8)BulletTypes::E_BULLET_TYPE_ENEMY);

				double _angle = _sprite.GetAngle();

				bullet->ReturnSprite()->SetAngle(_angle);

				tmpX = _sprite.GetX() + 10;
				tmpY = _sprite.GetY() + 10;
				Utils::GetXYInFrontOfPoint(tmpX, tmpY, _angle, 10);
				Utils::GetXYInFrontOfPoint(tmpX, tmpY, Utils::AddToAngle(90, _angle), 2);
				bullet->ReturnSprite()->SetX(tmpX);
				bullet->ReturnSprite()->SetY(tmpY);
				tmpX = 0;
				tmpY = 0;
				_lastShoot = SDL_GetTicks();
				_shoot.Play();
			}
		}
	}
}

void Enemy::Render()
{
	_sprite.Render();
}

void Enemy::OnEvent(SDL_Event evt)
{

}

double Enemy::GetVelocity()
{
	return _velocity;
}