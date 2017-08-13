#ifndef _BDH_
#define _BDH_

#include "potion.h"


class BD : public Potion
{
		static bool discovered;
	public:
		BD();
		void discover();
		std::string isDiscovered();
};

#endif

