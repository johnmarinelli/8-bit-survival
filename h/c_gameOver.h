#pragma once
#include "SDL.h"
#include "timer.h"
#include "c_dialog_System.h"
#include "c_Globals.h"
#include "c_gamestate.h"
#include "c_imgFunctions.h"

const int FADEOUT_INTERVAL = 100;

enum OVERTYPE{
	OVERTYPE_WIN_WITH_FRIEND,
	OVERTYPE_WIN_NO_FRIEND,
	OVERTYPE_LOSE_ENEMY_TOUCHED,
	OVERTYPE_LOSE_FROSTBITE,
};

class c_gameOver : public c_gameState
{
private:
	SDL_Rect blackscreen;
	timer time;
	int alpha;
	SDL_Surface *blank;
	c_dialog_System message;

public:
	c_gameOver(OVERTYPE ending);

	void handleInput();
	void logic();
	void render();
	void fadeIn();

	~c_gameOver(void);
};

