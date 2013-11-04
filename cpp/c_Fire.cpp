#include "c_Fire.h"

int c_Fire::fireCount = 300;

c_Fire::c_Fire(int x, int y)
{
	entityGFX = load_image("big_fire.png");

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = FIRE_WIDTH;
	collisionBox.h = FIRE_HEIGHT;

	warmBox.x = collisionBox.x - (FIRE_RADIUS*2);
	warmBox.y = collisionBox.y - (FIRE_RADIUS*2);
	warmBox.w = FIRE_WIDTH + (FIRE_RADIUS * 4);
	warmBox.h = FIRE_HEIGHT + (FIRE_RADIUS * 4);

	onAnimate = new c_Animate(FIRE_TRASHCAN);
	tickCount = 0;

	fireID = fireCount;
	fireCount++;
}

void c_Fire::logic(Uint32 deltaTicks)
{
	tickCount += deltaTicks;

	if (tickCount > FIRE_FRAME_INTERVAL){
		nextFrame = true;
		tickCount = 0;
	}

	if ( check_collision(warmBox, player_ptr->getBox()) ){
		c_Entity_manager::getPlayer()->nearFire = true;
	}
	
	else
		c_Entity_manager::getPlayer()->nearFire = false;

	onAnimate->static_Animation(nextFrame);
	nextFrame = false;
}

int c_Fire::getID()
{
	return fireID;
}

void c_Fire::resetCount()
{
	fireCount = 300;
}

c_Fire::~c_Fire(void)
{
}
