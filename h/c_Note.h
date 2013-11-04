#pragma once
#include "c_dialog_System.h"
#include "c_Entity.h"
#include "c_Entity_manager.h"

enum noteTypes{
	NOTE_HOUSE1,
	NOTE_STORE,
	NOTE_MANOR,
	NOTE_HOUSE2,
	NOTE_MANOR2,
	NOTE_1_STORE,
};

const int NOTE_WIDTH = 15;
const int NOTE_HEIGHT = 20;

class c_Note : public c_Entity
{
private:
	static int noteCount;
	int noteID;

	noteTypes type;
	bool canSee;
	c_dialog_System onRead;

	std::string noteFile;

public:
	c_Note();
	c_Note(noteTypes note, int x, int y);

	int getID();

	void logic();
	void render();

	static void resetCount();

	~c_Note(void);
};

