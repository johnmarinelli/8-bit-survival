#include "c_Wall.h"

int c_Wall::wallCount = 100;

c_Wall::c_Wall(int x, int y)
{
	entityGFX = load_image( "wall.png" );

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = WALL_WIDTH;
	collisionBox.h = WALL_HEIGHT;

	w_ID = wallCount;
	wallCount++;
}

int c_Wall::getID()
{
	return w_ID;
}

void c_Wall::logic()
{
}

void c_Wall::resetCount()
{
	wallCount = 100;
}
c_Wall::~c_Wall(void)
{
}
