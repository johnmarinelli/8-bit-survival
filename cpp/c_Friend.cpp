#include "c_Friend.h"

c_crazy_Friend::c_crazy_Friend(int x, int y, std::string filename, std::string GFXfilename) : c_Entity_is_movable(x, y, FRIEND_WIDTH, COLLAPSED_FRIEND_HEIGHT)
{
	entityGFX = load_image(GFXfilename);
	std::ifstream ifile(filename);

	ifile.getline(line1, 999);
	ifile.getline(line2, 999);

	onAnimate = new c_Animate( FRIEND_SHIVERING );
	AIstate = new c_Chillmode();
	onSpeak = new c_dialog_System();

	ID = CRAZY_ID;
	tickCount = 0;
	msgtickCount = 0;
}

c_crazy_Friend::c_crazy_Friend(const c_crazy_Friend &c)
{
	collisionBox = c.collisionBox;

	entityGFX = load_image("friend-crazy.png");

	onAnimate = new c_Animate( FRIEND_SHIVERING );
	AIstate = new c_Chillmode();
	onSpeak = new c_dialog_System();

	ID = CRAZY_ID;
	tickCount = 0;
	msgtickCount = 0;
}

c_crazy_Friend& c_crazy_Friend::operator=(const c_crazy_Friend &c)
{
	collisionBox = c.collisionBox;

	entityGFX = load_image("friend-crazy.png");

	onAnimate = new c_Animate( FRIEND_SHIVERING );
	AIstate = new c_Chillmode();
	onSpeak = new c_dialog_System();

	ID = CRAZY_ID;
	tickCount = 0;
	msgtickCount = 0;

	return *this;
}

void c_crazy_Friend::say()
{
	if (alerted){
		onSpeak->setMessage(line2);
	}
	else{
		onSpeak->setMessage(line1);
	}
}

void c_crazy_Friend::logic( Uint32 deltaTicks )
{
	AIstate->AIlogic( collisionBox, player_ptr->getBox(), xVel, yVel, up, down, left, right, alerted );

	tickCount += deltaTicks;

	if ( tickCount > CRAZY_FRAME_INTERVAL )
	{
		nextFrame = true;
		tickCount = 0;
	}
	
	onAnimate->static_Animation( nextFrame );
	nextFrame = false;
	
	msgtickCount += deltaTicks;
}

void c_crazy_Friend::render()
{
	apply_surface( collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen, onAnimate->get_current_Frame() );
	say();
	onSpeak->render(collisionBox.x, collisionBox.y);
}

c_crazy_Friend::~c_crazy_Friend(void)
{
	delete onAnimate;
	onAnimate = NULL;
	delete AIstate;
	AIstate = NULL;
	delete onSpeak;
	onSpeak = NULL;
}

c_dead_Friend::c_dead_Friend(int x, int y) : c_Entity(x, y, FRIEND_WIDTH, COLLAPSED_FRIEND_HEIGHT)
{
	entityGFX = load_image( "friend-dead.png" );

	ID = DEAD_ID;
}

int c_dead_Friend::getID()
{
	return ID;
}

c_dead_Friend::~c_dead_Friend(void)
{
}