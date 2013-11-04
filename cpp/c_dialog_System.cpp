#include "c_dialog_System.h"


c_dialog_System::c_dialog_System(void)
{
	TTF_Init();
	font = TTF_OpenFont( "00TT.TTF", TEXT_HEIGHT );
	textColor.b = 255; textColor.g = 255; textColor.r = 255;
	message =  TTF_RenderText_Solid( font, "", textColor );
}

c_dialog_System::c_dialog_System(const c_dialog_System &c)
{
	font = TTF_OpenFont( "00TT.TTF", TEXT_HEIGHT );
	textColor.b = 255; textColor.g = 255; textColor.r = 255;
	message =  TTF_RenderText_Solid( font, "", textColor );
}

c_dialog_System& c_dialog_System::operator=(const c_dialog_System &c)
{
	font = TTF_OpenFont( "00TT.TTF", TEXT_HEIGHT );
	textColor.b = 255; textColor.g = 255; textColor.r = 255;
	message =  TTF_RenderText_Solid( font, "", textColor );
	return *this;
}

void c_dialog_System::setMessage( const char* msg )
{
	message = TTF_RenderText_Solid( font, msg, textColor );
}

void c_dialog_System::readFile( std::string fileName )
{
	std::ifstream textFile( fileName );

	std::string line;
	std::string msg;

	while ( !textFile.eof() ) 
	{
		getline(textFile, line);
		msg += "\n" + line;
	}

	textFile.close();

	const char *ch_msg = msg.c_str();
	message = TTF_RenderText_Solid( font, ch_msg, textColor );
}

void c_dialog_System::render(int x, int y)
{
	apply_surface( x - camera.x, (y - TEXT_HEIGHT) - camera.y, message, screen );
}

void c_dialog_System::render()
{
	apply_surface( 0, 0, message, screen );
}

c_dialog_System::~c_dialog_System(void)
{
	TTF_CloseFont(font);
	SDL_FreeSurface(message);
}

c_cold_Meter::c_cold_Meter(void)
{
	TTF_Init();
	font = TTF_OpenFont( "00TT.TTF", TEXT_HEIGHT );
	textColor.b = 255; textColor.g = 255; textColor.r = 255;

	message = TTF_RenderText_Solid( font, "COLD: ", textColor );
}

void c_cold_Meter::showCold(int cold)
{
	std::string res;
	std::stringstream out;
	out << cold;
	res = out.str();

	std::string defaultmsg = "COLD: ";
	std::string total = defaultmsg + res;

	message = TTF_RenderText_Solid( font, total.c_str(), textColor );
	apply_surface( 0, SCREEN_HEIGHT - TEXT_HEIGHT, message, screen );
}

c_cold_Meter::~c_cold_Meter(void)
{
}
