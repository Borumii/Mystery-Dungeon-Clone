#ifndef _RHH_
#define _RHH_

#include "potion.h"


class RH: public Potion
{
		static bool discovered;
	public:
		RH();
		void discover();
		std::string isDiscovered();

};

#endif

