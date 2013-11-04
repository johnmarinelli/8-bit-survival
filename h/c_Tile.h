#pragma once
#include "SDL.h"
#include "c_Globals.h"
#include "fx_checkCollision.h"
#include "c_imgFunctions.h"
#include <fstream>

const short TILE_WIDTH = 40;
const short TILE_HEIGHT = 40;

const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;
const int TILE_CLIFF_FORWARD = 12;

class c_Tile
{
private:
	SDL_Rect box;

	static SDL_Rect clips[13];

	static SDL_Surface* tileSheet;

	int type;

	bool isWalkable;

public:
	c_Tile(void);

	c_Tile( int x, int y, int tileType,bool walkable );

	static c_Tile** loadTiles( const std::string fileName, int &TOTAL_TILES, int &LEVEL_WIDTH, int &LEVEL_HEIGHT );
	static void setClips();

	void setWalkable( bool walkable );
	void show();

	int getType();

	SDL_Rect getBox();
	int getX();
	int getY();

	~c_Tile(void);
};

