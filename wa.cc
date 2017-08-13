#include "wa.h"

bool WA::discovered = false;

WA::WA()
{
	setAtkMod(-5);
	potionType = "WA";
}

void WA::discover()
{
	discovered=true;
}

std::string WA::isDiscovered()
{
	return (discovered ? getPotionType():"");
}

