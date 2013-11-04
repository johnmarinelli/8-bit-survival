#pragma once
#include "c_Entity.h"
#include "timer.h"
#include "fx_checkCollision.h"
#include "c_imgFunctions.h"

const int HOLEBOX_X_OFFSET = 277;
const int HOLEBOX_Y_OFFSET = 195;
const int HOLEBOX_WIDTH = 92;
const int HOLEBOX_HEIGHT = 95;
const int CIRCLEBOX_RADIUS = 46;

class c_Flashlight : public c_Entity
{
private:
	int alpha;
	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;
	timer time;

public:
	c_Flashlight();
	c_Flashlight(int LEVELWIDTH, int LEVELHEIGHT);
	/*c_Flashlight(const c_Flashlight &c);
	c_Flashlight& operator=(const c_Flashlight &c);*/

	circle holeCircle;
	SDL_Rect holeBox;

	void setFlashlight(int p_X, int p_Y);
	void render(int p_X, int p_Y);

	~c_Flashlight(void);
};

