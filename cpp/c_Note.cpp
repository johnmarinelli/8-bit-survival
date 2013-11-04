#include "c_Note.h"

int c_Note::noteCount = 500;

c_Note::c_Note()
{
}

c_Note::c_Note(noteTypes note, int x, int y)
{
	entityGFX = load_image( "note.png" );

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = NOTE_WIDTH;
	collisionBox.h = NOTE_HEIGHT;

	if (note == NOTE_HOUSE1){
		noteFile = "h1_note.txt";
	}

	else if (note == NOTE_STORE){
		noteFile = "store_note.txt";
	}

	else if (note == NOTE_MANOR){
		noteFile = "manor_note.txt";
	}

	else if (note == NOTE_HOUSE2){
		noteFile = "h2_note.txt";
	}

	else if (note == NOTE_MANOR2){
		noteFile = "manor2_note.txt";
	}

	else if (note == NOTE_1_STORE){
		noteFile = "1_store_note.txt";
	}

	onRead.readFile( noteFile );

	noteID = noteCount;
	noteCount++;
}

void c_Note::logic()
{
	if ( check_collision( collisionBox, c_Entity_manager::getPlayer()->getBox()) ){
		canSee = true;
	}
	else
		canSee = false;
}

void c_Note::render()
{
	apply_surface( collisionBox.x - camera.x, collisionBox.y - camera.y, entityGFX, screen );

	if (canSee){
		onRead.render();
	}
}

void c_Note::resetCount()
{
	noteCount = 500;
}

int c_Note::getID()
{
	return noteID;
}

c_Note::~c_Note(void)
{
}
