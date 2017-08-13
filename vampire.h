#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "hero.h"

// gains 5 HP every successful attack and has no maximum HP (implemented)

class Vampire: public Hero{
	public:
		Vampire();
		bool attack(Creature &other);

};

#endif


