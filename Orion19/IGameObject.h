#ifndef I_GAME_OBJECT
#define I_GAME_OBJECT

#include <SDL.h>

#include "Input.h"
#include "Sprite.h"

class IGameObject : public Input
{
	protected:
		Sprite _sprite;
		Uint8  _type;
		bool  _alive;
		double _velocity;
		Uint8 _state;
		//
		double _x;
		double _y;

	public:
		/* Methods */
		IGameObject();
		virtual ~IGameObject();
		virtual void Logic() = 0;
		virtual void Render() = 0;
		virtual void OnEvent(SDL_Event evt) = 0;
		virtual void SetX(double value);
		virtual void SetY(double value);
		virtual double GetX() const;
		virtual double GetY() const;
		virtual void OnPickupPickup(IGameObject* pickup) {};
		//
		Sprite* ReturnSprite() { return &_sprite; };
		virtual void SetType(Uint8 type) { _type = type; };
		Uint8 ReturnType() { return _type; };
		void SetAlive(bool alive) { _alive = alive; };
		bool GetAlive() const { return _alive; };
		void SetVelocity(double _value) { _velocity = _value; };
		double ReturnVelocity() const { return _velocity; };
		void SetState(Uint8 value) { _state = value; };
		Uint8 ReturnState() { return _state; };
};

#endif