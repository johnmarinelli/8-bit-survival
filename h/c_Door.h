#pragma once
#include "c_Entity.h"
#include "c_Globals.h"
#include "c_Entity_manager.h"

const int DOOR_WIDTH = 32;
const int DOOR_HEIGHT = 36;
const int STAIR_WIDTH = 123;
const int STAIR_HEIGHT = 33;

class c_Door : public c_Entity
{
public:
	static int doorCount;
	int dID;

	c_Door(void);
	int getID();
	static void resetCount();
	virtual ~c_Door(void);
};

class c_Door_h1 : public c_Door
{
public:
	c_Door_h1( int x, int y);
	void logic();
	~c_Door_h1(void);
};

class c_Door_h2 : public c_Door
{
public:
	c_Door_h2( int x, int y );
	void logic();
	~c_Door_h2(void);
};

class c_Door_store : public c_Door
{
public:
	c_Door_store( int x, int y );
	void logic();
	~c_Door_store(void);
};

class c_Door_manor: public c_Door
{
public:
	c_Door_manor( int x, int y );
	void logic();
	~c_Door_manor(void);
};

class c_Upstairs_manor: public c_Door
{
public:
	c_Upstairs_manor( int x, int y );
	void logic();
	~c_Upstairs_manor(void);
};