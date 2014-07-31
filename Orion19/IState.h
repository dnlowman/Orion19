#ifndef I_STATE
#define I_STATE

#include "Input.h"

class IState : public Input
{
	public:
		virtual ~IState() {};
		virtual void OnLogic() = 0;
		virtual void OnRender() = 0;
};

#endif