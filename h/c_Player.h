#pragma once
#include "c_Flashlight.h"
#include "c_Entity_is_movable.h"

const int CHAR_VEL = 6;
const int MAXCOLD = 100;
const int COLDINTERVAL = 8000;

class c_Player : public c_Entity_is_movable
{
private:
	int xVel, yVel;
	int cold; int totalTicks;

	inline void handleCold(Uint32 dTicks);
	
	bool keysdown[4];
	bool playerMoving;

	int LEVEL_WIDTH, LEVEL_HEIGHT;

	c_cold_Meter coldMeter;
	c_Flashlight myFlashlight;

public:
	/*=====constructors=====*/
	c_Player(int x, int y);
	c_Player(const c_Player &c);
	c_Player& operator=(const c_Player &c);
	
	bool up, left, down, right;
	bool deadfriend_visited;

	void init( int x, int y );

	void setCamera();

	int getX();
	void setX(int x);
	int getY();
	void setY(int x);
	void setLevel(int w, int h);

	c_Flashlight* getFlashlight();
	
	bool nearFire;

	void handleInput();
	void logic( Uint32 deltaTicks );
	void render();

	~c_Player(void);
};

