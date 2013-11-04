#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include <fstream>
#include "c_gamestate.h"

class c_Store_Extension : public c_gameState
{
private:
	c_Entity_manager entityManager;

	c_Player *store_player;

	SDL_Rect exit;

	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_Tile **tileArray;

	void loadObjects();

public:
	c_Store_Extension();

	void handleInput();
	void logic();
	void render();

	~c_Store_Extension();
};

