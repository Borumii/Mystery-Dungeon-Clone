#ifndef _BAH_
#define _BAH_

#include "potion.h"


class BA : public Potion
{
		static bool discovered;
	public:
		BA();
		void discover();
		std::string isDiscovered();
};

#endif

