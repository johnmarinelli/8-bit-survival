#include "c_Store.h"

c_Store::c_Store(gameStates prevState)
{
	I_Audio_system::playSound("doorOpen.wav");

	entityManager = c_Entity_manager();
	tileArray = c_Tile::loadTiles("emptyStore.map", TOTAL_TILES, LEVEL_WIDTH, LEVEL_HEIGHT);
	loadObjects();
	
	extensionDoor.x = 0;
	extensionDoor.y = LEVEL_HEIGHT/4;
	extensionDoor.w = 1;
	extensionDoor.h = HIDDEN_DOOR_HEIGHT;

	switch (prevState)
	{
	case STATE_OVERWORLD:{ store_player->init( (entityManager.get(5)->getX()) + 3, (entityManager.get(5)->getY())- 45 ); }break;
	case STATE_STORE_EXTENSION: store_player->init(extensionDoor.x + SPRITE_WIDTH/2, extensionDoor.y); break;
	}

	if (!initStereo()){
		return;
	}

	store_player->setLevel(LEVEL_WIDTH, LEVEL_HEIGHT);

	if (store_enemy != NULL){
		store_enemy->LEVEL_HEIGHT = this->LEVEL_HEIGHT;
		store_enemy->LEVEL_WIDTH = this->LEVEL_WIDTH;
	}
}

bool c_Store::initStereo()
{
	store_stereo = new c_Stereo();

	if (store_stereo == NULL){
		return false;
	}

	if (store_player->deadfriend_visited == false){
	/*top right*/
	sound1.x = LEVEL_WIDTH - 1;
	sound1.y = LEVEL_HEIGHT/4;
	sound1.w = SOUNDBOX_SIDE;
	sound1.h = SOUNDBOX_SIDE;

	/*bottom right*/
	sound2.x = LEVEL_WIDTH - 1;
	sound2.y = LEVEL_HEIGHT - (LEVEL_HEIGHT/4);
	sound2.w = SOUNDBOX_SIDE;
	sound2.h = SOUNDBOX_SIDE;

	/*top*/
	sound3.x = LEVEL_WIDTH/2;
	sound3.y = 0;
	sound3.w = SOUNDBOX_SIDE;
	sound3.h = SOUNDBOX_SIDE;

	/*top left, true sound*/
	trueSound.x = 0;
	trueSound.y = LEVEL_HEIGHT/4;
	trueSound.w = SOUNDBOX_SIDE;
	trueSound.h = SOUNDBOX_SIDE;

	/*bottom left*/
	sound4.x = 0;
	sound4.y = LEVEL_HEIGHT - (LEVEL_HEIGHT/4);
	sound4.w = SOUNDBOX_SIDE;
	sound4.h = SOUNDBOX_SIDE;

	store_stereo->loadSFX("101389__dobroide__20100711-wrathful-loony.wav", "wrathfulLoony");
	store_stereo->loadSFX("79776__engreitz__thatsmylaugh.wav", "talkingLaughter");
	store_stereo->loadSFX("123678__timbre__tv-in-next-room-simulation-muffled.wav", "tv");
	store_stereo->loadSFX("94733__ttiimm54__heavy-breathes(1).wav", "friendBreathing");
	store_stereo->loadSFX("86568__uair01__tilburg-kusjes-doeidoei.wav", "conversations");

	store_stereo->play_distanceSFX("wrathfulLoony", store_player->getBox().x, store_player->getBox().y,
		sound1.x, sound1.y, SOUND1_CHANNEL);

	store_stereo->play_distanceSFX("talkingLaughter", store_player->getBox().x, store_player->getBox().y,
		sound2.x, sound2.y, SOUND2_CHANNEL);

	store_stereo->play_distanceSFX("tv", store_player->getBox().x, store_player->getBox().y,
		sound3.x, sound3.y, SOUND3_CHANNEL);

	store_stereo->play_distanceSFX("friendBreathing", store_player->getBox().x, store_player->getBox().y,
		trueSound.x, trueSound.y, TRUESOUND_CHANNEL);

	store_stereo->play_distanceSFX("conversations", store_player->getBox().x, store_player->getBox().y,
		sound4.x, sound4.y, SOUND4_CHANNEL);
	}
	
	else{
		/*play shh*/
	}

	return true;
}

