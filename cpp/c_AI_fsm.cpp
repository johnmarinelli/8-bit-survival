#include "c_AI_fsm.h"
#include "fx_checkCollision.h"

void changeAIState(c_AIstate* &thisAIstate)
{
	if ( nextAIState != AI_NULL )
	{
		delete thisAIstate;
		thisAIstate = NULL;

		switch (nextAIState)
		{
		case CHILL:
			thisAIstate = new c_Chillmode(); break;
		case GO_TO: 
			thisAIstate = new c_Gotomode(); break;
		case ATTACK:
			thisAIstate = new c_Attackmode(); break;
		case DEAD:
			thisAIstate = new c_Deadmode(); break;

		default:
			thisAIstate = new c_Chillmode(); break;
		}

		AIstateID = nextAIState;
		nextAIState = AI_NULL;
	}
}

void setnextAIState( int state )
{
	nextAIState = state;
}

extern int nextAIState = 0;
extern int AIstateID = 0;

/*============CHILL MODE==============*/
c_Chillmode::c_Chillmode()
{
}

void c_Chillmode::AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
		int &xVel, int &yVel,
		bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity)
{
	int width = collisionBox.w;
	int height = collisionBox.h;

	SDL_Rect alertBox;

	alertBox.x = collisionBox.x - ALERTBOX_RADIUS;
	alertBox.y = collisionBox.y - ALERTBOX_RADIUS;
	alertBox.w = width + (ALERTBOX_RADIUS*2);
	alertBox.h = height + (ALERTBOX_RADIUS*2);

	if ( check_collision( alertBox, p_Box ) == true )
	{
		alerted = true;
	}

	else
		alerted = false;
}

c_Chillmode::~c_Chillmode()
{
}

/*============ATTACK MODE==============*/
c_Attackmode::c_Attackmode()
{
}

void c_Attackmode::AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
	int &xVel, int &yVel,
	bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity)
{
	collisionBox.x = 0;
	collisionBox.y = 0;
}

c_Attackmode::~c_Attackmode()
{
}

/*============GOTO MODE==============*/
c_Gotomode::c_Gotomode()
{
}

void c_Gotomode::AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
	int &xVel, int &yVel,
	bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity )
{
	SDL_Rect AI_box;

	AI_box.x = collisionBox.x;
	AI_box.y = collisionBox.y;
	AI_box.w = 35;
	AI_box.h = 35;

	p_Box.h = 30;

	if ( AI_box.x + AI_box.w < p_Box.x )/*to the left of player*/
	{
		xVel = velocity;
		right = true;
		left = false;
		down = false;
		up = false;
	}

	else if ( AI_box.x > p_Box.x + AI_box.w )/*to the right of player*/
	{
		xVel = -velocity;
		left = true;
		right = false;
		down = false;
		up = false;
	}

	if ( AI_box.y + (AI_box.h/2) < p_Box.y ) /*above player*/
	{
		yVel = velocity;
		down = true;
		up = false;
		left = false;
		right = false;
	}

	else if ( AI_box.y > p_Box.y + (AI_box.h/2) ) /*below player*/
	{
		yVel = -velocity;
		up = true;
		down = false;
		left = false;
		right = false;
	}

	if ( check_collision( AI_box, p_Box ) )
	{
		xVel -= xVel;
		yVel -= yVel;
	}


}

c_Gotomode::~c_Gotomode()
{
}

/*============DEAD MODE==============*/
c_Deadmode::c_Deadmode()
{
}

void c_Deadmode::AIlogic( SDL_Rect &collisionBox, SDL_Rect p_Box,
	int &xVel, int &yVel,
	bool &up, bool &down, bool &left, bool &right, bool &alerted, int velocity)
{
	up = false;
	down = false;
	left = false;
	right = false;
	alerted = false;

	xVel = 0; 
	yVel = 0;
}

c_Deadmode::~c_Deadmode()
{
}