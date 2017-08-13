#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <memory>

#include "creature.h"
#include "info.h"
#include "hero.h"



class Monster: public Creature{
		static bool tracking;
		static double multiplier;
	public:
		Monster(int new_hp, int new_atk, int new_def, std::string new_raceName, char new_symbol, int new_gold);
		Monster(int new_hp, int new_atk, int new_def, std::string new_raceName, char new_symbol);
		virtual bool attack(Creature &other);
		Info action(Hero &h);
		static void enableTracking();
		static void disableTracking();
		static void enableChallengeMode(double new_multiplier);
		static void disableChallengeMode();
		static bool isTracking();
};

#endif

	

