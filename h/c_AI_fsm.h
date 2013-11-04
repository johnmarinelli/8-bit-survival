#pragma once
#include "c_AIstate.h"

void changeAIState(c_AIstate* &thisAIstate);
void setnextAIState( int state );

extern int nextAIState;
extern int AIstateID;

const int ALERTBOX_RADIUS = 30;

class c_Attackmode : public c_AIstate
{
public:
	c_Attackmode(void);

	void AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
	int &xVel, int &yVel,
	bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity = AVG_VEL);

	~c_Attackmode(void);
};

class c_Gotomode : public c_AIstate
{
public:
	c_Gotomode(void);

	void AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
		int &xVel, int &yVel,
		bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity = AVG_VEL );
	
	~c_Gotomode(void);
};

class c_Chillmode : public c_AIstate
{
public:
	c_Chillmode(void);

	void AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
		int &xVel, int &yVel,
		bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity = AVG_VEL);

	~c_Chillmode(void);
};

class c_Deadmode : public c_AIstate
{
public:
	c_Deadmode();

	void AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
		int &xVel, int &yVel,
		bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity = AVG_VEL);

	~c_Deadmode();
};