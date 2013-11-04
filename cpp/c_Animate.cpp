#include "c_Animate.h"

c_Animate::c_Animate( int eID )
{
	set_clips(eID);
	frameNo = 0;
	animType = eID;

	currentFrame = &defaultFrame;
}

void c_Animate::set_clips( int eID )
{
	if ( eID == ENTITY_ZOMBIE ){
	//default frame
	defaultFrame.x = 0;
	defaultFrame.y = 0;
	defaultFrame.w = CHAR_WIDTH;
	defaultFrame.h = CHAR_HEIGHT;

	//standing position, down
	standing[0].x = 0;
	standing[0].y = 0;
	standing[0].w = CHAR_WIDTH;
	standing[0].h = CHAR_HEIGHT;

	//down, right leg facing me up
	clipsDown[0].x = 0;
	clipsDown[0].y = CHAR_HEIGHT + 1;
	clipsDown[0].w = CHAR_WIDTH;
	clipsDown[0].h = CHAR_HEIGHT;

	//down, left leg facing me up
	clipsDown[1].x = 0;
	clipsDown[1].y = (CHAR_HEIGHT + 1) * 2;
	clipsDown[1].w = CHAR_WIDTH;
	clipsDown[1].h = CHAR_HEIGHT;

	//standing position, up
	standing[1].x = CHAR_WIDTH + 1;
	standing[1].y = 0;
	standing[1].w = CHAR_WIDTH;
	standing[1].h = CHAR_HEIGHT;

	//up, left leg facing me up
	clipsUp[0].x = CHAR_WIDTH + 1;
	clipsUp[0].y = CHAR_HEIGHT + 1;
	clipsUp[0].w = CHAR_WIDTH;
	clipsUp[0].h = CHAR_HEIGHT;

	//up, right leg facing me up
	clipsUp[1].x = CHAR_WIDTH + 1;
	clipsUp[1].y = (CHAR_HEIGHT + 1) * 2;
	clipsUp[1].w = CHAR_WIDTH;
	clipsUp[1].h = CHAR_HEIGHT;

	//left, standing
	clipsLeft[0].x = (CHAR_WIDTH + 1) * 2;
	clipsLeft[0].y = (CHAR_HEIGHT + 1);
	clipsLeft[0].w = CHAR_WIDTH;
	clipsLeft[0].h = CHAR_HEIGHT;

	//left, walking
	clipsLeft[1].x = (CHAR_WIDTH + 1) * 3;
	clipsLeft[1].y = (CHAR_HEIGHT + 1);
	clipsLeft[1].w = CHAR_WIDTH;
	clipsLeft[1].h = CHAR_HEIGHT;

	//right, standing
	clipsRight[0].x = (CHAR_WIDTH + 1) * 2;
	clipsRight[0].y = 0;
	clipsRight[0].w = CHAR_WIDTH;
	clipsRight[0].h = CHAR_HEIGHT;

	//right, walking
	clipsRight[1].x = (CHAR_WIDTH + 1) * 3;
	clipsRight[1].y = 0;
	clipsRight[1].w = CHAR_WIDTH;
	clipsRight[1].h = CHAR_HEIGHT;
	}

	/*==========PLAYER===============*/

	else if ( eID == ENTITY_PLAYER ){
	//default frame
	defaultFrame.x = 0;
	defaultFrame.y = 0;
	defaultFrame.w = CHAR_WIDTH;
	defaultFrame.h = CHAR_HEIGHT;

	//standing position, down
	standing[0].x = 0;
	standing[0].y = 0;
	standing[0].w = CHAR_WIDTH;
	standing[0].h = CHAR_HEIGHT;

	//down, right leg facing me up
	clipsDown[0].x = 0;
	clipsDown[0].y = CHAR_HEIGHT + 1;
	clipsDown[0].w = CHAR_WIDTH;
	clipsDown[0].h = CHAR_HEIGHT;

	//down, left leg facing me up
	clipsDown[1].x = 0;
	clipsDown[1].y = (CHAR_HEIGHT + 1) * 2;
	clipsDown[1].w = CHAR_WIDTH;
	clipsDown[1].h = CHAR_HEIGHT;

	//down, weapon sequence #2
	weapon_Down[0].x = 0;
	weapon_Down[0].y = (CHAR_HEIGHT + 1 ) * 4;
	weapon_Down[0].w = CHAR_WIDTH;
	weapon_Down[0].h = CHAR_HEIGHT;

	//standing position, up
	standing[1].x = CHAR_WIDTH + 1;
	standing[1].y = 0;
	standing[1].w = CHAR_WIDTH;
	standing[1].h = CHAR_HEIGHT;

	//up, left leg facing me up
	clipsUp[0].x = CHAR_WIDTH + 1;
	clipsUp[0].y = CHAR_HEIGHT + 1;
	clipsUp[0].w = CHAR_WIDTH;
	clipsUp[0].h = CHAR_HEIGHT;

	//up, right leg facing me up
	clipsUp[1].x = CHAR_WIDTH + 1;
	clipsUp[1].y = (CHAR_HEIGHT + 1) * 2;
	clipsUp[1].w = CHAR_WIDTH;
	clipsUp[1].h = CHAR_HEIGHT;

	//left, standing
	clipsLeft[0].x = (CHAR_WIDTH + 1) * 2;
	clipsLeft[0].y = (CHAR_HEIGHT + 1);
	clipsLeft[0].w = CHAR_WIDTH;
	clipsLeft[0].h = CHAR_HEIGHT;

	//left, walking
	clipsLeft[1].x = (CHAR_WIDTH + 1) * 3;
	clipsLeft[1].y = (CHAR_HEIGHT + 1);
	clipsLeft[1].w = CHAR_WIDTH;
	clipsLeft[1].h = CHAR_HEIGHT;

	//right, standing
	clipsRight[0].x = (CHAR_WIDTH + 1) * 2;
	clipsRight[0].y = 0;
	clipsRight[0].w = CHAR_WIDTH;
	clipsRight[0].h = CHAR_HEIGHT;

	//right, walking
	clipsRight[1].x = (CHAR_WIDTH + 1) * 3;
	clipsRight[1].y = 0;
	clipsRight[1].w = CHAR_WIDTH;
	clipsRight[1].h = CHAR_HEIGHT;
	}

	/*=========SHOVEL=============*/
	else if ( eID == WEAPON_SHOVEL )
	{
		//down, attack seq 1
		clipsDown[0].x = 0;
		clipsDown[0].y = W_SHOVEL_HEIGHT * 2;
		clipsDown[0].w = W_SHOVEL_WIDTH;
		clipsDown[0].h = W_SHOVEL_HEIGHT;

		//down, attack seq 2
		clipsDown[1].x = 0;
		clipsDown[1].y = W_SHOVEL_HEIGHT * 3;
		clipsDown[1].w = W_SHOVEL_WIDTH;
		clipsDown[1].h = W_SHOVEL_HEIGHT;
	}

	/*========TRASHCAN FIRE=======*/
	else if ( eID == FIRE_TRASHCAN ){
		//default frame
		defaultFrame.x = 0;
		defaultFrame.y = 0;
		defaultFrame.w = FIRE_WIDTH;
		defaultFrame.h = FIRE_HEIGHT;

		fire[0].x = 0;
		fire[0].y = 0;
		fire[0].w = FIRE_WIDTH;
		fire[0].h = FIRE_HEIGHT;

		fire[1].x = FIRE_WIDTH + 1;
		fire[1].y = 0;
		fire[1].w = FIRE_WIDTH;
		fire[1].h = FIRE_HEIGHT;

		fire[2].x = (FIRE_WIDTH + 1) * 2;
		fire[2].y = 0;
		fire[2].w = FIRE_WIDTH;
		fire[2].h = FIRE_HEIGHT;
	}

	/*======SHIVERING_FRIEND======*/

	else if( eID == FRIEND_SHIVERING ){
		defaultFrame.x = 0;
		defaultFrame.y = 0;
		defaultFrame.w = CHAR_WIDTH;
		defaultFrame.h = CHAR_HEIGHT;

		shivering[0].x = 0;
		shivering[0].y = 0;
		shivering[0].w = CHAR_WIDTH;
		shivering[0].h = CHAR_HEIGHT;

		shivering[1].x = CHAR_WIDTH + 1;
		shivering[1].y = 0;
		shivering[1].w = CHAR_WIDTH;
		shivering[1].h = CHAR_HEIGHT;

		shivering[2].x = (CHAR_WIDTH + 1) * 2;
		shivering[2].y = 0;
		shivering[2].w = CHAR_WIDTH;
		shivering[2].h = CHAR_HEIGHT;

		shivering[3].x = (CHAR_WIDTH + 1) * 3;
		shivering[3].y = 0;
		shivering[3].w = CHAR_WIDTH;
		shivering[3].h = CHAR_HEIGHT;

		//standing position, down
		standing[0].x = 0;
		standing[0].y = CHAR_HEIGHT;
		standing[0].w = CHAR_WIDTH;
		standing[0].h = CHAR_HEIGHT;

		//down, right leg facing me up
		clipsDown[0].x = 0;
		clipsDown[0].y = (CHAR_HEIGHT + 1) * 2;
		clipsDown[0].w = CHAR_WIDTH;
		clipsDown[0].h = CHAR_HEIGHT;

		//down, left leg facing me up
		clipsDown[1].x = 0;
		clipsDown[1].y = (CHAR_HEIGHT + 1) * 3;
		clipsDown[1].w = CHAR_WIDTH;
		clipsDown[1].h = CHAR_HEIGHT;

		//standing position, up
		standing[1].x = CHAR_WIDTH + 1;
		standing[1].y = CHAR_HEIGHT;
		standing[1].w = CHAR_WIDTH;
		standing[1].h = CHAR_HEIGHT;

		//up, left leg facing me up
		clipsUp[0].x = CHAR_WIDTH + 1;
		clipsUp[0].y = (CHAR_HEIGHT + 1) * 2;
		clipsUp[0].w = CHAR_WIDTH;
		clipsUp[0].h = CHAR_HEIGHT;

		//up, right leg facing me up
		clipsUp[1].x = CHAR_WIDTH + 1;
		clipsUp[1].y = (CHAR_HEIGHT + 1) * 3;
		clipsUp[1].w = CHAR_WIDTH;
		clipsUp[1].h = CHAR_HEIGHT;

		//left, standing
		clipsLeft[0].x = (CHAR_WIDTH + 1) * 2;
		clipsLeft[0].y = (CHAR_HEIGHT + 1) * 2;
		clipsLeft[0].w = CHAR_WIDTH;
		clipsLeft[0].h = CHAR_HEIGHT;

		//left, walking
		clipsLeft[1].x = (CHAR_WIDTH + 1) * 3;
		clipsLeft[1].y = (CHAR_HEIGHT + 1) * 2;
		clipsLeft[1].w = CHAR_WIDTH;
		clipsLeft[1].h = CHAR_HEIGHT;

		//right, standing
		clipsRight[0].x = (CHAR_WIDTH + 1) * 2;
		clipsRight[0].y = (CHAR_HEIGHT + 1);
		clipsRight[0].w = CHAR_WIDTH;
		clipsRight[0].h = CHAR_HEIGHT;

		//right, walking
		clipsRight[1].x = (CHAR_WIDTH + 1) * 3;
		clipsRight[1].y = (CHAR_HEIGHT + 1);
		clipsRight[1].w = CHAR_WIDTH;
		clipsRight[1].h = CHAR_HEIGHT;
	}

	else if ( eID == FRIEND_CRAZY ){
		defaultFrame.x = 0;
		defaultFrame.y = 0;
		defaultFrame.w = CHAR_WIDTH;
		defaultFrame.h = CHAR_HEIGHT;

		crazy[0].x = 0;
		crazy[0].y = 0;
		crazy[0].w = CHAR_WIDTH;
		crazy[0].h = CHAR_HEIGHT;

		crazy[1].x = CHAR_WIDTH + 1;
		crazy[1].y = 0;
		crazy[1].w = CHAR_WIDTH;
		crazy[1].h = CHAR_HEIGHT;

		crazy[2].x = (CHAR_WIDTH + 1) * 2;
		crazy[2].y = 0;
		crazy[2].w = CHAR_WIDTH;
		crazy[2].h = CHAR_HEIGHT;

		crazy[3].x = (CHAR_WIDTH + 1) * 3;
		crazy[3].y = 0;
		crazy[3].w = CHAR_WIDTH;
		crazy[3].h = CHAR_HEIGHT;
	}
}

