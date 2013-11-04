#include "c_States.h"

c_Intro::c_Intro(void)
{
}

void c_Intro::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_Intro::logic()
{
}

void c_Intro::render()
{
}

c_Intro::~c_Intro(void)
{
}

c_stageOne::c_stageOne(void)
{
	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("stageThree.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	loadObjects();
	I_Audio_system::playMUS("scary.wav");

	player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
	enemy = NULL;

	narrator = c_dialog_System();

	exit.x = (TILE_WIDTH*3);
	exit.y = 0;
	exit.w = (TILE_WIDTH*2);
	exit.h = 5;
}

c_stageOne::c_stageOne(gameStates prevState)
{
	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("stageThree.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);

	loadObjects();

	switch (prevState)
	{
		case STATE_HOUSE1: player->init( (entityManager.get(0)->getBox().x + DOOR_X_BUFFER), 
							   (entityManager.get(0)->getBox().y + entityManager.get(0)->getBox().h + DOOR_Y_BUFFER) );
			break;

		case STATE_HOUSE2: player->init( (entityManager.get(1)->getBox().x + DOOR_X_BUFFER), 
							   (entityManager.get(1)->getBox().y + entityManager.get(1)->getBox().h + DOOR_Y_BUFFER) ); 
			break;

		case STATE_STORE: player->init( (entityManager.get(2)->getBox().x + DOOR_X_BUFFER), 
							   (entityManager.get(2)->getBox().y + entityManager.get(2)->getBox().h + DOOR_Y_BUFFER) );
			break;

		case STATE_MANOR: player->init( (entityManager.get(3)->getBox().x + DOOR_X_BUFFER), 
						   (entityManager.get(3)->getBox().y + entityManager.get(3)->getBox().h + DOOR_Y_BUFFER) );
			break;
	};
	
	player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);

	narrator = c_dialog_System();
	I_Audio_system::playSound("doorClose.wav");

	exit.x = (TILE_WIDTH*3);
	exit.y = 0;
	exit.w = (TILE_WIDTH*2);
	exit.h = 5;

	if (enemy != NULL){
		enemy->LEVEL_HEIGHT = this->LEVEL_HEIGHT;
		enemy->LEVEL_WIDTH = this->LEVEL_WIDTH;
	}
}

void c_stageOne::loadObjects()
{
	std::ifstream map("stageThree.map");

	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
	map.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );

	while ( !map.eof() )
		{
			int objType = -1;
			
			int objX, objY = 0;

			map >> objType;
			map >> objX; map >> objY;

			/*enemy only spawns in overworld, so there's no need for his objType to be in other states*/
			switch (objType){
			case 0:
			{
				if (c_Entity_manager::getEnemy() == NULL && c_Manor_2F::isVisited){
					c_Zombie *zombie;

					if (c_Manor_2F::friendDead){
						zombie = new c_Zombie(objX, objY, INCREASED_VEL);
					}
					else{
						zombie = new c_Zombie(objX, objY);
					}

					zombie->isSpawned = true;
					entityManager.addEnemy(zombie);

					enemy = zombie;
				}
				else if (c_Entity_manager::getEnemy() != NULL && c_Entity_manager::getEnemy()->isSpawned){
					enemy = c_Entity_manager::getEnemy();
				}
				else{
					enemy = NULL;
				}
			}
			break;
			
			case 1:
			{
				if (c_Entity_manager::getPlayer() == NULL){
				player = new c_Player(objX, objY);
				player_ptr = player;
				c_Entity_manager::addPlayer(player);
				}

				else
					player = c_Entity_manager::getPlayer();
			}
			break;

			case TREE:
			{
			c_Entity *decor = new c_Entity(objX, objY, 
				TREE_WIDTH, TREE_HEIGHT, "tree.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
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

			/*house parts*/
			case 4:
			{
				c_House *houseNW = new c_House( objX, objY, ROOF_NORTHWEST );
				entityManager.add_Decor( houseNW->getID(), houseNW );

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

			case 5:
			{
				c_House *houseML = new c_House( objX, objY, ROOF_MIDDLELEFT );
				entityManager.add_Decor( houseML->getID(), houseML );

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

			case 6:
			{
				c_House *houseMR = new c_House( objX, objY, ROOF_MIDDLERIGHT );
				entityManager.add_Decor( houseMR->getID(), houseMR );

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

			case 7:
			{
				c_House *houseNE = new c_House( objX, objY, ROOF_NORTHEAST );
				entityManager.add_Decor( houseNE->getID(), houseNE );

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

			case 8:
			{
				c_House *houseMW = new c_House( objX, objY, MIDDLE_WEST );
				entityManager.add_Decor( houseMW->getID(), houseMW );

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

			case 9:
			{
				c_House *houseMML = new c_House( objX, objY, MIDDLE_MIDDLELEFT );
				entityManager.add_Decor( houseMML->getID(), houseMML );

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

			case 10:
			{
				c_House *houseMMR = new c_House( objX, objY, MIDDLE_MIDDLERIGHT );
				entityManager.add_Decor( houseMMR->getID(), houseMMR );

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

			case 11:
			{
				c_House *houseE = new c_House( objX, objY, MIDDLE_EAST );
				entityManager.add_Decor( houseE->getID(), houseE );

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

			case 12:
			{
				c_House *houseBSW = new c_House( objX, objY, BOTTOM_SOUTHWEST );
				entityManager.add_Decor( houseBSW->getID(), houseBSW );

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

			case 13:
			{
				c_House *houseBML = new c_House( objX, objY, BOTTOM_MIDDLELEFT );
				entityManager.add_Decor( houseBML->getID(), houseBML );

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

			case 14:
			{
				c_House *houseBMR = new c_House( objX, objY, BOTTOM_MIDDLERIGHT );
				entityManager.add_Decor( houseBMR->getID(), houseBMR );

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

			case 15:
			{
				c_House *houseBSE = new c_House( objX, objY, BOTTOM_SOUTHEAST );
				entityManager.add_Decor( houseBSE->getID(), houseBSE );

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
				/*h1 door will be ID 0, h2 door will be ID 1, general store will be ID 2, manor will be ID 3*/
				c_Door_h1 *door = new c_Door_h1( objX, objY );
				entityManager.add_Decor( door->getID(), door );
			}
			break;

			case 17:{
				c_Door_h2 *door = new c_Door_h2( objX, objY );
				entityManager.add_Decor( door->getID(), door );
			}
			break;

			case 18:{
				c_Door_store *door = new c_Door_store( objX, objY );
				entityManager.add_Decor( door->getID(), door );
			}
			break;

			case 19:{
				c_Door_manor *door = new c_Door_manor( objX, objY );
				entityManager.add_Decor( door->getID(), door );
			}
			break;

			case 20:{
				c_Fire *fire = new c_Fire( objX, objY );
				entityManager.add( "fire"+fire->getID(), fire );
				c_Entity_is_movable::unCollidables.push_back(fire);
			}
			break;

			case 21:{
				c_Entity *decor = new c_Entity(objX, objY, 
					STORE_SIGN_WIDTH, STORE_SIGN_HEIGHT, "store-sign.png");
				entityManager.add_Decor( c_Entity::decorCount++, decor );
			}
	}
}

	map.close();
}

void c_stageOne::handleInput()
{
	while ( SDL_PollEvent( &event ) )
	{
		player->handleInput();

		if ( event.type == SDL_QUIT )
		{
			running = false;
		}
	}
}

void c_stageOne::logic()
{
	entityManager.logicAll();

	if ( check_collision(entityManager.get(0)->getBox(), player->getBox()) ){
		set_next_State( STATE_HOUSE1 );
	}

	else if ( check_collision(entityManager.get(1)->getBox(), player->getBox()) ){
		set_next_State( STATE_HOUSE2 );
	}

	else if ( check_collision(entityManager.get(2)->getBox(), player->getBox()) ){
		set_next_State( STATE_STORE );
	}

	else if (check_collision(entityManager.get(3)->getBox(), player->getBox()) ){
		set_next_State( STATE_MANOR );
	}

	else if (check_collision(exit, player->getBox()) && c_Manor_2F::isVisited){
		set_next_State(STATE_GAMEWIN_WITH_FRIEND);
	}

	else if (check_collision(exit, player->getBox()) && !c_Manor_2F::isVisited){
		narrator.setMessage( "No point in turning back now..." );
	}

	else
		narrator.setMessage("");

	if (enemy != NULL){
		narrator.setMessage("You feel a cold wind through the air...");
	}
}

void c_stageOne::render()
{
	for (int t = 0; t < TOTAL_TILES; t++)
	{
		tileArray[t]->show();
	}

	entityManager.drawAll();
	narrator.render();
}

c_stageOne::~c_stageOne(void)
{
	for (int i = 0; i < TOTAL_TILES; i++){
		delete tileArray[i];
		tileArray[i] = NULL;
	}
}

