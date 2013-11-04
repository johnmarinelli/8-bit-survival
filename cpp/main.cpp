#include "c_mainFunctions.h"/*-c_Globals, c_States-*/
#include "timer.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main( int argc, char* args[] )
{
	const int fps = 10;

	initialize();
	
	_CrtDumpMemoryLeaks();

	loadFiles();

	timer fpsTimer;
	
	while(running)
	{
		fpsTimer.start();

		currentState->handleInput();
		currentState->logic();
		changeState();
		currentState->render();
		
		SDL_Flip( screen );

		if ( fpsTimer.getTicks() < 1000/fps )
		{
			SDL_Delay( (1000/fps) - fpsTimer.getTicks());
		}
	}

	cleanUp();

	return 0;
}