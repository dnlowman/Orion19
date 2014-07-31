#include "Timer.h"

Timer::Timer(void)
{
	_frame = 0;
	_seconds = 0;
	_lastTicks = SDL_GetTicks();
	_text.UpdateText("TIMER START", 255, 255, 255, 255);
	_prefixText = "RESPAWNING IN ";
	_text.SetAngle(-90);
}


Timer::~Timer(void)
{
}

void Timer::Logic()
{
	if (SDL_GetTicks() > _lastTicks + _seconds)
	{
		switch (_type)
		{
			case (Uint8)E_TIMER_TYPE::E_TIMER_COUNT_DOWN:
			{
				--_frame;
				break;
			}

			case (Uint8)E_TIMER_TYPE::E_TIMER_COUNT_UP:
			{
				++_frame;
				break;
			}

			default:
			{
				++_frame;
				break;
			}
		}
		_lastTicks = SDL_GetTicks();
	}
}

void Timer::Render()
{
	_text.SetX(_x);
	_text.SetY(_y);
	std::ostringstream format;
	format << _prefixText << _frame;
	_text.UpdateText(format.str().c_str(), 255, 255, 255, 255);
	_text.Render();
}

void Timer::OnEvent(SDL_Event evt)
{

}
