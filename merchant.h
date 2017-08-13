#ifndef MERCHANT_H
#define MERCHANT_H

#include "monster.h"

// they all become hostile after one getting attacked

class Merchant: public Monster{
		static bool hostile;
	public:
		Merchant();
		void getAttacked(Creature &other);
		bool isHostile();
		void setHostile();
};

#endif




