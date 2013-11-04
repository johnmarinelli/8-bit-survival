#include "c_Player.h"
#include "fx_checkCollision.h"
#include "c_imgFunctions.h"
#include <vector>

c_Player::c_Player(int x, int y) : c_Entity_is_movable(x, y, CHAR_WIDTH, CHAR_HEIGHT)
{
	up = false; down = false; left = false; right = false; playerMoving = false;
	deadfriend_visited = false;

	keysdown[0] = false;
	keysdown[1] = false;
	keysdown[2] = false;
	keysdown[3] = false;
	nearFire = false;
	
	yVel = xVel = 0;

	cold = 0;
	totalTicks = 0;
	coldMeter = c_cold_Meter();
	
	myFlashlight = c_Flashlight(1280, 960);

	entityGFX = load_image( "villagerSpritesheet.png" );
	onAnimate = new c_Animate( ENTITY_PLAYER );
}

c_Player::c_Player(const c_Player &c)
{
	collisionBox = c.collisionBox;
	coldMeter = c.coldMeter;
	myFlashlight = c_Flashlight(1280, 960);
	entityGFX = load_image( "villagerSpritesheet.png" );
	onAnimate = new c_Animate( ENTITY_PLAYER );
}

c_Player& c_Player::operator=(const c_Player &c)
{
	up = false; down = false; left = false; right = false; playerMoving = false;
	deadfriend_visited = c.deadfriend_visited;

	keysdown[0] = false;
	keysdown[1] = false;
	keysdown[2] = false;
	keysdown[3] = false;
	nearFire = false;
	
	yVel = xVel = 0;

	collisionBox = c.collisionBox;
	coldMeter = c.coldMeter;
	myFlashlight = c.myFlashlight;
	entityGFX = c.entityGFX;
	onAnimate = c.onAnimate;

	return *this;
}

void c_Player::init( int x, int y )
{
	up = false; down = false; left = false; right = false; playerMoving = false;

	this->collisionBox.x = x;
	this->collisionBox.y = y;
	this->collisionBox.w = CHAR_WIDTH;
	this->collisionBox.h = CHAR_HEIGHT;

	onAnimate->reset_current_Frame();

	collisionBox.x -= xVel;
	collisionBox.y -= yVel;
}

void c_Player::setCamera()
{
	camera.x = (collisionBox.x + CHAR_WIDTH/2) - SCREEN_WIDTH / 2;
	camera.y = (collisionBox.y + CHAR_HEIGHT/2) - SCREEN_HEIGHT / 2;
}

int c_Player::getX()
{
	return collisionBox.x;
}

void c_Player::setX(int x)
{
	collisionBox.x = x;
}

int c_Player::getY()
{
	return collisionBox.y;
}

void c_Player::setY(int y)
{
	collisionBox.y = y;
}

void c_Player::setLevel(int w, int h)
{
	LEVEL_WIDTH = w;
	LEVEL_HEIGHT = h;

	myFlashlight = c_Flashlight(LEVEL_WIDTH, LEVEL_HEIGHT);
}

void c_Player::handleInput()
{
	if ( event.type == SDL_KEYDOWN )
	{
		if( event.key.keysym.sym == SDLK_DOWN ){
		yVel += CHAR_VEL;
		keysdown[0] = true;
		}
		else if ( event.key.keysym.sym == SDLK_UP ){
		yVel -= CHAR_VEL;
		keysdown[1] = true;
		}
		else if ( event.key.keysym.sym == SDLK_RIGHT ){
		xVel += CHAR_VEL;
		keysdown[2] = true;
		}
		else if ( event.key.keysym.sym == SDLK_LEFT){
		xVel -= CHAR_VEL;
		keysdown[3] = true;
		}
		playerMoving = true;
	}

	if ( event.type == SDL_KEYUP )
	{
		if( event.key.keysym.sym == SDLK_DOWN ){
		yVel -= CHAR_VEL; 
		keysdown[0] = false;
		}
		else if ( event.key.keysym.sym == SDLK_UP ){
		yVel += CHAR_VEL;
		keysdown[1] = false;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT){
		xVel -= CHAR_VEL;
		keysdown[2] = false;
		}
		else if ( event.key.keysym.sym == SDLK_LEFT){
		xVel += CHAR_VEL; 
		keysdown[3] = false;
		}

		playerMoving = false;
	}
}

inline void c_Player::handleCold(Uint32 deltaTicks)
{
	totalTicks += deltaTicks;

	if (totalTicks > COLDINTERVAL && nearFire == false ){
		totalTicks = 0;
		cold++;
	}

	else if (totalTicks > COLDINTERVAL && nearFire == true){
		totalTicks = 0;
		cold -= 10;
	}

	if (cold > MAXCOLD){
		set_next_State(STATE_GAMELOSE_FROSTBITE);
	}

	else if (cold < 1){
		cold = 1;
	}
}

void c_Player::logic( Uint32 deltaTicks )
{
	setCamera();
	myFlashlight.setFlashlight(collisionBox.x, collisionBox.y);
	handleCold(deltaTicks);

	if (keysdown[0] == true && keysdown[1] == true ||
		keysdown[0] == true && keysdown[2] == true ||
		keysdown[0] == true && keysdown[3] == true ||
		keysdown[1] == true && keysdown[2] == true ||
		keysdown[1] == true && keysdown[3] == true ||
		keysdown[2] == true && keysdown[3] == true)
	{
		collisionBox.x -= xVel;
		collisionBox.y -= yVel;
	}

	onAnimate->animate(yVel, xVel, playerMoving, up, down, right, left);

	collisionBox.x += xVel;

	if (collisionBox.x < 0 - CHAR_VEL || collisionBox.x + CHAR_WIDTH > LEVEL_WIDTH + CHAR_VEL){
		collisionBox.x -= xVel;
	}

	collisionBox.y += yVel;

	if (collisionBox.y < 0 - CHAR_VEL|| collisionBox.y + CHAR_HEIGHT > LEVEL_HEIGHT + CHAR_VEL){
		collisionBox.y -= yVel;
	}

	std::vector<c_Tile*>::iterator uW_it, uW_itEnd = unWalkables.end();

	for (uW_it = unWalkables.begin(); uW_it != uW_itEnd; uW_it++)
	{
		c_Tile* tile = *uW_it;
		if (check_player_Collision( collisionBox, tile->getBox() ) == true)
		{
			collisionBox.x -= xVel; 
			collisionBox.y -= yVel;
		}
	} 

	std::vector<c_Entity*>::iterator uC_it, uC_itEnd = unCollidables.end();

	for (std::vector<c_Entity*>::iterator uC_it = unCollidables.begin(); uC_it != uC_itEnd; uC_it++)
	{
		c_Entity* entity = *uC_it;
		if ( check_player_Collision( collisionBox, entity->getBox() ) == true )
		{
			collisionBox.x -= xVel; 
			collisionBox.y -= yVel;
		}
	}
}

c_Flashlight* c_Player::getFlashlight()
{
	return &myFlashlight;
}

void c_Player::render()
{
	apply_surface(collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen, onAnimate->get_current_Frame());
	myFlashlight.render(collisionBox.x, collisionBox.y);
	coldMeter.showCold(cold);
}

c_Player::~c_Player(void)
{
	delete onAnimate;
	onAnimate = NULL;
}
