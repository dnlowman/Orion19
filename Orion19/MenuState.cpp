#include "MenuState.h"

MenuState::MenuState()
{
	_bg.ReturnSprite()->UpdateAsset("img\\bg.png");
	_logo.UpdateAsset("img\\logo.png");
	_logo.SetX(20);
	_logo.SetY(20);
	_logo.SetAngle(-90);
	_playButton.ReturnSprite()->SetX(50);
	_playButton.ReturnSprite()->SetY(200);
	_playButton.SetText("Play");
	//_playButton.SetCallback();
	_creditsButton.ReturnSprite()->SetX(50);
	_creditsButton.ReturnSprite()->SetY(400);
	_creditsButton.SetText("Credits");
	_quitButton.ReturnSprite()->SetX(50);
	_quitButton.ReturnSprite()->SetY(500);
	_quitButton.SetText("Quit");
	_helpButton.ReturnSprite()->SetX(50);
	_helpButton.ReturnSprite()->SetY(300);
	_helpButton.SetText("Help");
	_snd.Load("sounds\\wil.wav");
	_snd.Play(1);
}

MenuState::~MenuState()
{
	_snd.Stop();
}

void MenuState::OnLogic()
{
	_bg.Logic();

	if (_playButton.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED) StateManager::ReturnInstance()->SetState(E_STATE_DEFAULT);
	else if (_creditsButton.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED) StateManager::ReturnInstance()->SetState(E_STATE_CREDITS);
	else if (_quitButton.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED) SDLFramework::Quit();
	else if (_helpButton.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED) StateManager::ReturnInstance()->SetState(E_STATE_HELP);
}

void MenuState::OnRender()
{
	_bg.Render();
	_logo.Render();
	_playButton.Render();
	_creditsButton.Render();
	_quitButton.Render();
	_helpButton.Render();
}

void MenuState::OnEvent(SDL_Event evt)
{
	_playButton.OnEvent(evt);
	_creditsButton.OnEvent(evt);
	_quitButton.OnEvent(evt);
	_helpButton.OnEvent(evt);
}