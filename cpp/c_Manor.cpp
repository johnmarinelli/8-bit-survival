#include "c_Manor.h"

c_Manor::c_Manor(gameStates prevState)
{
	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("manor.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	loadObjects();

	if (prevState == STATE_OVERWORLD){
		manor_player->init( (entityManager.get(5)->getBox().x + DOOR_X_BUFFER), (entityManager.get(5)->getBox().y - (DOOR_Y_BUFFER*3)) ); 
		I_Audio_system::playSound("doorOpen.wav");
	}

	else if (prevState == STATE_MANOR2F){
		manor_player->init( (entityManager.get(0)->getBox().x + DOOR_X_BUFFER), (entityManager.get(0)->getBox().y + entityManager.get(0)->getBox().h + DOOR_Y_BUFFER) );
	}

	manor_player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
	
	if ( manor_enemy != NULL ){
		manor_enemy->LEVEL_HEIGHT = LEVEL_HEIGHT;
		manor_enemy->LEVEL_WIDTH = LEVEL_WIDTH;
		manor_enemy->init(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
	}
}

void c_Manor::loadObjects()
{
	std::ifstream map("manor.map");

	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );

	while ( !map.eof() )
		{
			int objType = -1;
			
			int objX, objY = 0;

			map >> objType;
			map >> objX; map >> objY;

			switch(objType){
			case 0:
			{
				c_Zombie *zombie = new c_Zombie( objX, objY );
				entityManager.add( "Zombie", zombie );
			}
			break;

			case 1:
			{
				manor_player = c_Entity_manager::getPlayer();
				
				if (c_Entity_manager::getEnemy() != NULL && c_Entity_manager::getEnemy()->isSpawned){
					manor_enemy = c_Entity_manager::getEnemy();
					manor_enemy->init(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
				}
				else if(c_Entity_manager::getEnemy() != NULL && !c_Entity_manager::getEnemy()->isSpawned){
					manor_enemy = NULL;
				}
				else
					manor_enemy = NULL;
			}
			break;

			case 2:
			{
				/*c_Shovel *shovelSprite = new c_Shovel( objX, objY );
				entityManager.add_Decor( shovelSprite->getID(), shovelSprite );
				*/
				//TODO: TREE
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
				exit = new c_Exit(objX + 5, objY + 35);
				entityManager.add_Decor(exit->getID(), exit);
			}
			break;

			case 18:
			{
				upStairs = new c_Upstairs_manor(objX, objY);
				entityManager.add_Decor( upStairs->getID(), upStairs );
			}
			break;

			case 19:
			{
				if(!c_Manor_2F::isVisited){
				manor_copy = new c_player_Copy( objX, objY, (gameStates)stateID );
				entityManager.add("playerCopy", manor_copy);
				}
				else
					manor_copy = NULL;
			}
			break;

			case 20:
			{
				piano = new c_Piano(objX, objY);
				entityManager.add_Decor( piano->pianoID, piano );
				c_Entity_is_movable::unCollidables.push_back(piano);
			}
			break;

			case 21:
			{
				c_Note* note = new c_Note(NOTE_MANOR, objX, objY);
				entityManager.add_Special(note);
			}
			break;

			case ENTITY_CRATE_TALL:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				CRATE_TALL_WIDTH, CRATE_TALL_HEIGHT, "crate-tall.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

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

void c_Manor::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		piano->handleInput();
		manor_player->handleInput();

		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_Manor::logic()
{
	entityManager.logicAll();

	if ( check_collision( manor_player->getBox(), exit->getBox() ) == true ){
		set_next_State( STATE_OVERWORLD );
	}

	else if ( check_collision( manor_player->getBox(), upStairs->getBox() ) == true ){
		set_next_State( STATE_MANOR2F );
	}
}

void c_Manor::render()
{
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		tileArray[t]->show();
	}

	entityManager.drawAll();
}

c_Manor::~c_Manor()
{	
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		delete tileArray[t];
		tileArray[t] = NULL;
	}

	manor_player = NULL;

	if (manor_enemy != NULL){
		manor_enemy = NULL;
	}

	if (manor_copy != NULL){
		manor_copy = NULL;
	}

	piano = NULL;
	upStairs = NULL;
	exit = NULL;
}
