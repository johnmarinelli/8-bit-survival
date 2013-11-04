#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include "c_Flashlight.h"
#include <fstream>
#include "c_gameState.h"
#include "c_Manor_2F.h"
#include <vector>

class c_Intro : public c_gameState
{
private:
	SDL_Surface* background;

public:
	c_Intro(void);

	void handleInput();
	void logic();
	void render();

	~c_Intro(void);
};

class c_stageOne : public c_gameState
{
private:
	c_Entity_manager entityManager;
	c_Player *player;
	c_Zombie *enemy;
	c_dialog_System narrator;

	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_Tile **tileArray;

	void loadObjects();

	SDL_Rect exit;

public:
	c_stageOne(void);
	c_stageOne( gameStates prevState );

	void handleInput();
	void logic();
	void render();

	~c_stageOne(void);
};
