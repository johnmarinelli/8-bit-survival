#pragma once

const int DOOR_Y_BUFFER = 20;
const int DOOR_X_BUFFER = 5;
const int CHARACTER_Y_BUFFER = 5;

enum gameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_OVERWORLD,
	STATE_HOUSE1,
	STATE_HOUSE2,
	STATE_STORE,
	STATE_STORE_EXTENSION,
	STATE_MANOR,
	STATE_MANOR2F,
	STATE_GAMEWIN_WITH_FRIEND,
	STATE_GAMEWIN_NO_FRIEND,
	STATE_GAMELOSE_ENEMY_TOUCHED,
	STATE_GAMELOSE_FROSTBITE,
	STATE_EXIT,
};

extern bool running;

class c_gameState
{
public:
	virtual void handleInput() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;

	virtual ~c_gameState(void);
};