#ifndef GOBLIN_H
#define GOBLIN_H

#include "hero.h"

// steals 5 gold from every slain enemy (implemented)

class Goblin: public Hero{
	public:
		Goblin();
		bool attack(Creature &other);
		void getAttacked(Creature &other);

};

#endif


