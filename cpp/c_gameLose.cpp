//#include "c_gameLose.h"
//
//
//c_gameLose::c_gameLose(void)
//{
//	blackscreen.x = 0;
//	blackscreen.y = 0;
//	blackscreen.w = SCREEN_WIDTH;
//	blackscreen.h = SCREEN_HEIGHT;
//
//	blank = load_image("alphaLayerWITHHOLE.png");
//	time = timer();
//
//	loseMessage = c_dialog_System();
//	loseMessage.readFile("losemessage.txt");
//
//	fadeIn();
//}
//
//void c_gameLose::handleInput()
//{
//	while ( SDL_PollEvent( &event ) )
//	{
//		if ( event.type == SDL_QUIT )
//		{
//			running = false;
//		}
//	}
//}
//
//void c_gameLose::fadeIn()
//{
//	/*while (alpha < 255){
//		time.start();
//
//		if (time.getTicks() > FADEOUT_INTERVAL){
//			alpha+=11;
//			SDL_SetAlpha(blank, SDL_SRCALPHA, alpha);
//			time.stop();
//		}
//	}*/
//}
//
//void c_gameLose::logic()
//{
//}
//
//void c_gameLose::render()
//{
//	apply_surface(blackscreen.x, blackscreen.y, blank, screen);
//	loseMessage.render();
//}
//
//c_gameLose::~c_gameLose(void)
//{
//}