void c_Store::loadObjects()
{
	std::ifstream map("emptyStore.map");

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
				c_Zombie *zombie = new c_Zombie( objX, objY );
				entityManager.add( "Zombie", zombie );
			}
			break;

			case 1:
			{
				store_player = c_Entity_manager::getPlayer();
				store_player->init( objX, objY );

				if (c_Entity_manager::getEnemy() != NULL && c_Entity_manager::getEnemy()->isSpawned){
				store_enemy = c_Entity_manager::getEnemy();
				store_enemy->init(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);
				}
				else{
					store_enemy = NULL;
				}
			}
			break;

			case 2:{
				c_Note* note = new c_Note(NOTE_1_STORE, objX, objY);
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
				exit = new c_Exit( objX, (objY + 35) );
				entityManager.add_Decor( exit->getID(), exit );
			}
			break;

			case 23:{
			c_dead_Friend *friend_Dead= new c_dead_Friend( objX, objY );
			entityManager.add_Decor( friend_Dead->getID(), friend_Dead );
			c_Entity_is_movable::unCollidables.push_back( friend_Dead );
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
			}
			break;

			case ENTITY_STORE_SHELF_1:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				STORE_SHELF_WIDTH, STORE_SHELF_HEIGHT, "store-shelves.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_STORE_CHECKOUT:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				STORE_CHECKOUT_WIDTH, STORE_CHECKOUT_HEIGHT, "store-checkout.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_STORE_SHELF_2:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				STORE_SHELF_WIDTH, STORE_SHELF_HEIGHT, "store-shelves2.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;

			case ENTITY_STORE_SHELF_3:
			{
			c_Entity *decor = new c_Entity(objX, objY,
				STORE_SHELF_WIDTH, STORE_SHELF_HEIGHT, "store-shelves3.png");
			entityManager.add_Decor( c_Entity::decorCount++, decor );
			c_Entity_is_movable::unCollidables.push_back(decor);
			}
			break;
		}
	}

	map.close();
}

void c_Store::handleInput()
{
	while ( SDL_PollEvent(&event ))
	{
		store_player->handleInput();

		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}
}

void c_Store::logic()
{
	entityManager.logicAll();
	
	if(!store_player->deadfriend_visited){
	update_stereo_Position();
	}

	if (check_collision( store_player->getBox(), exit->getBox()) == true ){
		set_next_State(STATE_OVERWORLD);
	}

	else if (check_collision( store_player->getBox(), extensionDoor) == true ){
		set_next_State(STATE_STORE_EXTENSION);
	}
}

void c_Store::update_stereo_Position()
{
	store_stereo->updatePosition(store_player->getBox().x, store_player->getBox().y, sound1.x, sound1.y, SOUND1_CHANNEL);
	store_stereo->updatePosition(store_player->getBox().x, store_player->getBox().y, sound2.x, sound2.y, SOUND2_CHANNEL);
	store_stereo->updatePosition(store_player->getBox().x, store_player->getBox().y, sound3.x, sound3.y, SOUND3_CHANNEL);
	store_stereo->updatePosition(store_player->getBox().x, store_player->getBox().y, trueSound.x, trueSound.y, TRUESOUND_CHANNEL);
	store_stereo->updatePosition(store_player->getBox().x, store_player->getBox().y, sound4.x, sound4.y, SOUND4_CHANNEL);
}

void c_Store::render()
{
	for (int t = 0; t < TOTAL_TILES; t++)
	{
		tileArray[t]->show();
	}

	entityManager.drawAll();
}

c_Store::~c_Store()
{	
	for (int t = 0; t < TOTAL_TILES; t++){
		delete tileArray[t];
		tileArray[t] = NULL;
	}

	if (store_enemy != NULL){
		store_enemy = NULL;
	}

	if (store_stereo != NULL){
		delete store_stereo;
		store_stereo = NULL;
	}

	store_player = NULL;
	exit = NULL;
}