void c_Animate::animate( int &yVel, int &xVel,
						bool &playerMoving, bool &up, bool &down, bool &right, bool &left)
{
	if ( yVel > 0 && playerMoving == true ){
		down = true;
		up = false;
		left = false;
		right = false;
		currentFrame = &clipsDown[frameNo];
		frameNo++;
	}

	else if ( yVel < 0 && playerMoving == true){
		up = true;
		down = false;
		left = false;
		right = false;
		currentFrame = &clipsUp[frameNo];
		frameNo++;
	}

	else if ( xVel > 0 && playerMoving == true ){
		right = true;
		left = false;
		up = false;
		down = false;
		currentFrame = &clipsRight[frameNo];
		frameNo++;
	}

	else if ( xVel < 0 && playerMoving == true ){
		left = true;
		right = false;
		up = false;
		down = false;
		currentFrame = &clipsLeft[frameNo];
		frameNo++;
	}

	/*if ( xVel != 0 && yVel != 0 ){
		left = false;
		right = false;
		up = false;
		down = false;
		currentFrame = &standing[0];
	}*/

	if ( xVel == 0 && yVel == 0 && down == true && playerMoving == false ){
		currentFrame = &standing[0];
	}

	else if ( xVel == 0 && yVel == 0 && up == true && playerMoving == false ){
		currentFrame = &standing[1];
	}

	else if ( xVel == 0 && yVel == 0 && left == true && playerMoving == false ){
		currentFrame = &clipsLeft[0];
	}
	
	else if ( xVel == 0 && yVel == 0 && right == true && playerMoving == false ){
		currentFrame = &clipsRight[0];
	}

	if ( frameNo >= 2 ){
		frameNo= 0; 
	}
}

