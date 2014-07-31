#include "Pickup.h"

Pickup::Pickup(E_PICKUP_TYPES type)
{
	_sprite.SetAngle(-90);
	_type = (Uint8)type;
	switch(type)
	{
		case E_PICKUP_TYPES::E_TYPE_HEALTH:
		{
			_sprite.UpdateAsset("img\\hpPickup.png");
			break;
		}

		case E_PICKUP_TYPES::E_TYPE_MULTI_SHOOT:
		{
			_sprite.UpdateAsset("img\\multiPickup.png");
			break;
		}

		case E_PICKUP_TYPES::E_TYPE_SHIELD:
		{
			_sprite.UpdateAsset("img\\shieldPickup.png");
			break;
		}

		case E_PICKUP_TYPES::E_TYPE_SPEED:
		{
			 _sprite.UpdateAsset("img\\speedPickup.png");
			break;
		}

	}
	_sprite.SetX(900);
	_sprite.SetY((float)(rand() % 500 + 100));
}

Pickup::~Pickup(void)
{
}

void Pickup::Logic()
{
	_sprite.SetX((float)(_sprite.GetX() - 1.5));
}

void Pickup::Render()
{
	_sprite.Render();
}

void Pickup::OnEvent(SDL_Event evt)
{

}