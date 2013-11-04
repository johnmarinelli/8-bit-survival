#pragma once
#include "SDL_ttf.h"
#include "c_imgFunctions.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "c_Globals.h"

const int TEXT_HEIGHT = 12;

class c_dialog_System
{
public:
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Surface *message;

	c_dialog_System(void);
	c_dialog_System(const c_dialog_System &c);
	c_dialog_System& operator=(const c_dialog_System &c);

	void setMessage( const char* msg );
	void readFile( std::string fileName );

	void render(int x, int y);
	void render();

	virtual ~c_dialog_System(void);
};

class c_cold_Meter : public c_dialog_System
{
public:
	c_cold_Meter(void);
	void showCold( int cold );
	~c_cold_Meter(void);
};

