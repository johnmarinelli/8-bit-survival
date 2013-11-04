#include "c_Shovel.h"

int c_Shovel::w_ID = 0;

c_Shovel::c_Shovel(int x, int y)
{
	entityGFX = load_image("shovelTile.png");

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = 12;
	collisionBox.h = 20;

	this->ID_number = w_ID;

	w_ID++;
}

void c_Shovel::logic()
{
	if ( check_collision(collisionBox, c_Entity_manager::getPlayer()->getBox()) == true )
	{
		/*c_Entity_manager::getPlayer()->setWeapon( SHOVEL );*/
		/*c_Entity_manager::remove( ID_number );*/
	}
}

int c_Shovel::getID()
{
	return ID_number;
}

c_Shovel::~c_Shovel(void)
{
}
