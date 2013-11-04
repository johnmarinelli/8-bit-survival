#pragma once
#include "c_Entity.h"
#include "I_Audio_system.h"
#include "c_Tile.h"
#include "c_Animate.h"
#include "c_dialog_System.h"
#include <vector>

class c_Entity_is_movable : public c_Entity
{
public:
	c_Entity_is_movable(void);
	c_Entity_is_movable(int x, int y);
	c_Entity_is_movable(int x, int y, int w, int h);
	/*c_Entity_is_movable(const c_Entity_is_movable &c);
	c_Entity_is_movable& operator=(const c_Entity_is_movable &c);*/

	int xVel, yVel;

	c_Animate* onAnimate;
	static std::vector<c_Tile*> unWalkables;
	static std::vector<c_Entity*> unCollidables;

	static void resetunWalkables();
	static void resetunCollidables();

	bool up, left, down, right;

	int getX();
	int getY();

	virtual void logic( Uint32 deltaTicks );
	virtual void render();

	virtual ~c_Entity_is_movable(void);
};


