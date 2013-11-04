#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include <fstream>
#include "c_gamestate.h"

class c_House1 : public c_gameState
{
private:
	c_Entity_manager entityManager;

	c_Player *h1_player;
	c_Zombie *h1_enemy;
	c_Exit *exit;
	c_Note h1_note;
	c_dialog_System narrator;

	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_Tile **tileArray;

	bool loadObjects();

	static bool noteFound;

public:
	c_House1(void);

	void handleInput();
	void logic();
	void render();

	~c_House1(void);
};