#include "c_Store_Extension.h"

c_Store_Extension::c_Store_Extension()
{
	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("storeExtension.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	loadObjects();

	exit.x = LEVEL_WIDTH;
	exit.y = LEVEL_HEIGHT/2;
	exit.w = 0;
	exit.h = HIDDEN_DOOR_HEIGHT;
	
	store_player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
	store_player->init(exit.x - (SPRITE_WIDTH*2), exit.y);
	store_player->deadfriend_visited = true;
}

void c_Store_Extension::loadObjects()
{
	std::ifstream map("storeExtension.map");

	map.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
	map.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
	map.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

	while ( !map.eof() )
		{
			int objType = -1;
			
			int objX, objY = 0;

			map >> objType;
			map >> objX; map >> objY;

			switch (objType)
			{
			case 1: store_player = c_Entity_manager::getPlayer();
					break;
			case 2:  {
				c_Note *note = new c_Note(NOTE_STORE, objX, objY);
				entityManager.add_Special(note);
					 }
					break;
			case 23:{
				c_dead_Friend *friend_Dead= new c_dead_Friend( objX, objY );
				entityManager.add_Decor(friend_Dead->getID(), friend_Dead);
					}
					break;
			case ENTITY_CRATE_FAT:{
					c_Entity *decor = new c_Entity(objX, objY,  CRATE_FAT_WIDTH, CRATE_FAT_HEIGHT, "crate-fat.png");
					entityManager.add_Decor( c_Entity::decorCount++, decor );
					c_Entity_is_movable::unCollidables.push_back(decor);
								  }
					break;
			}
	}
	map.close();
}

void c_Store_Extension::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		store_player->handleInput();

		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_Store_Extension::logic()
{
	entityManager.logicAll();

	if ( check_collision(store_player->getBox(), exit) ){
		set_next_State(STATE_STORE);
	}
}

void c_Store_Extension::render()
{
	for ( int t = 0; t < TOTAL_TILES; t++ ){
		tileArray[t]->show();
	}

	entityManager.drawAll();
}

c_Store_Extension::~c_Store_Extension()
{
	for (int t = 0; t < TOTAL_TILES; t++)
	{
		delete tileArray[t];
		tileArray[t] = NULL;
	}

	store_player = NULL;
}
