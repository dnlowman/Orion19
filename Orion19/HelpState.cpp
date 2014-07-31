#include "HelpState.h"

HelpState::HelpState()
{
	_help.UpdateAsset("img\\help.png");
	_help.SetAngle(-90);
	_help.SetX(0);
	_help.SetY(0);
	_goBack.SetText("Back");
	_goBack.SetX(10);
	_goBack.SetY(10);
}

HelpState::~HelpState()
{

}

void HelpState::OnLogic()
{
	if(_goBack.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED)
	{
		StateManager::ReturnInstance()->SetState(E_STATE_MAIN_MENU);
	}
}

void HelpState::OnRender()
{
	_help.Render();
	_goBack.Render();
}

void HelpState::OnEvent(SDL_Event evt)
{
	_goBack.OnEvent(evt);
}