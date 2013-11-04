#pragma once
#include "c_Entity.h"
#include "fx_checkCollision.h"
#include "c_Entity_manager.h"

class c_Shovel : public c_Entity
{
private:
	static int w_ID;
	int ID_number;

public:
	c_Shovel(int x, int y);

	void logic();

	int getID();
	~c_Shovel(void);
};

