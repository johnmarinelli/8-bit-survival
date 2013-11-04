#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

extern SDL_Rect camera;
extern SDL_Surface* screen;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );