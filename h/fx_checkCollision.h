#pragma once
#include "SDL.h"
#include <cmath>
#include "c_Tile.h"

struct circle{
	int x,y;
	int r;
};

bool check_collision( SDL_Rect &a, SDL_Rect &b);
bool check_player_Collision( SDL_Rect &a, SDL_Rect &b );

double distance(const int &x1, const int &y1,
	const int &x2, const int &y2);

int inverted_sound_Distance( const int &pX, const int &pY,
	const int &rX, const int &rY );
int sound_Distance( const int &pX, const int &pY,
	const int &rX, const int &rY );

int getAngle( const int &pX, const int &pY,
	const int &rX, const int &rY);

bool check_collision( const circle &a, const SDL_Rect &b );