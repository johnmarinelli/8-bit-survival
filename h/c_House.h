#pragma once
#include "c_entity.h"

const int HOUSE_PART_WIDTH = 40;
const int HOUSE_PART_HEIGHT = 40;

enum PARTS{
	ROOF_NORTHWEST,
	ROOF_MIDDLELEFT,
	ROOF_MIDDLERIGHT,
	ROOF_NORTHEAST,
	MIDDLE_WEST,
	MIDDLE_MIDDLELEFT,
	MIDDLE_MIDDLERIGHT,
	MIDDLE_EAST,
	BOTTOM_SOUTHWEST,
	BOTTOM_MIDDLELEFT,
	BOTTOM_MIDDLERIGHT,
	BOTTOM_SOUTHEAST,
};

class c_House : public c_Entity
{
private:
	int housePart;
	static void clip_House();
	static SDL_Rect clip[12];

	static int houseNumber;
	int hID;

public:
	c_House(int x, int y, int part);

	void render();
	int getID();
	static void resetCount();

	~c_House(void);
};

