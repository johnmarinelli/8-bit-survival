#pragma once
#include "c_Player.h"
#include "c_Friend.h"
#include "c_Shovel.h"
#include "c_Door.h"
#include "c_Wall.h"
#include "c_House.h"
#include "c_Zombie.h"
#include "c_Exit.h"
#include "c_Fire.h"
#include "c_Note.h"
#include "c_player_Copy.h"
#include "c_Piano.h"
#include "timer.h"
#include <map>
#include <string>
#include <vector>

class c_Entity_manager
{
private:
	std::map<std::string, c_Entity_is_movable*> eList;
	std::map<int, c_Entity*> decorations_list;
	std::vector<c_Entity*> specials_list;

	static c_Player* player;
	static c_Zombie* enemy;

	timer delta;

	struct entityDeallocater
	{
		void operator() (
			const std::pair<std::string, c_Entity_is_movable*> &p ) const
		{
			delete p.second;
		}
	};

	struct decorDeallocater
	{
		void operator() ( const std::pair<int, c_Entity*> &p ) const
		{
			delete p.second;
		}
	};

public:
	c_Entity_manager(void);
	~c_Entity_manager(void);

	void add( std::string name, c_Entity_is_movable* entity );
	void add_Decor( int ID, c_Entity* decor );
	void add_Special( c_Entity* special );

	static void addPlayer( c_Player *p );
	static void addEnemy( c_Zombie *e );

	static c_Player* getPlayer();
	static c_Zombie* getEnemy();
	static c_Zombie getEnemycopy();

	void remove(std::string name);
	void removeAll();

	int getCount() const;
	c_Entity_is_movable* get( std::string name ) const;
	c_Entity* get( int ID ) const;

	void drawAll();
	void logicAll();
};

