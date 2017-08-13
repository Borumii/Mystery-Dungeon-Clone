#ifndef _WAH_
#define _WAH_

#include "potion.h"


class WA : public Potion
{
		static bool discovered;
	public:
		WA();
		void discover();
		std::string isDiscovered();
};

#endif

