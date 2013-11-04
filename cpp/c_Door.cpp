#include "c_Door.h"

int c_Door::doorCount = 0;

c_Door::c_Door(void)
{
	entityGFX = load_image("door.png");
	dID = doorCount;
	doorCount++;
}

int c_Door::getID()
{
	return dID;
}

void c_Door::resetCount()
{
	doorCount = 0;
}

c_Door::~c_Door(void)
{
};

c_Door_h1::c_Door_h1( int x, int y )
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = DOOR_WIDTH;
	collisionBox.h = DOOR_HEIGHT;
}

void c_Door_h1::logic()
{
}

c_Door_h1::~c_Door_h1(void)
{
}

c_Door_h2::c_Door_h2( int x, int y )
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = DOOR_WIDTH;
	collisionBox.h = DOOR_HEIGHT;
}

void c_Door_h2::logic()
{
}

c_Door_h2::~c_Door_h2(void)
{
}

c_Door_store::c_Door_store( int x, int y )
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = DOOR_WIDTH;
	collisionBox.h = DOOR_HEIGHT;
}

void c_Door_store::logic()
{
}

c_Door_store::~c_Door_store(void)
{
}

c_Door_manor::c_Door_manor( int x, int y )
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = DOOR_WIDTH;
	collisionBox.h = DOOR_HEIGHT;
}

void c_Door_manor::logic()
{
}

c_Door_manor::~c_Door_manor(void)
{
}

c_Upstairs_manor::c_Upstairs_manor(int x, int y)
{
	entityGFX = load_image( "stairs.png" );
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = STAIR_WIDTH;
	collisionBox.h = STAIR_HEIGHT;
}

void c_Upstairs_manor::logic()
{
}

c_Upstairs_manor::~c_Upstairs_manor(void)
{
}