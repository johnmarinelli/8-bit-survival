#include "c_Piano.h"

extern noteStage nextNote = STAGENULL;
extern noteStage note_stageID = STAGENULL;

void set_next_noteState(noteStage input)
{
	if (input != SEQUENCECOMPLETE)
	{
		nextNote = input;
	}
	else
		nextNote = SEQUENCECOMPLETE;
}

void change_noteState(noteStates* &current_noteState)
{
	delete current_noteState;

	if (nextNote != SEQUENCECOMPLETE)
	{
		switch(nextNote){
		case SEQUENCE1: current_noteState = new sequenceOne(); break;
		case SEQUENCE2: current_noteState = new sequenceTwo(); break;
		case SEQUENCE3: current_noteState = new sequenceThree(); break;
		case SEQUENCE4: current_noteState = new sequenceFour(); break;
		case SEQUENCE5: current_noteState = new sequenceFive(); break;
		default: current_noteState = new sequenceOne(); break;
		}
		note_stageID = nextNote;
	}

	else{
		note_stageID = SEQUENCECOMPLETE;
		current_noteState = new sequenceComplete();
	}
}

noteStates::noteStates()
{
}

noteStates::~noteStates()
{
}

c_Piano::c_Piano()
{
}

c_Piano::c_Piano(int x, int y)
{
	entityGFX = load_image("piano.png");
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = PIANO_WIDTH;
	collisionBox.h = PIANO_HEIGHT;
	pianoID = PIANO_ID;

	if(!isPlayed){
	noteInput = new sequenceOne();
	}
	else
	noteInput = NULL;

	seqDone = false;
	piano = c_Stereo();

	piano.loadSFX("A.wav", "A");
	piano.loadSFX("B.wav", "B");
	piano.loadSFX("C.wav", "C");
	piano.loadSFX("D.wav", "D");
	piano.loadSFX("E.wav", "E");
	piano.loadSFX("F.wav", "F");
	piano.loadSFX("G.wav", "G");
	piano.loadSFX("seqDone.wav", "seqComplete");
}

c_Piano::c_Piano(const c_Piano &c)
{
	collisionBox.x = c.collisionBox.x;
	collisionBox.y = c.collisionBox.y;
	collisionBox.w = PIANO_WIDTH;
	collisionBox.h = PIANO_HEIGHT; 

	piano = c_Stereo();
	seqDone = c.seqDone;
	entityGFX = load_image("piano.png");
	pianoID = PIANO_ID;

	if(!isPlayed){
	noteInput = new sequenceOne();
	}
	else
	noteInput = NULL;

	piano.loadSFX("A.wav", "A");
	piano.loadSFX("B.wav", "B");
	piano.loadSFX("C.wav", "C");
	piano.loadSFX("D.wav", "D");
	piano.loadSFX("E.wav", "E");
	piano.loadSFX("F.wav", "F");
	piano.loadSFX("G.wav", "G");
	piano.loadSFX("seqDone.wav", "seqComplete");
}

c_Piano& c_Piano::operator=(const c_Piano &c)
{
	collisionBox.x = c.collisionBox.x;
	collisionBox.y = c.collisionBox.y;
	collisionBox.w = PIANO_WIDTH;
	collisionBox.h = PIANO_HEIGHT;

	piano = c_Stereo();
	seqDone = c.seqDone;
	entityGFX = load_image("piano.png");
	pianoID = PIANO_ID;

	if(!isPlayed){
	noteInput = new sequenceOne();
	}
	else
	noteInput = NULL;

	piano.loadSFX("A.wav", "A");
	piano.loadSFX("B.wav", "B");
	piano.loadSFX("C.wav", "C");
	piano.loadSFX("D.wav", "D");
	piano.loadSFX("E.wav", "E");
	piano.loadSFX("F.wav", "F");
	piano.loadSFX("G.wav", "G");
	piano.loadSFX("seqDone.wav", "seqComplete");

	return *this;
}

void c_Piano::handleInput()
{
	if ( event.type == SDL_KEYDOWN )
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_a: piano.play_loadedSFX( "A", NOTE_A ); break;
		case SDLK_b: piano.play_loadedSFX( "B", NOTE_B ); break;
		case SDLK_c: piano.play_loadedSFX( "C", NOTE_C ); break;
		case SDLK_d: piano.play_loadedSFX( "D", NOTE_D ); break;
		case SDLK_e: piano.play_loadedSFX( "E", NOTE_E ); break;
		case SDLK_f: piano.play_loadedSFX( "F", NOTE_F ); break;
		case SDLK_g: piano.play_loadedSFX( "G", NOTE_G ); break;
		}

		if (noteInput != NULL){
		noteInput->handleInput(event);
		}
	}
}

void c_Piano::logic()
{
	if(noteInput != NULL && !seqDone){

	if (note_stageID == SEQUENCECOMPLETE){
		isPlayed = true;
		c_player_Copy::distracted = true;
		piano.play_loadedSFX("seqComplete");
		seqDone = true;
	}

	change_noteState(noteInput);
	}
}

void c_Piano::render()
{
	apply_surface( collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen );
}

c_Piano::~c_Piano(void)
{
	if (noteInput != NULL){
	delete noteInput;
	noteInput = NULL;
	}
}
