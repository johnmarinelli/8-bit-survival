#include "c_House2.h"

c_House2::c_House2(void)
{
	I_Audio_system::playSound("doorOpen.wav");

	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("house2.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	loadObjects();

	h2_player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);

	if (h2_enemy != NULL){
		h2_enemy->LEVEL_HEIGHT = LEVEL_HEIGHT;
		h2_enemy->LEVEL_WIDTH = LEVEL_WIDTH;
		h2_enemy->init(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
	}
}

void c_House2::loadObjects()
{
	std::ifstream map("house2.map");

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
			case 0:
			{
				/*c_Zombie *zombie = new c_Zombie( objX, objY );
				entityManager.add( "Zombie", zombie );*/
			}
			break;

			case 1:
			{
				h2_player = c_Entity_manager::getPlayer();
				h2_player->init( objX, objY );

				if (c_Entity_manager::getEnemy() != NULL && c_Entity_manager::getEnemy()->isSpawned){
					h2_enemy = c_Entity_manager::getEnemy();
				}
				else{
					h2_enemy = NULL;
				}
			}
			break;

			case 2:
			{
				c_Note *note = new c_Note( NOTE_HOUSE2, objX, objY );
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

			case 16:{
				c_Door_h1 *door = new c_Door_h1( objX, objY );
				entityManager.add_Decor( door->getID(), door );
			}
			break;

			case 17:{
				exit = new c_Exit( objX, objY + 35);
				entityManager.add_Decor( exit->getID(), exit );
			}
			break;

			case 22:{
				c_crazy_Friend *friend_Crazy= new c_crazy_Friend(objX, objY, "crazyFriend.txt", "friend-crazy.png");
				entityManager.add("crazyFriend", friend_Crazy);
				c_Entity_is_movable::unCollidables.push_back(friend_Crazy);
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
}

void c_House2::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		h2_player->handleInput();

		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_House2::logic()
{
	entityManager.logicAll();

	if ( check_collision( h2_player->getBox(), exit->getBox() ) == true )
	{
		set_next_State( STATE_OVERWORLD );
	}
}

void c_House2::render()
{
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		tileArray[t]->show();
	}

	entityManager.drawAll();
}

c_House2::~c_House2()
{	
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		delete tileArray[t];
		tileArray[t] = NULL;
	}

	h2_player = NULL;

	if (h2_enemy != NULL){
		h2_enemy = NULL;
	}

	exit = NULL;
}