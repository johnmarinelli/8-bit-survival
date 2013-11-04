#include "SDL.h"
#include "c_gameState.h"

//extern SDL_Surface* screen;

/*-CONSTANTS-*/
//extern const int SCREEN_WIDTH;
//extern const int SCREEN_HEIGHT;
//extern const int SCREEN_BPP;

//const short TILE_WIDTH = 40;
//const short TILE_HEIGHT = 40;
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP = 32;

//const int SPRITE_WIDTH = 32;
//const int SPRITE_HEIGHT = 32;

/*---GAME STATE STUFF---*/
//extern bool running;
void set_next_State( int state );
extern int stateID;
extern int nextState;

extern c_gameState *currentState;

/*---EVENT AND CAMERA---*/
extern SDL_Event event;
//extern SDL_Rect camera;