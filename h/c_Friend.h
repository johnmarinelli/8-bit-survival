#pragma once
#include "c_entity_is_movable.h"
#include "I_Audio_system.h"
#include "c_AI_fsm.h"
#include <vector>

const int FRIEND_WIDTH = 28;
const int COLLAPSED_FRIEND_HEIGHT = 10;
const int FRIEND_HEIGHT = 30;
const int SHIVER_FRAME_INTERVAL = 100;
const int CRAZY_FRAME_INTERVAL = 300;
const int MESSAGE_FRAME_INTERVAL = 1000;

const int CRAZY_ID = 3630;
const int SHIVERING_ID = 3631;
const int DEAD_ID = 3632;

class c_crazy_Friend : public c_Entity_is_movable
{
private:
	bool nextFrame;
	bool alerted;
	int tickCount;
	int msgtickCount;

	char line1[99], line2[99] ;

	c_AIstate *AIstate;
	c_dialog_System *onSpeak;

	int ID;

public:
	/*=====ctors=====*/
	c_crazy_Friend(int x, int y, std::string filename, std::string GFXfilename);
	c_crazy_Friend(const c_crazy_Friend &c);
	c_crazy_Friend& operator=(const c_crazy_Friend &c);

	inline void say();
	void logic( Uint32 deltaTicks );
	void render();

	~c_crazy_Friend(void);
};

class c_dead_Friend : public c_Entity
{
private:
	int ID;

public:
	c_dead_Friend(int x, int y);

	int getID();

	~c_dead_Friend(void);
};
