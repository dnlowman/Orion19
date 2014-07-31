#include "Planet.h"

Planet::Planet()
{
	int random = std::rand() % 3;
	std::string file;

	switch (random)
	{
		case 0:
		{
			file = "img\\planet1.png";
			break;
		}

		case 1:
		{
			file = "img\\planet2.png";
			break;
		}

		case 2:
		{
			file = "img\\planet3.png";
			break;
		}

		case 3:
		{
			file = "img\\planet4.png";
			break;
		}
	}
	_img.UpdateAsset(file);
	_img.SetX(900);
	_img.SetY(std::rand() % 550);
}

Planet::~Planet()
{

}

void Planet::Logic()
{
	_img.SetX(_img.GetX() - 1.3);
}

void Planet::Render()
{
	_img.Render();
}

void Planet::OnEvent(SDL_Event evt)
{

}