#pragma once
#include "c_Entity_manager.h"
#include <vector>

const int FIRE_FRAME_INTERVAL = 300;
const int FIRE_RADIUS = 10;

class c_Fire : public c_Entity_is_movable
{
private:
	bool nextFrame;
	int tickCount;

	static int fireCount;
	int fireID;

public:
	c_Fire(int x, int y);
	
	void logic(Uint32 dTicks);

	int getID();
	SDL_Rect warmBox;

	static void resetCount();

	~c_Fire(void);
};