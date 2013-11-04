#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include <fstream>
#include "c_gamestate.h"
#include "c_Manor_2F.h"

class c_Manor : public c_gameState
{
private:
	c_Entity_manager entityManager;

	c_Player *manor_player;
	c_Zombie *manor_enemy;
	c_player_Copy *manor_copy;
	c_Piano *piano;

	c_Exit *exit;
	c_Door *upStairs;

	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_Tile **tileArray;

	void loadObjects();

public:
	c_Manor(gameStates prevState);

	void handleInput();
	void logic();
	void render();

	~c_Manor(void);
};

