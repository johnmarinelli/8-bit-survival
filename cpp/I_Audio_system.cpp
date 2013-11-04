#include "I_Audio_system.h"

I_Audio_system::I_Audio_system(void)
{
}

void I_Audio_system::init()
{
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
}

void I_Audio_system::playSound(const char* fileName)
{
	Mix_Chunk *SFX = Mix_LoadWAV(fileName);
	Mix_PlayChannel(-1, SFX, 0);
}

void I_Audio_system::playMUS(const char* fileName)
{
	Mix_Music *MUS = Mix_LoadMUS(fileName);
	Mix_PlayMusic(MUS, -1);
}

void I_Audio_system::fadeout_MUS()
{
	if (Mix_PlayingMusic()){
		Mix_FadeOutMusic(3000);
	}
}

void I_Audio_system::fadeout_SFX()
{
	Mix_FadeOutChannel(-1, 1500);
}

void I_Audio_system::cleanUp()
{
	fadeout_MUS();
	fadeout_SFX();
	Mix_CloseAudio();
}

I_Audio_system::~I_Audio_system(void)
{
}

c_Stereo::c_Stereo(void)
{
}

void c_Stereo::loadMUS(const char* fileName, std::string MUSname)
{
	Mix_Music *MUS= Mix_LoadMUS(fileName);

	if (MUS != NULL){
		MUS_list.insert( std::pair<std::string, Mix_Music*>(MUSname, MUS) );
	}
	else
		return;
}

void c_Stereo::loadSFX(const char* fileName, std::string SFXname)
{
	Mix_Chunk *SFX = Mix_LoadWAV( fileName );

	if (SFX != NULL){
	SFX_list.insert( std::pair<std::string, Mix_Chunk*>(SFXname, SFX) );
	}
	else
		return;
}

void c_Stereo::playSFX(const char* fileName)
{
	Mix_Chunk *SFX = Mix_LoadWAV( fileName );
	Mix_PlayChannel(-1, SFX, 0);
}

void c_Stereo::play_loadedSFX(std::string SFXname, const int &channel)
{
	Mix_Chunk *SFX;

	std::map<std::string, Mix_Chunk*>::const_iterator results = SFX_list.find(SFXname);
	if ( results == SFX_list.end() ){
		SFX = NULL;
	}
	else
		SFX = results->second;

	Mix_PlayChannel(channel, SFX, 0);
}

void c_Stereo::play_distanceSFX(std::string SFXname, const int pX, const int pY, const int rX, const int rY, const int channel)
{
	Mix_Chunk *SFX;

	std::map<std::string, Mix_Chunk*>::const_iterator results = SFX_list.find(SFXname);
	if ( results == SFX_list.end() ){
		SFX = NULL;
	}

	else{
		SFX = results->second;
		Mix_SetPosition(channel, getAngle(pX, pY, rX, rY), sound_Distance(pX, pY, rX, rY));
		Mix_PlayChannel(channel, SFX, channel);
	}
}

void c_Stereo::updatePosition(const int &pX, const int &pY, const int &rX, const int &rY, const int &channel)
{
	Mix_SetPosition(channel, getAngle( pX, pY, rX, rY), sound_Distance(pX, pY, rX, rY));
}

void c_Stereo::play_loadedMUS(std::string MUSname)
{
	Mix_Music *MUS;

	std::map<std::string, Mix_Music*>::const_iterator results = MUS_list.find(MUSname);

	if (results == MUS_list.end()){
		MUS = NULL;
	}
	else{
		MUS = results->second;
		Mix_PlayMusic(MUS, -1);
	}
}


c_Stereo::~c_Stereo(void)
{
	std::for_each(SFX_list.begin(), SFX_list.end(), chunkDeallocater());
	std::for_each(MUS_list.begin(), MUS_list.end(), musicDeallocater());

	SFX_list.clear();
	MUS_list.clear();
}