#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include <fstream>
#include "c_gameState.h"
//
//const int DOOR_Y_BUFFER = 20;
//const int DOOR_X_BUFFER = 5;
//const int CHARACTER_Y_BUFFER = 5;

class c_House2 : public c_gameState
{
private:
	c_Entity_manager entityManager;

	c_Player *h2_player;
	c_Zombie *h2_enemy;
	c_Exit *exit;

	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_Tile **tileArray;

	void loadObjects();

public:
	c_House2(void);

	void handleInput();
	void logic();
	void render();

	~c_House2(void);
};