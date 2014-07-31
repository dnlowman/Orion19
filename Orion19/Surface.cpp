#include "Surface.h"

Surface::Surface()
{
	_surface = nullptr;
}

Surface::~Surface()
{
	SDL_FreeSurface(_surface);
}

bool Surface::LoadImage(std::string file)
{
	_surface = IMG_Load(file.c_str());
	if(_surface == NULL) return false;
	else return true;
}

SDL_Surface* Surface::ReturnSurface() const
{
	return _surface;
}