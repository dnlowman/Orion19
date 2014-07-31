#include "IGameObject.h"

IGameObject::IGameObject()
{
	_x = _y = 0.0;
}

IGameObject::~IGameObject()
{

}

void IGameObject::SetX(double value)
{
	_x = value;
	_sprite.SetX(value);
}

void IGameObject::SetY(double value)
{
	_y = value;
	_sprite.SetY(value);
}

double IGameObject::GetX() const
{
	return _x;
}

double IGameObject::GetY() const
{
	return _y;
}