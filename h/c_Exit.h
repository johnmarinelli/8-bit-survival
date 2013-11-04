#pragma once
#include "c_entity.h"

const int EXIT_WIDTH = 36;
const int EXIT_HEIGHT = 7;

class c_Exit : public c_Entity
{
private:
	static int exitCount;
	int eID;
public:
	c_Exit(int x, int y);

	bool isLocked;
	int getID();
	static void resetExits();

	~c_Exit(void);
};

