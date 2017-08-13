#ifndef _WDH_
#define _WDH_

#include "potion.h"


class WD : public Potion
{
		static bool discovered;
	public:
		WD();
		void discover();
		std::string isDiscovered();
};

#endif

