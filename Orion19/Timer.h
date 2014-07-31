#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <sstream>

#include "IGameObject.h"
#include "Sprite.h"

enum class E_TIMER_TYPE : Uint8
{
	E_TIMER_COUNT_UP,
	E_TIMER_COUNT_DOWN,
};

class Timer : public IGameObject
{
	protected:
		int _frame;
		Uint32 _lastTicks;
		Uint32 _seconds;
		std::string _prefixText;
		Sprite _text;

	public:
		Timer(void);
		~Timer(void);
		void Logic();
		void Render();
		void OnEvent(SDL_Event evt);
		int GetFrame() const { return _frame; };
		void SetFrame(int value)  { _frame = value; };
		void SetSeconds(Uint32 value) { _seconds = value; };
		Uint32 GetSeconds() const { return _seconds; };
		
};

#endif