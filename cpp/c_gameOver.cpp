#include "c_gameOver.h"


c_gameOver::c_gameOver(OVERTYPE ending)
{
	blackscreen.x = 0;
	blackscreen.y = 0;
	blackscreen.w = SCREEN_WIDTH;
	blackscreen.h = SCREEN_HEIGHT;

	blank = load_image("alphaLayerWITHHOLE.png");
	time = timer();
	message = c_dialog_System();

	switch(ending){
	case OVERTYPE_LOSE_ENEMY_TOUCHED: message.readFile("losemessage.txt"); break;
	case OVERTYPE_LOSE_FROSTBITE: message.readFile("frostbitemessage.txt"); break;
	case OVERTYPE_WIN_WITH_FRIEND: message.readFile("winmessage.txt"); break;
	case OVERTYPE_WIN_NO_FRIEND: message.readFile("winnofriendmessage.txt"); break;
	}

	alpha = 235;

	fadeIn();
}

void c_gameOver::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_gameOver::fadeIn()
{
	int start = SDL_GetTicks();

	while (alpha < 255){
		if (SDL_GetTicks() - start > FADEOUT_INTERVAL){
			alpha+=2;
			start = SDL_GetTicks();
		}
	}
}

void c_gameOver::logic()
{
}

void c_gameOver::render()
{
	SDL_SetAlpha(blank, SDL_SRCALPHA, alpha);
	apply_surface(blackscreen.x, blackscreen.y, blank, screen);
	message.render();
}

c_gameOver::~c_gameOver(void)
{
}
