#include "Player.h"

Player::Player()
{
	_alive = true;
	_tmpAngle = _velocity = 0.0;
	_sprite.UpdateAsset("img\\player.png");
	_lastShoot = 0;
	shoot.Load("sounds\\weaponfire.wav");
	_state = -1;
	_sprite.SetY(300);
	_sprite.SetOffsetWidth(35);
	_sprite.SetWidth(35);
}

Player::~Player()
{

}

void Player::Logic()
{
	int 
		width,
		height;

	double
		tmpX,
		tmpY;

	SDL_GetWindowSize(SDLFramework::ReturnWindow(), &width, &height);
	
	if (_sprite.GetX() >= width - _sprite.GetWidth())
	{
		_velocity = -_velocity;
		SetX(width - _sprite.GetWidth());
	}

	if(_sprite.GetX() <= 0)
	{
		_velocity = -_velocity;
		SetX(1.0);
	}
	
	if(_sprite.GetY() <= 0)
	{
		_velocity = -_velocity;
		SetY(1.0);
	}
	
	if (_sprite.GetY() >= height - _sprite.GetHeight())
	{
		_velocity = -_velocity;
		SetY(height - _sprite.GetHeight());
	}

	
	if(keys[SDLK_LEFT])
	{
		_sprite.SetAngle(Utils::AddToAngle((_state != (Uint8)E_PLAYER_STATES::E_STATE_SPEED) ? - 3 : - 5, _sprite.GetAngle()));
		_sprite.SetOffsetX(67);
	}
	
	if (keys[SDLK_RIGHT])
	{
		_sprite.SetAngle(Utils::AddToAngle((_state != (Uint8)E_PLAYER_STATES::E_STATE_SPEED) ? 3 : 5, _sprite.GetAngle()));
		_sprite.SetOffsetX(35);
	}

	if (!keys[SDLK_LEFT] && !keys[SDLK_RIGHT])
	{
		_sprite.SetOffsetX(0);
	}

	if(keys[SDLK_UP])
	{
		if (_velocity < 5.0) _velocity += (_state != (Uint8)E_PLAYER_STATES::E_STATE_SPEED) ? 1.0 : 3.0;
		_tmpAngle = _sprite.GetAngle();

		IGameObject* _cache = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_PARTICLE);
		_cache->ReturnSprite()->SetX(_sprite.GetX());
		_cache->ReturnSprite()->SetY(_sprite.GetY());

	}

	if(!keys[SDLK_UP])
	{
		if (_velocity > 0.0) _velocity -= 0.05;
		if (_velocity < 0.0) _velocity += 0.05;
	}

	if(keys[SDLK_SPACE])
	{
		if(SDL_GetTicks() > _lastShoot + 500 || _state == (Uint8)E_PLAYER_STATES::E_STATE_MULTI_SHOOT && SDL_GetTicks() > _lastShoot + 350)
		{
			IGameObject* bullet = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_BULLET);
			bullet->SetType((Uint8)BulletTypes::E_BULLET_TYPE_PLAYER);

			double _angle = _sprite.GetAngle();

			bullet->ReturnSprite()->SetAngle(_angle);

			tmpX = _sprite.GetX() + 10.0;
			tmpY = _sprite.GetY() + 10.0;
			Utils::GetXYInFrontOfPoint(tmpX, tmpY, _angle, 2);
			Utils::GetXYInFrontOfPoint(tmpX, tmpY, Utils::AddToAngle((_angle >= 0 && _angle <= 180) ? 0 : 180, _angle), 2);
			bullet->SetX(tmpX);
			bullet->SetY(tmpY);
			tmpX = 0;
			tmpY = 0;
			shoot.Play();
			_lastShoot = SDL_GetTicks();

			//

			if(_state == (Uint8)E_PLAYER_STATES::E_STATE_MULTI_SHOOT)
			{
				bullet = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_BULLET);
				bullet->SetType((Uint8)BulletTypes::E_BULLET_TYPE_PLAYER);

				double _angle = _sprite.GetAngle() + 45.0;

				bullet->ReturnSprite()->SetAngle(_angle);

				tmpX = _sprite.GetX() + 10;
				tmpY = _sprite.GetY() + 10;
				Utils::GetXYInFrontOfPoint(tmpX, tmpY, _angle, 10);
				Utils::GetXYInFrontOfPoint(tmpX, tmpY, Utils::AddToAngle(90, _angle), 2);
				bullet->SetX(tmpX);
				bullet->SetY(tmpY);
				shoot.Play();
				tmpX = 0;
				tmpY = 0;

				//

				bullet = GameManager::ReturnInstance()->AddGameObject(E_GAME_OBJECTS::E_GAME_OBJECT_BULLET);
				bullet->SetType((Uint8)BulletTypes::E_BULLET_TYPE_PLAYER);

				_angle = _sprite.GetAngle() - 45.0;

				bullet->ReturnSprite()->SetAngle(_angle);

				tmpX = _sprite.GetX() + 10;
				tmpY = _sprite.GetY() + 10;
				Utils::GetXYInFrontOfPoint(tmpX, tmpY, _angle, 10);
				Utils::GetXYInFrontOfPoint(tmpX, tmpY, Utils::AddToAngle(90, _angle), 2);
				bullet->SetX(tmpX);
				bullet->SetY(tmpY);
				shoot.Play();
				tmpX = 0;
				tmpY = 0;
			}
		}

		

	}

	if(keys[SDLK_BACKSPACE])
	{
		_sprite.SetX(0);
		_sprite.SetY(0);
		_velocity = 0.0;
	}

	if(_velocity > 0.0 || _velocity < 0.0)
	{
		tmpX = _sprite.GetX();
		tmpY = _sprite.GetY();
		Utils::GetXYInFrontOfPoint(tmpX, tmpY, _tmpAngle, _velocity);
		_sprite.SetX(tmpX);
		_sprite.SetY(tmpY);
	}
}

void Player::Render()
{
	_sprite.Render();
}

void Player::OnEvent(SDL_Event evt)
{
	Input::OnEvent(evt);
}