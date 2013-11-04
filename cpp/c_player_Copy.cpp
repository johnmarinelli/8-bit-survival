#include "c_player_Copy.h"

bool c_player_Copy::distracted = false;

c_player_Copy::c_player_Copy(int x, int y, gameStates current)
{
	up = false; down = false; left = false; right = false; alerted = true;
	reachedStairs = false;
	entityGFX = load_image("villagerSpritesheet.png");

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = CHAR_WIDTH;
	collisionBox.h = CHAR_HEIGHT;
	xVel = 0;
	yVel = 0;

	onAnimate = new c_Animate( ENTITY_PLAYER );
	AIstate = new c_Gotomode();

	/*incoming magic numbers*/
	objective.x = 300;
	objective.y = -10;
	objective.w = 123;
	objective.h = 33;

	distraction.x = 40;
	distraction.y = 350;
	distraction.w = 40;
	distraction.h = 40;
}

c_player_Copy::c_player_Copy(const c_player_Copy &c)
{
	entityGFX = load_image("villagerSpritesheet.png");

	collisionBox = c.collisionBox;
	xVel = 0;
	yVel = 0;

	onAnimate = new c_Animate( ENTITY_PLAYER );
	AIstate = new c_Gotomode();
}

c_player_Copy& c_player_Copy::operator=(const c_player_Copy &c)
{
	entityGFX = load_image("villagerSpritesheet.png");

	collisionBox = c.collisionBox;
	xVel = 0;
	yVel = 0;

	onAnimate = new c_Animate( ENTITY_PLAYER );
	AIstate = new c_Gotomode();

	return *this;
}

void c_player_Copy::logic(Uint32 deltaTicks)
{
	if(!distracted){
		AIstate->AIlogic( collisionBox, objective, xVel, yVel, up, down, left, right, alerted, COPY_VELOCITY );
	}
	else if (distracted){
		AIstate->AIlogic( collisionBox, distraction, xVel, yVel, up, down, left, right, alerted, COPY_VELOCITY );
	}

	move( deltaTicks );
	onAnimate->animateLogic( up, down, left, right, xVel, yVel );

	reachedStairs = check_collision(collisionBox, objective);
}

void c_player_Copy::move( int deltaTicks )
{
	collisionBox.x += xVel * ( deltaTicks / 1000.f );
	collisionBox.y += yVel * ( deltaTicks / 1000.f );
}

void c_player_Copy::render()
{
	if (!reachedStairs){
		apply_surface( collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen, onAnimate->get_current_Frame() );
	}
}

c_player_Copy::~c_player_Copy(void)
{
	delete onAnimate;
	onAnimate = NULL;
	delete AIstate;
	AIstate = NULL;
}
