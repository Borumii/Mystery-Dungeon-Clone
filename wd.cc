#include "wd.h"

bool WD::discovered = false;

WD::WD()
{
	setDefMod(-5);
	potionType = "WD";
}

void WD::discover()
{
	discovered=true;
}

std::string WD::isDiscovered()
{
	return (discovered ? getPotionType():"");
}
