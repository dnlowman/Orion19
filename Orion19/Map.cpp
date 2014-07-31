#include "Map.h"

Map::Map()
{
	tile.UpdateAsset("img\\bg.png");
}

Map::~Map()
{
}

void Map::Render()
{
	SDL_Rect _offset = *tile.ReturnSDLRect();
	SDL_RenderCopy(SDLFramework::ReturnRenderer(), tile.ReturnSDLTexture(), NULL, &_offset);
	_offset.x += tile.GetWidth();
	SDL_RenderCopy(SDLFramework::ReturnRenderer(), tile.ReturnSDLTexture(), NULL, &_offset);
}

void Map::Logic()
{
	if (tile.ReturnSDLRect()->x < 0 - tile.GetWidth()) tile.ReturnSDLRect()->x = 0;
	tile.ReturnSDLRect()->x -= 1;
	tile.SetX(tile.GetX() - 1);
}

void Map::OnEvent(SDL_Event evt)
{

}