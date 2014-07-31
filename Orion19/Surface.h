#ifndef SURFACE_H
#define SURFACE_H

/* STL Includes */
#include <string>

/* SDL Includes */
#include <SDL.h>
#include <SDL_image.h>

class Surface
{
	protected:
		/* Variables */
		SDL_Surface* _surface;

	public:
		/* Methods */
		Surface();
		~Surface();
		bool LoadImage(std::string file);
		SDL_Surface* ReturnSurface() const;
};

#endif