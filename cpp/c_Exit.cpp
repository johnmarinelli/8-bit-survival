#include "c_Exit.h"

int c_Exit::exitCount = 5;

c_Exit::c_Exit(int x, int y)
{
	isLocked = false;
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = EXIT_WIDTH;
	collisionBox.h = EXIT_HEIGHT;

	entityGFX = load_image( "exit_SMALL.png" );

	eID = exitCount;
	exitCount++;
}

int c_Exit::getID()
{
	return eID;
}

void c_Exit::resetExits()
{
	exitCount = 5;
}

c_Exit::~c_Exit(void)
{
}
