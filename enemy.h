#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "monster.h"

class Enemy: public Monster{
	public:
		Enemy(int new_hp, int new_atk, int new_def, std::string new_raceName, char new_symbol, int new_gold);
		Enemy(int new_hp, int new_atk, int new_def, std::string new_raceName, char new_symbol);
};

#endif


