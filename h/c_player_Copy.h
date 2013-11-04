#pragma once
#include "c_entity_is_movable.h"
#include "c_AI_fsm.h"

const int COPY_VELOCITY = 20;

class c_player_Copy : public c_Entity_is_movable
{
private:
	c_AIstate *AIstate;
	SDL_Rect objective;
	SDL_Rect distraction;
	bool alerted;

public:
	bool reachedStairs;
	static bool distracted;

	/*=====ctors=====*/
	c_player_Copy(int x, int y, gameStates current);
	c_player_Copy(const c_player_Copy &c);
	c_player_Copy& operator=(const c_player_Copy &c);

	void logic( Uint32 deltaTicks );
	void move( int deltaTicks );
	void render();

	~c_player_Copy(void);
};

