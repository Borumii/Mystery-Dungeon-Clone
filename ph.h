#ifndef _PHH_
#define _PHH_

#include "potion.h"


class PH: public Potion
{
		static bool discovered;
	public:
		PH();
		void discover();
		std::string isDiscovered();

};

#endif

