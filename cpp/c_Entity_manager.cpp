#include "c_Entity_manager.h"
#include <utility>
#include <algorithm>

c_Player* c_Entity_manager::player;
c_Zombie* c_Entity_manager::enemy;

c_Entity_manager::c_Entity_manager(void)
{
	delta.start();
}

void c_Entity_manager::add( std::string name, c_Entity_is_movable* entity)
{
	eList.insert( std::pair<std::string, c_Entity_is_movable*>(name, entity));
}

void c_Entity_manager::add_Decor( int ID, c_Entity* decor )
{
	decorations_list.insert(std::pair<int, c_Entity*>(ID, decor));
}

void c_Entity_manager::add_Special( c_Entity* special )
{
	specials_list.push_back(special);
}

void c_Entity_manager::addPlayer( c_Player* p )
{
	player = p;
}

void c_Entity_manager::addEnemy( c_Zombie *e )
{
	enemy = e;
}

c_Player* c_Entity_manager::getPlayer()
{
	return player;
}

c_Zombie* c_Entity_manager::getEnemy()
{
	return enemy;
}

c_Zombie c_Entity_manager::getEnemycopy()
{
	return *enemy;
}

void c_Entity_manager::remove( std::string name )
{
	std::map<std::string, c_Entity_is_movable*>::iterator results = eList.find( name );
	if ( results != eList.end() )
	{
		delete results->second;
		eList.erase(results);
	}
}

void c_Entity_manager::removeAll()
{
	decorations_list.clear();
	eList.clear();
}

c_Entity_is_movable* c_Entity_manager::get( std::string name ) const
{
	std::map<std::string, c_Entity_is_movable*>::const_iterator results = eList.find( name );
	if ( results == eList.end() )
	{
		return NULL;
	}
	else
		return results->second;
}

c_Entity* c_Entity_manager::get( int ID ) const
{
	std::map<int, c_Entity*>::const_iterator results = decorations_list.find( ID );
	if ( results == decorations_list.end() )
	{
		return NULL;
	}
	else
		return results->second;
}

void c_Entity_manager::drawAll()
{
	std::map<int, c_Entity*>::const_iterator D_itr = decorations_list.begin();
	while ( D_itr != decorations_list.end() ){
		D_itr->second->render();
		D_itr++;
	}
	
	std::map<std::string, c_Entity_is_movable*>::const_iterator itr = eList.begin();
	while ( itr != eList.end() ){
		itr->second->render();
		itr++;
	}

	if (enemy != NULL){
	SDL_Rect a = { enemy->getBox().x - (enemy->getBox().w * 4) - camera.x, enemy->getBox().y - (enemy->getBox().h * 4) - camera.y,
		enemy->getBox().w * 8, enemy->getBox().h * 8 };

		if (check_collision(player->getFlashlight()->holeCircle, a) ){
			enemy->render();
		}
	}

	player->render();
	
	for( int i = 0; i < (int)specials_list.size(); i++){
		SDL_Rect a = {specials_list.at(i)->getBox().x - camera.x, specials_list.at(i)->getBox().y - camera.y, 
			specials_list.at(i)->getBox().w, specials_list.at(i)->getBox().h};

		if ( check_collision(player->getFlashlight()->holeCircle, a) ){
			specials_list.at(i)->render();
		}
	}
}

void c_Entity_manager::logicAll()
{
	player->logic( delta.getTicks() );

	if (enemy != NULL && enemy->isSpawned){
	enemy->logic(delta.getTicks());
	}

	std::map<std::string, c_Entity_is_movable*>::const_iterator itr = eList.begin();
	while ( itr != eList.end() ){
		itr->second->logic( delta.getTicks() );
		itr++;
	}

	std::map<int, c_Entity*>::const_iterator D_itr = decorations_list.begin();
	while ( D_itr != decorations_list.end() ){
		D_itr->second->logic();
		++D_itr;
	}

	for (int i = 0; i < specials_list.size(); i++){
		specials_list.at(i)->logic();
	}
	
	delta.start();
}

c_Entity_manager::~c_Entity_manager(void)
{
	std::for_each( eList.begin(), eList.end(), entityDeallocater() );
	std::for_each( decorations_list.begin(), decorations_list.end(), decorDeallocater() );
	specials_list.clear();

	for(int i = 0; i < specials_list.size(); i++){
		delete specials_list.at(i);
		specials_list.at(i) = NULL;
	}

	c_Door::resetCount();
	c_Wall::resetCount();
	c_House::resetCount();
	c_Entity_is_movable::resetunWalkables();
	c_Entity_is_movable::resetunCollidables();
	c_Entity::resetdecorCount();
	c_Exit::resetExits();
	c_Fire::resetCount();
	c_Note::resetCount();
}
