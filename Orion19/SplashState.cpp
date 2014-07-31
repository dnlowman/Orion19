#include "SplashState.h"

SplashState::SplashState()
{
	/* PRELOAD BEGIN */

	AssetManager::ReturnInstance()->PreloadImage("img\\bg.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\blueparticle.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\bullet.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\codeheads.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\comlogo.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\credits.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\drone.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\enemyBullet.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\explosions.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\help.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\hpPickup.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\logo.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\logo360.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\missileEnemy.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\multiPickup.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\optionsButton.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\orion.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\player.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\quitButton.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\shieldPickup.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\speedPickup.png");
	AssetManager::ReturnInstance()->PreloadImage("img\\startButton.png");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\dss.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\explosion.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\weaponfire.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\wil.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\explosion.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\ex4.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\phaser.wav");
	AssetManager::ReturnInstance()->PreloadSound("sounds\\pickup.wav");

	/* PRELOAD END */
	
	splashState = E_SPLASH_STATE_CH_INTRO;
	gameLogo.UpdateAsset("img\\logo.png");
	gameLogo.SetAngle(-90);
	codeheads.UpdateAsset("img\\codeheads.png");
	codeheads.SetAngle(-90);
	comlogo.UpdateAsset("img\\comlogo.png");
	comlogo.SetAngle(-90);

	int width, height;
	SDL_GetWindowSize(SDLFramework::ReturnWindow(), &width, &height);

	gameLogo.SetX((float)((width / 2) - (gameLogo.GetWidth() / 2)));
	gameLogo.SetY((float)(height / 2 - (gameLogo.GetHeight() / 2)));
	codeheads.SetX((float)(width / 2 - (codeheads.GetWidth() / 2)));
	codeheads.SetY((float)(height / 2 - (codeheads.GetHeight() / 2)));
	comlogo.SetX((float)(width / 2 - (comlogo.GetWidth() / 2)));
	comlogo.SetY((float)(height / 2 - (comlogo.GetHeight() / 2)));

	gameLogo.SetAlpha(0);
	codeheads.SetAlpha(0);
	comlogo.SetAlpha(0);
	gameLogo.FadeIn(200);
	codeheads.FadeIn(200);
	comlogo.FadeIn(200);

	snd.Load("wil.wav");
	snd.Play();
}

SplashState::~SplashState()
{
	snd.Stop();
}

void SplashState::OnLogic()
{
	switch(splashState)
	{
		case E_SPLASH_STATE_CH_INTRO:
		{
			if(codeheads.ReturnState() != TextureStates::E_TEXTURE_STATE_DEFAULT) codeheads.Logic();
			else
			{
				codeheads.FadeOut(200);
				splashState = E_SPLASH_STATE_CH_OUTRO;
			}
			break;
		}

		case E_SPLASH_STATE_CH_OUTRO:
		{
			if (codeheads.ReturnState() != TextureStates::E_TEXTURE_STATE_DEFAULT) codeheads.Logic();
			else
			{
				splashState = E_SPLASH_STATE_COM_INTRO;
			}
			break;
		}

		case E_SPLASH_STATE_COM_INTRO:
		{
			if (comlogo.ReturnState() != TextureStates::E_TEXTURE_STATE_DEFAULT) comlogo.Logic();
			else
			{
				comlogo.FadeOut(200);
				splashState = E_SPLASH_STATE_COM_OUTRO;
			}
			break;
		}

		case E_SPLASH_STATE_COM_OUTRO:
		{
			if (comlogo.ReturnState() != TextureStates::E_TEXTURE_STATE_DEFAULT) comlogo.Logic();
			else
			{
				splashState = E_SPLASH_STATE_LOGO_INTRO;
			}
			break;
		}

		case E_SPLASH_STATE_LOGO_INTRO:
		{
			if (gameLogo.ReturnState() != TextureStates::E_TEXTURE_STATE_DEFAULT) gameLogo.Logic();
			else
			{
				gameLogo.FadeOut(200);
				splashState = E_SPLASH_STATE_LOGO_OUTRO;
			}
			break;
		}

		case E_SPLASH_STATE_LOGO_OUTRO:
		{
			if (gameLogo.ReturnState() != TextureStates::E_TEXTURE_STATE_DEFAULT) gameLogo.Logic();
			else
			{
				StateManager::ReturnInstance()->SetState(E_STATE_MAIN_MENU);
			}
			break;
		}
	}
}

void SplashState::OnRender()
{
	gameLogo.Render();
	codeheads.Render();
	comlogo.Render();
}

void SplashState::OnEvent(SDL_Event evt)
{
	Input::OnEvent(evt);
	//GameManager OnEvent...
	if (keys[SDLK_SPACE])
	{
		StateManager::ReturnInstance()->SetState(E_STATE_MAIN_MENU);
	}
}
