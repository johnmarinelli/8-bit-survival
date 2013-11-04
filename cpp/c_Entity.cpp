#include "c_Entity.h"

c_Entity *player_ptr;
int c_Entity::decorCount = 1000;

c_Entity::c_Entity(void)
{
	collisionBox.x = 0;
	collisionBox.y = 0;
	collisionBox.w = 0;
	collisionBox.h = 0;

	entityGFX = NULL;
}

c_Entity::c_Entity(int x, int y)
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = 0;
	collisionBox.h = 0;

	entityGFX = NULL;
}

c_Entity::c_Entity(int x, int y, int width, int height, const char *fileName)
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = width;
	collisionBox.h = height;

	if(fileName != NULL){
	entityGFX = load_image(fileName);
	}
}

SDL_Rect c_Entity::getBox()
{
	return collisionBox;
}

void c_Entity::render()
{
	apply_surface(collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen);
}

void c_Entity::logic()
{
}

int c_Entity::getX()
{
	return collisionBox.x;
}

int c_Entity::getY()
{
	return collisionBox.y;
}

void c_Entity::resetdecorCount()
{
	decorCount = 1000;
}

c_Entity::~c_Entity(void)
{
}