#include "c_Manor_2F.h"

bool c_Manor_2F::isVisited = false;
bool c_Manor_2F::friendDead = false;

c_Manor_2F::c_Manor_2F(void)
{
	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("manor2floor.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	loadObjects();

	manor_player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
	manor_player->init( (entityManager.get(5)->getX()) + 3, (entityManager.get(5)->getY())- 45 );

	if (manor_2F_enemy != NULL){
		manor_2F_enemy->LEVEL_HEIGHT = this->LEVEL_HEIGHT;
		manor_2F_enemy->LEVEL_WIDTH = this->LEVEL_WIDTH;
	}
	
	isVisited = true;
}

void c_Manor_2F::loadObjects()
{
	std::ifstream map("manor2floor.map");

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

			case 1:{
				manor_player = c_Entity_manager::getPlayer();
				manor_player->init( objX, objY );

				if (c_Entity_manager::getEnemy() != NULL && c_Entity_manager::getEnemy()->isSpawned){
				manor_2F_enemy = c_Entity_manager::getEnemy();
				manor_2F_enemy->init(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
				}
				else{
					manor_2F_enemy = NULL;
				}
			}
			break;
			
			case 2:
			{
				c_Note *note = new c_Note( NOTE_MANOR2, objX, objY );
				entityManager.add_Special(note);
			}
			break;

			case 3:{
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

			case 17:{
				exit = new c_Exit( objX, objY + 35 );
				entityManager.add_Decor( exit->getID(), exit );
			}
			break;

			case 22:{
				if (c_player_Copy::distracted){
				c_crazy_Friend *friend_Crazy= new c_crazy_Friend(objX, objY, "shiveringFriend.txt", "friend-shivering.png");
				entityManager.add("shiveringFriend", friend_Crazy);
				c_Entity_is_movable::unCollidables.push_back(friend_Crazy);
				}
				else{
				c_dead_Friend *friend_Dead= new c_dead_Friend(objX, objY);
				entityManager.add_Decor(friend_Dead->getID(), friend_Dead);
				friendDead = true;
				}
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

void c_Manor_2F::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		manor_player->handleInput();

		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_Manor_2F::logic()
{
	entityManager.logicAll();

	if ( check_collision( manor_player->getBox(), exit->getBox() ) == true )
	{
		set_next_State(STATE_MANOR);
	}
}

void c_Manor_2F::render()
{
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		tileArray[t]->show();
	}

	entityManager.drawAll();
}

c_Manor_2F::~c_Manor_2F()
{	
	for ( int t = 0; t < TOTAL_TILES; t++ )
	{
		delete tileArray[t];
		tileArray[t] = NULL;
	}

	manor_player = NULL;

	if(manor_2F_enemy != NULL){
		manor_2F_enemy = NULL;
	}

	exit = NULL;
}