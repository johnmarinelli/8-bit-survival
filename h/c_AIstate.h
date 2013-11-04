#pragma once
#include "SDL.h"

enum AIstates{
	AI_NULL,
	CHILL,
	GO_TO,
	ATTACK,
	DEAD,
};

const int AVG_VEL = 60;

class c_AIstate
{
public:
	c_AIstate(void);

	virtual void AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
	int &xVel, int &yVel,
	bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity = AVG_VEL ) = 0;

	virtual ~c_AIstate(void);
};

