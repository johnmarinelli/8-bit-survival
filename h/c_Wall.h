#pragma once
#include "c_Entity.h"
#include "c_Entity_manager.h"

const int WALL_WIDTH = 40;
const int WALL_HEIGHT = 40;

class c_Wall : public c_Entity
{
private:
	static int wallCount;
	int w_ID;

public:
	c_Wall(int x, int y);

	void logic();
	int getID();
	static void resetCount();

	~c_Wall(void);
};

