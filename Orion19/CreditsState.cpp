/*
	Class:
		SDLFramework

	Description:
		This is the credits state, essentially just decrements an images Y to give a
		credits effect.
*/

#include "CreditsState.h"

CreditsState::CreditsState()
{	
	_credits.UpdateAsset("img\\credits.png");
	_credits.SetAngle(-90);
	_credits.SetY(10);
	_credits.SetX(20);
	_backButton.SetText("Back");
	_backButton.SetX(10);
	_backButton.SetY(10);
}

CreditsState::~CreditsState()
{

}

void CreditsState::OnLogic()
{
	_credits.SetY((_credits.GetY() - 0.5));
	
	if (_backButton.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED)
	{
		StateManager::ReturnInstance()->SetState(E_STATE_MAIN_MENU);
	}
}

void CreditsState::OnRender()
{
	_credits.Render();
	_backButton.Render();
}

void CreditsState::OnEvent(SDL_Event evt)
{
	_backButton.OnEvent(evt);
}