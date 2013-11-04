#pragma once
#include "SDL.h"

const int CHAR_WIDTH = 32;
const int CHAR_HEIGHT = 32;
const int W_SHOVEL_WIDTH = 21;
const int W_SHOVEL_HEIGHT = 22;
const int FIRE_WIDTH = 36;
const int FIRE_HEIGHT = 44;

const int ANIMATE_FRAME_INTERVAL = 250;

enum entityType{
	ENTITY_ZOMBIE,
	ENTITY_PLAYER,
	WEAPON_SHOVEL,
	FIRE_TRASHCAN,
	FRIEND_SHIVERING,
	FRIEND_CRAZY,
};

class c_Animate
{
private:
	SDL_Rect* currentFrame;

	int frameNo;
	int animType;

	void set_clips( int eID );

	SDL_Rect clipsUp[2];
	SDL_Rect clipsDown[2];
	SDL_Rect clipsRight[2];
	SDL_Rect clipsLeft[2];
	SDL_Rect standing[2];
	SDL_Rect defaultFrame;

	SDL_Rect weapon_Down[2];

	SDL_Rect fire[3];

	SDL_Rect shivering[4];

	SDL_Rect crazy[4];

public:
	c_Animate( int eID );
	
	SDL_Rect* get_current_Frame();

	void animate( int &yVel, int &xVel, bool &playerMoving, bool &up, bool &down,
							bool &right, bool &left);

	void animateLogic( bool up, bool down, bool left, bool right,
							int xVel, int yVel );

	void static_Animation( bool nextFrame );

	void reset_current_Frame();

	~c_Animate(void);
};

