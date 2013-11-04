#include "timer.h"


timer::timer(void)
{
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void timer::stop()
{
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void timer::pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTicks = SDL_GetTicks()-startTicks;
	}
}

void timer::unpause()
{
	if (paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

int timer::getTicks()
{
	if (started)
	{
		if (paused)
		{
			return pausedTicks;
		}
		
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}
		
	return 0;
}


timer::~timer(void)
{
}
