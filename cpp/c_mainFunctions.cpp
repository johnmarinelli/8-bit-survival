#include "c_mainFunctions.h"

void initialize()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {   
		SDL_Quit();
    }

	SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {  
		SDL_Quit();
    }

	I_Audio_system::init();
    currentState = new c_stageOne();
}

bool loadFiles()
{
    //If everything loaded fine
    return true;
}

void cleanUp()
{
    delete currentState;
	currentState = NULL;
	delete player_ptr;
	player_ptr = NULL;

	I_Audio_system::cleanUp();
	TTF_Quit();
    //Quit SDL
    SDL_Quit();
}

void changeState()
{
	if ( nextState != STATE_NULL )
	{
		if ( nextState != STATE_EXIT )
		{
			delete currentState;
		}

		switch (nextState)
	{
		case STATE_INTRO: 
			currentState = new c_Intro(); break;
		case STATE_OVERWORLD:
			currentState = new c_stageOne((gameStates) stateID); break;
		case STATE_HOUSE1:
			currentState = new c_House1(); break;
		case STATE_HOUSE2:
			currentState = new c_House2(); break;
		case STATE_STORE:
			currentState = new c_Store((gameStates) stateID); break;
		case STATE_STORE_EXTENSION:
			currentState = new c_Store_Extension(); break;
		case STATE_MANOR:
			currentState = new c_Manor((gameStates) stateID); break;
		case STATE_MANOR2F:
			currentState = new c_Manor_2F(); break;
		case STATE_GAMEWIN_WITH_FRIEND:
			currentState = new c_gameOver(OVERTYPE_WIN_WITH_FRIEND); break;
		case STATE_GAMEWIN_NO_FRIEND:
			currentState = new c_gameOver(OVERTYPE_WIN_NO_FRIEND); break;
		case STATE_GAMELOSE_ENEMY_TOUCHED:
			currentState = new c_gameOver(OVERTYPE_LOSE_ENEMY_TOUCHED); break;
		case STATE_GAMELOSE_FROSTBITE:
			currentState = new c_gameOver(OVERTYPE_LOSE_FROSTBITE); break;
		case STATE_EXIT: break;
	}

		stateID = nextState;

		nextState = STATE_NULL;
	}
}
