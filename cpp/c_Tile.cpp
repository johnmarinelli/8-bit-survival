#include "c_Tile.h"
#include "c_Entity_is_movable.h"

SDL_Surface* c_Tile::tileSheet = NULL;
SDL_Rect c_Tile::clips[13];

c_Tile::c_Tile(void)
{
}

c_Tile::c_Tile( int x, int y, int tileType, bool walkable )
{
	box.x = x;
	box.y = y;
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;

	type = tileType;
	tileSheet = load_image( "tiles40x40.png" );

	this->isWalkable = walkable;

	setClips();
}

c_Tile** c_Tile::loadTiles( std::string fileName, int &TOTAL_TILES, int &LEVEL_WIDTH, int &LEVEL_HEIGHT )
{
	int x = 0;
	int y = 0;

	std::ifstream map(fileName);

	if ( map == NULL )
	{
		SDL_Quit();
	}

	map >> TOTAL_TILES; map.ignore();

	map >> LEVEL_WIDTH; map >> LEVEL_HEIGHT; map.ignore();

	c_Tile** tileArray = new c_Tile*[TOTAL_TILES];

	/*for ( short i = 0; i < TOTAL_TILES; i++ )*/
	for (c_Tile **ptr = tileArray; ptr < (tileArray + TOTAL_TILES); ptr++)
	{
		short tileType = -1;
		int i = 0;

		map >> tileType;

		if ( tileType >= TILE_RED && tileType <= TILE_CLIFF_FORWARD )
		{
			if ( tileType >= TILE_CENTER && tileType <= TILE_CLIFF_FORWARD )
			{
				*ptr = new c_Tile(x, y, tileType, false);
				c_Entity_is_movable::unWalkables.push_back(*ptr);
			}
			else
				*ptr = new c_Tile(x, y, tileType, true);
		}

		else
			SDL_Quit();

		x += TILE_WIDTH;

		if ( x >= LEVEL_WIDTH )
		{
			x = 0;
			y += TILE_HEIGHT;
		}

		i++;
	}

	return tileArray;
	map.close();
}

void c_Tile::setClips()
{
	clips[ TILE_RED ].x = 0;
    clips[ TILE_RED ].y = 0;
    clips[ TILE_RED ].w = TILE_WIDTH;
    clips[ TILE_RED ].h = TILE_HEIGHT;
    
    clips[ TILE_GREEN ].x = 0;
    clips[ TILE_GREEN ].y = 40;
    clips[ TILE_GREEN ].w = TILE_WIDTH;
    clips[ TILE_GREEN ].h = TILE_HEIGHT;
    
    clips[ TILE_BLUE ].x = 0;
    clips[ TILE_BLUE ].y = 80;
    clips[ TILE_BLUE ].w = TILE_WIDTH;
    clips[ TILE_BLUE ].h = TILE_HEIGHT;

    clips[ TILE_TOPLEFT ].x = 40;
    clips[ TILE_TOPLEFT ].y = 0;
    clips[ TILE_TOPLEFT ].w = TILE_WIDTH;
    clips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

    clips[ TILE_LEFT ].x = 40;
    clips[ TILE_LEFT ].y = 40;
    clips[ TILE_LEFT ].w = TILE_WIDTH;
    clips[ TILE_LEFT ].h = TILE_HEIGHT;
        
    clips[ TILE_BOTTOMLEFT ].x = 40;
    clips[ TILE_BOTTOMLEFT ].y = 80;
    clips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
    clips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;
    
    clips[ TILE_TOP ].x = 80;
    clips[ TILE_TOP ].y = 0;
    clips[ TILE_TOP ].w = TILE_WIDTH;
    clips[ TILE_TOP ].h = TILE_HEIGHT;
    
    clips[ TILE_CENTER ].x = 80;
    clips[ TILE_CENTER ].y = 40;
    clips[ TILE_CENTER ].w = TILE_WIDTH;
    clips[ TILE_CENTER ].h = TILE_HEIGHT;
    
    clips[ TILE_BOTTOM ].x = 80;
    clips[ TILE_BOTTOM ].y = 80;
    clips[ TILE_BOTTOM ].w = TILE_WIDTH;
    clips[ TILE_BOTTOM ].h = TILE_HEIGHT;
    
    clips[ TILE_TOPRIGHT ].x = 120;
    clips[ TILE_TOPRIGHT ].y = 0;
    clips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
    clips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;
    
    clips[ TILE_RIGHT ].x = 120;
    clips[ TILE_RIGHT ].y = 40;
    clips[ TILE_RIGHT ].w = TILE_WIDTH;
    clips[ TILE_RIGHT ].h = TILE_HEIGHT;
    
    clips[ TILE_BOTTOMRIGHT ].x = 120;
    clips[ TILE_BOTTOMRIGHT ].y = 80;
    clips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
    clips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;

	clips[ TILE_CLIFF_FORWARD ].x = 0;
	clips[ TILE_CLIFF_FORWARD ].y = 120;
	clips[ TILE_CLIFF_FORWARD ].w = TILE_WIDTH;
	clips[ TILE_CLIFF_FORWARD ].h = TILE_HEIGHT;
}

void c_Tile::setWalkable( bool walkable )
{
	isWalkable = walkable;
}

int c_Tile::getX()
{
	return box.x;
}

int c_Tile::getY()
{
	return box.y;
}

void c_Tile::show()
{
	if (check_collision(camera, box) == true)
	{
		apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[type]);
	}
}

SDL_Rect c_Tile::getBox()
{
	return box;
}

int c_Tile::getType()
{
	return type;
}

c_Tile::~c_Tile(void)
{
}
