#pragma once
#include "SDL_mixer.h"
#include "fx_checkCollision.h" /*for distance formula*/
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class I_Audio_system
{
private:
public:
	I_Audio_system(void);
	
	static void init();
	static void playMUS(const char* fileName);
	static void playSound(const char* fileName);
	
	static void fadeout_MUS();
	static void fadeout_SFX();

	static void cleanUp();

	struct chunkDeallocater
	{
		void operator() ( const std::pair<std::string, Mix_Chunk*> &p ) const
		{
			Mix_FreeChunk(p.second);
		}
	};

	struct musicDeallocater
	{
		void operator() ( const std::pair<std::string, Mix_Music*> &p ) const
		{
			Mix_FreeMusic(p.second);
		}
	};

	virtual ~I_Audio_system(void);
};

const int ZOMBIENOISE_CHANNEL = 2;
const int SOUND1_CHANNEL = 3;
const int SOUND2_CHANNEL = 4;
const int SOUND3_CHANNEL = 5;
const int SOUND4_CHANNEL = 6;
const int TRUESOUND_CHANNEL = 7;

const int NOTE_A = 1;
const int NOTE_B = 2;
const int NOTE_C = 3;
const int NOTE_D = 4;
const int NOTE_E = 5;
const int NOTE_F = 6;
const int NOTE_G = 7;

const int MAX_CHANNELS = 8;

class c_Stereo : public I_Audio_system
{
private:
	std::map<std::string, Mix_Chunk*> SFX_list;
	std::map<std::string, Mix_Music*> MUS_list;

public:
	c_Stereo(void);

	void loadSFX(const char* fileName, std::string SFXname);
	void loadMUS(const char* fileName, std::string MUSname);

	void updatePosition(const int &pX, const int &pY, const int &rX, const int &rY, const int &channel = -1);

	void playSFX(const char* fileName);
	void play_loadedSFX(std::string SFXname, const int &channel = -1);
	void play_loadedMUS(std::string MUSname);

	void play_distanceSFX(std::string SFXname, const int pX, const int pY,
		const int rX, const int rY, const int channel);
	
	~c_Stereo(void);
};

