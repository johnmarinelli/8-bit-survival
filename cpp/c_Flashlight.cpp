#include "c_Flashlight.h"

c_Flashlight::c_Flashlight()
{
}

c_Flashlight::c_Flashlight(int levWidth, int levHeight)
{
	LEVEL_WIDTH = levWidth;
	LEVEL_HEIGHT = levHeight;
	timer time = timer();

	collisionBox.x = 0;
	collisionBox.y = 0;
	collisionBox.w = SCREEN_WIDTH;
	collisionBox.h = SCREEN_HEIGHT;

	holeBox.x = collisionBox.x + HOLEBOX_X_OFFSET;
	holeBox.y = collisionBox.y + HOLEBOX_Y_OFFSET;
	holeBox.h = HOLEBOX_HEIGHT;
	holeBox.w = HOLEBOX_WIDTH;

	holeCircle.x = holeBox.x + (HOLEBOX_WIDTH/2);
	holeCircle.y = holeBox.y + (HOLEBOX_HEIGHT/2);
	holeCircle.r = CIRCLEBOX_RADIUS;

	alpha = 240;
	entityGFX = load_image("alphaLayerWITHHOLE.png");
	SDL_SetAlpha(entityGFX, SDL_SRCALPHA, alpha);
}

void c_Flashlight::setFlashlight(int p_X, int p_Y )
{
	if ( p_X - 25 < 0 ){
		collisionBox.x = 25 - p_X;
	}
	else if ( p_X + 65 > LEVEL_WIDTH ){
		collisionBox.x =( LEVEL_WIDTH - (p_X + 65) );
	}
	else{
		collisionBox.x = 0;
	}

	if ( p_Y - 27 < 0 ){
		collisionBox.y = 27 - p_Y;
	}
	else if ( p_Y + 65 > LEVEL_HEIGHT ){
		collisionBox.y =( LEVEL_HEIGHT - (p_Y + 65) );
	}
	else{
		collisionBox.y = 0;
	}

	holeBox.x = collisionBox.x + HOLEBOX_X_OFFSET;
	holeBox.y = collisionBox.y + HOLEBOX_Y_OFFSET;

	holeCircle.x = holeBox.x + (HOLEBOX_WIDTH/2);
	holeCircle.y = holeBox.y + (HOLEBOX_HEIGHT/2);
}

void c_Flashlight::render(int p_X, int p_Y)
{
	apply_surface( collisionBox.x, collisionBox.y, entityGFX, screen );
}

c_Flashlight::~c_Flashlight(void)
{
}
