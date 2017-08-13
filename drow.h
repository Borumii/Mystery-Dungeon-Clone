#ifndef DROW_H
#define DROW_H

#include "hero.h"

// all potions have their effect magnified by 1.5 (implemented)

class Drow: public Hero{
	public:
		Drow();
		void applyPotion(Potion &potion);
};

#endif


