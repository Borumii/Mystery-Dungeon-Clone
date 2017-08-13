#ifndef HALFLING_H
#define HALFLING_H

#include "enemy.h"

// has a 50% chance to cause the player character to miss in combat (implemented)

class Halfling: public Enemy{
	public:
		Halfling();
		void getAttacked(Creature &other);
};

#endif


