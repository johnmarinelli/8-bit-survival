#pragma once
#include "c_Entity_manager.h"
#include "c_Tile.h"
#include "timer.h"
#include <fstream>
#include "c_gamestate.h"

const int SOUNDBOX_SIDE = 1;
class c_Store : public c_gameState
{
private:
	c_Entity_manager entityManager;

	c_Player *store_player;
	c_Zombie *store_enemy;
	c_Exit *exit;
	c_Stereo *store_stereo;

	bool initStereo();
	void update_stereo_Position();

	SDL_Rect extensionDoor;

	SDL_Rect sound1;
	SDL_Rect sound2;
	SDL_Rect sound3;
	SDL_Rect trueSound;
	SDL_Rect sound4;
	
	int TOTAL_TILES;
	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_Tile **tileArray;

	void loadObjects();

public:
	c_Store(gameStates prevState);

	void handleInput();
	void logic();
	void playSounds();
	void render();

	~c_Store(void);
};