#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include <fstream>
#include "c_gamestate.h"

class c_Manor_2F : public c_gameState
{
private:
	c_Entity_manager entityManager;

	c_Player *manor_player;
	c_Zombie *manor_2F_enemy;
	c_Exit *exit;

	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;
	
	c_Tile **tileArray;
	void loadObjects();

public:
	c_Manor_2F(void);
	
	static bool isVisited;
	static bool friendDead;

	void handleInput();
	void logic();
	void render();

	~c_Manor_2F(void);
};


