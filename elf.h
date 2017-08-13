#ifndef ELF_H
#define ELF_H

#include "enemy.h"

// gets two attacks against every race except drow (implemented)

class Elf: public Enemy{
	public:
		Elf();
		bool attack(Creature &other);
};

#endif


