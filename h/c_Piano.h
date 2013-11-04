#pragma once
#include "c_Entity.h"
#include "c_player_Copy.h"
#include "I_Audio_system.h"
#include "c_dialog_System.h"

const int PIANO_WIDTH = 26;
const int PIANO_HEIGHT = 55;
const int PIANO_ID = 999;

enum noteStage{
	STAGENULL,
	SEQUENCE1,
	SEQUENCE2,
	SEQUENCE3,
	SEQUENCE4,
	SEQUENCE5,
	SEQUENCECOMPLETE,
};
void set_next_noteState(noteStage input);

/*finite state machine for puzzle three*/
class noteStates
{
public:
	noteStates();

	virtual void handleInput(SDL_Event &event) = 0;
	
	virtual ~noteStates();
};

void change_noteState(noteStates* &currentState);

extern noteStage nextNote;
extern noteStage note_stageID;

class sequenceOne : public noteStates
{
public:
	sequenceOne(){};
	void handleInput(SDL_Event &event)
	{
		switch (event.key.keysym.sym)
		{ 
		case SDLK_c: set_next_noteState(SEQUENCE2); break;
		    default: set_next_noteState(SEQUENCE1); break;
		}
	};

	~sequenceOne(){};
};

class sequenceTwo : public noteStates
{
public:
	sequenceTwo()
	{
	};

	void handleInput(SDL_Event &event){
		switch (event.key.keysym.sym)
		{ 
		case SDLK_a: set_next_noteState(SEQUENCE3);break;
		    default: set_next_noteState(SEQUENCE1); break;
		}
	};
	~sequenceTwo(){};
};

class sequenceThree : public noteStates
{
public:
	sequenceThree(){};
	void handleInput(SDL_Event &event){
		switch (event.key.keysym.sym)
		{ 
		case SDLK_b: set_next_noteState(SEQUENCE4);break;
		    default: set_next_noteState(SEQUENCE1); break;
		}
	};
	~sequenceThree(){};
};

class sequenceFour : public noteStates
{
public:
	sequenceFour(){};
	void handleInput(SDL_Event &event){
		switch (event.key.keysym.sym)
		{
		case SDLK_c: set_next_noteState(SEQUENCE5);break;
		    default: set_next_noteState(SEQUENCE1); break;
		}
	};
	~sequenceFour(){};
};

class sequenceFive : public noteStates
{
public:
	sequenceFive(){};
	void handleInput(SDL_Event &event){
		switch (event.key.keysym.sym)
		{
		case SDLK_e: set_next_noteState(SEQUENCECOMPLETE);break;
			default: set_next_noteState(SEQUENCE1); break;
		}
	};
	~sequenceFive(){};
};

class sequenceComplete : public noteStates
{
public:
	sequenceComplete(){};
	void handleInput(SDL_Event &event){};
	~sequenceComplete(){};
};

static bool isPlayed = false;
class c_Piano : public c_Entity
{
private:
	c_Stereo piano;
	noteStates *noteInput;
	bool seqDone;

public:
	int pianoID;

	/*=====ctors=====*/
	c_Piano();
	c_Piano(int x, int y);
	c_Piano(const c_Piano &c);
	c_Piano& operator=(const c_Piano &c);

	void handleInput();
	void logic();
	void render();
	
	~c_Piano(void);
};


