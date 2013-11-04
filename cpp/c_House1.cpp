#include "c_House1.h"

bool c_House1::noteFound = false;

c_House1::c_House1(void)
{
    I_Audio_system::playSound("doorOpen.wav");

	entityManager = c_Entity_manager();

	tileArray = c_Tile::loadTiles("house1.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	if (!loadObjects()){
		return;
	}

	h1_player->setLevel(this->LEVEL_WIDTH, this->LEVEL_HEIGHT);

	if (h1_enemy != NULL ){
		h1_enemy->LEVEL_HEIGHT = this->LEVEL_HEIGHT;
		h1_enemy->LEVEL_WIDTH = this->LEVEL_WIDTH;
		h1_enemy->init(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
	}

	if (!noteFound){
		exit->isLocked = true;
	}
	else
		exit->isLocked = false;

	narrator = c_dialog_System();
}

bool c_House1::loadObjects()
{
	std::ifstream map("house1.map");

	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );

	while ( !map.eof() )
		{
			int objType = -1;
			
			int objX, objY = 0;

			map >> objType;
			map >> objX; map >> objY;

			switch (objType){
			case 0:{
				c_Zombie *zombie = new c_Zombie( objX, objY );
				entityManager.add( "Zombie", zombie );
			}
			break;

			case 1:
			{
				h1_player = c_Entity_manager::getPlayer();
				h1_player->init(objX, objY);
				
				if (c_Entity_manager::getEnemy() != NULL && c_Entity_manager::getEnemy()->isSpawned){
					h1_enemy = c_Entity_manager::getEnemy();
				}
				else{
					h1_enemy = NULL;
				}
			}
			break;

			case 2:
			{
				c_Note *note = new c_Note( NOTE_HOUSE1, objX, objY );
				h1_note = *note;
				entityManager.add_Special(note);
			}
			break;

			case 3:
			{
				c_Wall *wall = new c_Wall( objX, objY );
				entityManager.add_Decor( wall->getID(), wall );

				for (int i = 0; i < TOTAL_TILES; i++)
				{
					if (tileArray[i]->getX() == objX
						  && tileArray[i]->getY() == objY)
					{
						tileArray[i]->setWalkable( false );
						c_Entity_is_movable::unWalkables.push_back(tileArray[i]);
					}
				}
			}
			break;

			case 17:
			{
				exit = new c_Exit( objX, objY + 35);
				entityManager.add_Decor( exit->getID(), exit );
				c_Entity_is_movable::unCollidables.push_back(exit);
			}
			break;

			case ENTITY_CRATE_FAT:
			{
			c_Entity *decor = new c_Entity(objX, objY, 
				CRATE_FAT_WIDTH, CRATE_FAT_HEIGHT, "crate-fat.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_CRATE_TALL:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				CRATE_TALL_WIDTH, CRATE_TALL_HEIGHT, "crate-tall.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}break;

			case ENTITY_CHAIR:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				CHAIR_WIDTH, CHAIR_HEIGHT, "chair.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_HOUSEPLANT:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				HOUSEPLANT_WIDTH, HOUSEPLANT_HEIGHT, "houseplant-tall.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_TABLE_LONG:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				TABLE_LONG_WIDTH, TABLE_LONG_HEIGHT, "table-long.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_BOOKSHELF:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				BOOKSHELF_WIDTH, BOOKSHELF_HEIGHT, "bookcase-full.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;
		}

	}

	map.close();
	return true;
}

void c_House1::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		h1_player->handleInput();

		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_House1::logic()
{
	entityManager.logicAll();

	if (check_collision( h1_player->getBox(), h1_note.getBox()) ){
		exit->isLocked = false;
		noteFound = true;
	}

	if (check_collision( h1_player->getBox(), exit->getBox() ) && !exit->isLocked){
		set_next_State( STATE_OVERWORLD );
	}

	else if (check_collision( h1_player->getBox(), exit->getBox() ) && exit->isLocked){
		narrator.setMessage("The door seems to be locked.");
	}

	else
		narrator.setMessage("");

}

void c_House1::render()
{
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		tileArray[t]->show();
	}

	entityManager.drawAll();

	narrator.render();
}

c_House1::~c_House1(void)
{
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		delete tileArray[t];
		tileArray[t] = NULL;
	}
	
	h1_player = NULL;

	if (h1_enemy != NULL){
		h1_enemy = NULL;
	}

	exit = NULL;
}