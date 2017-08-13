#ifndef DRAGON_H
#define DRAGON_H

#include <memory>
#include "enemy.h"
#include "hoard.h"

// always guards a treasure hoard

class Hoard;

class Dragon: public Enemy {
		std::shared_ptr<Hoard> hoard;
	public:
		Dragon();
		std::shared_ptr<Hoard> getHoard();
		void getAttacked(Creature &other);
		void kill();
		void setHoard(std::shared_ptr<Hoard> new_hoard);
};

#endif


