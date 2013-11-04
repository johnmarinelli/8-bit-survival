#include "c_Globals.h"
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP = 32;

//SDL_Surface* screen = NULL;

SDL_Event event;

//SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

/*-CONSTANTS-*/
//const short TILE_WIDTH = 40;
//const short TILE_HEIGHT = 40;
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP = 32;
//const int SPRITE_WIDTH = 32;
//const int SPRITE_HEIGHT = 32;
//const int DOOR_Y_BUFFER = 20;
//const int DOOR_X_BUFFER = 5;
//const int CHARACTER_Y_BUFFER = 5;

/*---GAME STATE STUFF---*/
//extern bool running = true;

void set_next_State(int state)
{
	if ( state != STATE_EXIT ){
		nextState = state;
	}

	else
		nextState = STATE_EXIT;
}

extern int stateID = STATE_OVERWORLD;
extern int nextState = NULL;

extern c_gameState *currentState = NULL;