#include "c_Entity_is_movable.h"

std::vector<c_Tile*> c_Entity_is_movable::unWalkables;
std::vector<c_Entity*> c_Entity_is_movable::unCollidables;

c_Entity_is_movable::c_Entity_is_movable()
{
	onAnimate = NULL;

	collisionBox.x = 0;
	collisionBox.y = 0;
	collisionBox.w = 0;
	collisionBox.h = 0;
}

c_Entity_is_movable::c_Entity_is_movable(int x, int y) : c_Entity(x, y)
{
	onAnimate = NULL;

	collisionBox.w = 0;
	collisionBox.h = 0;
}

c_Entity_is_movable::c_Entity_is_movable(int x, int y, int w, int h) : c_Entity(x, y, w, h)
{
}

int c_Entity_is_movable::getX()
{
	return collisionBox.x;
}

int c_Entity_is_movable::getY()
{
	return collisionBox.y;
}

void c_Entity_is_movable::logic( Uint32 deltaTicks )
{
}

void c_Entity_is_movable::resetunWalkables()
{
	unWalkables.clear();
}

void c_Entity_is_movable::resetunCollidables()
{
	unCollidables.clear();
}

void c_Entity_is_movable::render()
{
	apply_surface(collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen, onAnimate->get_current_Frame());
}

c_Entity_is_movable::~c_Entity_is_movable(void)
{
}
