#ifndef BULLET_H
#define BULLET_H

#include "IGameObject.h"
#include "Sprite.h"
#include "Utils.h"

enum class BulletTypes : Uint8
{
	E_BULLET_TYPE_PLAYER,
	E_BULLET_TYPE_ENEMY,
};

class Bullet : public IGameObject
{
	protected:

	public:
		Bullet();
		~Bullet();
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
		void SetType(Uint8 type);
};

#endif