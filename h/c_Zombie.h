#pragma once
#include "c_Entity_is_movable.h"
#include "c_AI_fsm.h"
#include "fx_checkCollision.h"
#include "timer.h"

const int ZOMBIE_WIDTH = 26;
const int ZOMBIE_HEIGHT = 26;
const int INCREASED_VEL = 100;

class c_Zombie : public c_Entity_is_movable
{
private:
	int xVel, yVel;
	bool up, left, down, right, alerted;

	c_Stereo noise;
	c_AIstate *currentAIstate;

public:
	bool isSpawned;

	/*=====ctors=====*/
	c_Zombie();
	c_Zombie(int x, int y, int vel = AVG_VEL);
	c_Zombie(const c_Zombie &c);
	c_Zombie& operator=(const c_Zombie &c);

	void init( int x, int y );

	int LEVEL_WIDTH, LEVEL_HEIGHT;
	int zombieVel;

	void logic( Uint32 deltaTicks );
	void move( Uint32 deltaTicks );

	~c_Zombie(void);
};

