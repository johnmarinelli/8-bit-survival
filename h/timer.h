#pragma once
#include "SDL.h"

class timer
{
private:
	int startTicks;
	int pausedTicks;

	bool paused;
	bool started;

public:
	timer(void);
	void start();
	void stop();
	void pause();
	void unpause();
	int getTicks();
	~timer(void);
};

