#pragma once
#include "SDL.h"
#include "c_imgFunctions.h"
#include "c_Globals.h"

const int TREE = 2;
const int ENTITY_CRATE_FAT = 29;
const int ENTITY_CRATE_TALL = 30;
const int ENTITY_CHAIR = 32;
const int ENTITY_HOUSEPLANT = 33;
const int ENTITY_TABLE_LONG = 34;
const int ENTITY_BOOKSHELF = 35;
const int ENTITY_STORE_SHELF_1 = 36;
const int ENTITY_STORE_CHECKOUT = 37;
const int ENTITY_STORE_SHELF_2 = 38;
const int ENTITY_STORE_SHELF_3 = 39;

const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 32;
const int TREE_WIDTH = 75;
const int TREE_HEIGHT = 54;
const int CRATE_FAT_WIDTH = 25;
const int CRATE_FAT_HEIGHT = 20;
const int CRATE_TALL_WIDTH = 20;
const int CRATE_TALL_HEIGHT = 30;
const int CHAIR_WIDTH = 15;
const int CHAIR_HEIGHT = 15;
const int HOUSEPLANT_WIDTH = 15;
const int HOUSEPLANT_HEIGHT = 35;
const int TABLE_LONG_WIDTH = 50;
const int TABLE_LONG_HEIGHT = 23;
const int BOOKSHELF_WIDTH = 20;
const int BOOKSHELF_HEIGHT = 50;
const int STORE_SHELF_HEIGHT = 50;
const int STORE_SHELF_WIDTH =  75;
const int STORE_CHECKOUT_HEIGHT = 45;
const int STORE_CHECKOUT_WIDTH = 50;
const int STORE_SIGN_WIDTH = 127;
const int STORE_SIGN_HEIGHT = 27;

const int HIDDEN_DOOR_HEIGHT = 25;

class c_Entity
{
public:
	static int decorCount;

	SDL_Surface* entityGFX;
	SDL_Rect collisionBox;
	
	c_Entity(void);
	c_Entity( int x, int y );
	c_Entity( int x, int y, int width, int height, const char *fileName = NULL);

	virtual void logic();
	virtual void render();

	SDL_Rect getBox();
	int getX();
	int getY();

	static void resetdecorCount();
	virtual ~c_Entity(void);
};

extern c_Entity *player_ptr;