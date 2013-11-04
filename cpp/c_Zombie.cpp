#include "c_Zombie.h"
#include "c_Entity_manager.h"

c_Zombie::c_Zombie()
{
}

c_Zombie::c_Zombie(int x, int y, int vel)
{
	up = false; down = false; left = false; right = false; alerted = false;
	isSpawned = false;
	entityGFX = load_image( "zombieSpriteSheet.png" );
	zombieVel = vel;
	yVel = xVel = 0;

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = ZOMBIE_WIDTH;
	collisionBox.h = ZOMBIE_HEIGHT;

	LEVEL_WIDTH = 1280; LEVEL_HEIGHT = 960;

	I_Audio_system::playSound("162472__kastenfrosch__scary.wav");

	noise = c_Stereo();
	noise.loadSFX("23129__digitil__crkts3b.wav", "zombieNoise");
	noise.play_distanceSFX("zombieNoise", collisionBox.x, collisionBox.y, player_ptr->getBox().x, player_ptr->getBox().y, ZOMBIENOISE_CHANNEL);

	onAnimate = new c_Animate( ENTITY_ZOMBIE );
	currentAIstate = new c_Chillmode();
}

c_Zombie::c_Zombie(const c_Zombie &c)
{
	collisionBox.x = c.collisionBox.x;
	collisionBox.y = c.collisionBox.y;
	collisionBox.w = ZOMBIE_WIDTH;
	collisionBox.h = ZOMBIE_HEIGHT;

	isSpawned = c.isSpawned;
	LEVEL_WIDTH = c.LEVEL_WIDTH;
	LEVEL_HEIGHT = c.LEVEL_HEIGHT;
	zombieVel = c.zombieVel;

	entityGFX = load_image( "zombieSpriteSheet.png" );
	up = false; down = false; left = false; right = false; alerted = false;
	yVel = xVel = 0;

	onAnimate = new c_Animate( ENTITY_ZOMBIE );
	currentAIstate = new c_Chillmode();
}

c_Zombie& c_Zombie::operator=(const c_Zombie &c)
{
	collisionBox.x = c.collisionBox.x;
	collisionBox.y = c.collisionBox.y;
	collisionBox.w = ZOMBIE_WIDTH;
	collisionBox.h = ZOMBIE_HEIGHT;

	isSpawned = c.isSpawned;
	LEVEL_WIDTH = c.LEVEL_WIDTH;
	LEVEL_HEIGHT = c.LEVEL_HEIGHT;
	zombieVel = c.zombieVel;

	entityGFX = load_image( "zombieSpriteSheet.png" );
	up = false; down = false; left = false; right = false; alerted = false;
	yVel = xVel = 0;

	onAnimate = new c_Animate(ENTITY_ZOMBIE);
	currentAIstate = new c_Chillmode();

	return *this;
}

void c_Zombie::init( int x, int y )
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = CHAR_WIDTH;
	collisionBox.h = CHAR_HEIGHT;
}

void c_Zombie::logic(Uint32 deltaTicks)
{
	currentAIstate->AIlogic(collisionBox, player_ptr->getBox(), xVel, yVel, up, down, left, right, alerted, zombieVel);
	noise.updatePosition(collisionBox.x, collisionBox.y, player_ptr->getBox().x, player_ptr->getBox().y, ZOMBIENOISE_CHANNEL);

	if (!alerted){
		setnextAIState( CHILL );
	}

	else if (alerted){
		setnextAIState( GO_TO );
	}

	onAnimate->animateLogic( up, down, left, right, xVel, yVel );
	move(deltaTicks);
}

void c_Zombie::move(Uint32 deltaTicks)
{
	collisionBox.x += xVel * ( deltaTicks / 1000.f );
	if ( collisionBox.x < 0 || collisionBox.x + CHAR_WIDTH > LEVEL_WIDTH )
	{
		collisionBox.x -= xVel *( deltaTicks / 1000.f );
	}

	collisionBox.y += yVel * ( deltaTicks / 1000.f );
	if ( collisionBox.y < 0 || collisionBox.y + CHAR_HEIGHT > LEVEL_HEIGHT )
	{
		collisionBox.y -= yVel *( deltaTicks / 1000.f );
	}

	if (check_collision(collisionBox, player_ptr->getBox()) ){
		set_next_State(STATE_GAMELOSE_ENEMY_TOUCHED);
		I_Audio_system::fadeout_SFX();
	}
	
	changeAIState(currentAIstate);
}

c_Zombie::~c_Zombie(void)
{
	delete currentAIstate;
	currentAIstate = NULL;
	delete onAnimate;
	onAnimate = NULL;
}
