#ifndef HOARD_H
#define HOARD_H

#include <memory>
#include "gold.h"
#include "dragon.h"

class Dragon;

class Hoard: public Gold{
		std::shared_ptr<Dragon> dragon;
	public:
		Hoard();
        ~Hoard() = default;
		bool getPickable();
		void updatePickable();
		void setDragon(std::shared_ptr<Dragon> dragon);
};

#endif


