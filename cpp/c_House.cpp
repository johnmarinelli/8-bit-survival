#include "c_House.h"

int c_House::houseNumber = 200;
SDL_Rect c_House::clip[12];

c_House::c_House( int x, int y, int part )
{
	entityGFX = load_image( "house2.png" );

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = HOUSE_PART_WIDTH;
	collisionBox.h = HOUSE_PART_HEIGHT;

	housePart = part;

	hID = houseNumber;
	houseNumber++;

	clip_House();
}

void c_House::clip_House()
{
	clip[ ROOF_NORTHWEST ].x = 0;
	clip[ ROOF_NORTHWEST ].y = 0;
	clip[ ROOF_NORTHWEST ].w = HOUSE_PART_WIDTH;
	clip[ ROOF_NORTHWEST ].h = HOUSE_PART_HEIGHT;

	clip[ ROOF_MIDDLELEFT ].x = HOUSE_PART_WIDTH;
	clip[ ROOF_MIDDLELEFT ].y = 0;
	clip[ ROOF_MIDDLELEFT ].w = HOUSE_PART_WIDTH;
	clip[ ROOF_MIDDLELEFT ].h = HOUSE_PART_HEIGHT;

	clip[ ROOF_MIDDLERIGHT ].x = HOUSE_PART_WIDTH * 2;
	clip[ ROOF_MIDDLERIGHT ].y = 0;
	clip[ ROOF_MIDDLERIGHT ].w = HOUSE_PART_WIDTH;
	clip[ ROOF_MIDDLERIGHT ].h = HOUSE_PART_HEIGHT;

	clip[ ROOF_NORTHEAST ].x = HOUSE_PART_WIDTH * 3;
	clip[ ROOF_NORTHEAST ].y = 0;
	clip[ ROOF_NORTHEAST ].w = HOUSE_PART_WIDTH;
	clip[ ROOF_NORTHEAST ].h = HOUSE_PART_HEIGHT;

	clip[ MIDDLE_WEST ].x = 0;
	clip[ MIDDLE_WEST ].y = HOUSE_PART_HEIGHT;
	clip[ MIDDLE_WEST ].w = HOUSE_PART_WIDTH;
	clip[ MIDDLE_WEST ].h = HOUSE_PART_HEIGHT;

	clip[ MIDDLE_MIDDLELEFT ].x = HOUSE_PART_WIDTH;
	clip[ MIDDLE_MIDDLELEFT ].y = HOUSE_PART_HEIGHT;
	clip[ MIDDLE_MIDDLELEFT ].w = HOUSE_PART_WIDTH;
	clip[ MIDDLE_MIDDLELEFT ].h = HOUSE_PART_HEIGHT;

	clip[ MIDDLE_MIDDLERIGHT ].x = HOUSE_PART_WIDTH * 2;
	clip[ MIDDLE_MIDDLERIGHT ].y = HOUSE_PART_HEIGHT;
	clip[ MIDDLE_MIDDLERIGHT ].w = HOUSE_PART_WIDTH;
	clip[ MIDDLE_MIDDLERIGHT ].h = HOUSE_PART_HEIGHT;

	clip[ MIDDLE_EAST ].x = HOUSE_PART_WIDTH * 3;
	clip[ MIDDLE_EAST ].y = HOUSE_PART_HEIGHT;
	clip[ MIDDLE_EAST ].w = HOUSE_PART_WIDTH;
	clip[ MIDDLE_EAST ].h = HOUSE_PART_HEIGHT;

	clip[ BOTTOM_SOUTHWEST ].x = 0;
	clip[ BOTTOM_SOUTHWEST ].y = HOUSE_PART_HEIGHT * 3;
	clip[ BOTTOM_SOUTHWEST ].w = HOUSE_PART_WIDTH;
	clip[ BOTTOM_SOUTHWEST ].h = HOUSE_PART_HEIGHT;

	clip[ BOTTOM_MIDDLELEFT ].x = HOUSE_PART_WIDTH;
	clip[ BOTTOM_MIDDLELEFT ].y = HOUSE_PART_HEIGHT * 3;
	clip[ BOTTOM_MIDDLELEFT ].w = HOUSE_PART_WIDTH;
	clip[ BOTTOM_MIDDLELEFT ].h = HOUSE_PART_HEIGHT;

	clip[ BOTTOM_MIDDLERIGHT ].x = HOUSE_PART_WIDTH * 2;
	clip[ BOTTOM_MIDDLERIGHT ].y = HOUSE_PART_HEIGHT * 3;
	clip[ BOTTOM_MIDDLERIGHT ].w = HOUSE_PART_WIDTH;
	clip[ BOTTOM_MIDDLERIGHT ].h = HOUSE_PART_HEIGHT;

	clip[ BOTTOM_SOUTHEAST ].x = HOUSE_PART_WIDTH * 3;
	clip[ BOTTOM_SOUTHEAST ].y = HOUSE_PART_HEIGHT * 3;
	clip[ BOTTOM_SOUTHEAST ].w = HOUSE_PART_WIDTH;
	clip[ BOTTOM_SOUTHEAST ].h = HOUSE_PART_HEIGHT;
}

void c_House::render()
{
	apply_surface( collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen, &clip[housePart]  );
}

int c_House::getID()
{
	return hID;
}

void c_House::resetCount()
{
	houseNumber = 200;
}

c_House::~c_House(void)
{
}
