#include "GameOverState.h"

GameOverState::GameOverState()
{
	_gameOverText.UpdateText("Game Over", 255, 255, 255, 255);
	_gameOverText.SetX(400 - (_gameOverText.GetWidth() / 2));
	_gameOverText.SetY(300);
	_gameOverText.SetAngle(-90);

	_playAgain.SetText("Play Again");
	_playAgain.SetX(400 - (_playAgain.ReturnSprite()->GetWidth() / 2));
	_playAgain.SetY(380);
	_quit.SetText("Quit");
	_quit.SetX(400 - (_quit.ReturnSprite()->GetWidth() / 2));
	_quit.SetY(420);

	std::ostringstream os;
	os << "Score: " << GameManager::ReturnInstance()->GetScore();
	_score.UpdateText(os.str().c_str(), 255, 255, 255, 255);
	_score.SetX(400 - (_score.GetWidth() / 2));
	_score.SetY(340);
	_score.SetAngle(-90);

	delete GameManager::ReturnInstance();
}

GameOverState::~GameOverState()
{
}

void GameOverState::OnLogic()
{
	if(_playAgain.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED) StateManager::ReturnInstance()->SetState(E_STATE_DEFAULT);
	if(_quit.GetState() == E_BUTTON_STATES::E_BUTTON_CLICKED) StateManager::ReturnInstance()->SetState(E_STATE_MAIN_MENU);
}

void GameOverState::OnRender()
{
	_gameOverText.Render();
	_playAgain.Render();
	_quit.Render();
	_score.Render();
}

void GameOverState::OnEvent(SDL_Event evt)
{
	_playAgain.OnEvent(evt);
	_quit.OnEvent(evt);
}