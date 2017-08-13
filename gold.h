#ifndef GOLD_H
#define GOLD_H

#include "item.h"

class Gold: public Item{
		int value;
	protected:
		bool pickable = true;
	public:
		Gold(int v);
        virtual ~Gold() = default;
		int getValue();
		bool getPickable();
};

#endif