void c_Animate::animateLogic( bool up, bool down, bool left, bool right,
						int xVel, int yVel)
{
	if (down){
		currentFrame = &clipsDown[frameNo];
		frameNo++;
	}
	else if (up){
		currentFrame = &clipsUp[frameNo];
		frameNo++;
	}
	else if (left){
		currentFrame = &clipsLeft[frameNo];
		frameNo++;
	}	
	else if (right){
		currentFrame = &clipsRight[frameNo];
		frameNo++;
	}

	if ( xVel == 0 && yVel == 0 && down == true ){
		currentFrame = &standing[0];
	}
	else if ( xVel == 0 && yVel == 0 && up == true ){
		currentFrame = &standing[1];
	}
	else if ( xVel == 0 && yVel == 0 && left == true ){
		currentFrame = &clipsLeft[0];
	}	
	else if ( xVel == 0 && yVel == 0 && right == true ){
		currentFrame = &clipsRight[0];
	}

	if ( frameNo >= 2 ){
		frameNo = 0;
	}
}

void c_Animate::static_Animation( bool nextFrame )
{
	if ( nextFrame == true )
	{
		if ( animType == FIRE_TRASHCAN ){
			currentFrame = &fire[frameNo];

			frameNo++;

			if ( frameNo > 2 ){frameNo = 0;}
		}

		else if ( animType == FRIEND_SHIVERING || animType == FRIEND_CRAZY ){
			currentFrame = &shivering[frameNo];
			
			frameNo++;

			if ( frameNo > 3 ){frameNo = 0;}
		}
	}
}

SDL_Rect* c_Animate::get_current_Frame()
{
	return currentFrame;
}

void c_Animate::reset_current_Frame()
{
	currentFrame = &defaultFrame;
}

c_Animate::~c_Animate(void)
{
}
