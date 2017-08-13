#include "ba.h"

bool BA::discovered = false;

BA::BA()
{
	setAtkMod(5);
	potionType = "BA";
}

void BA::discover()
{
	discovered=true;
}

std::string BA::isDiscovered()
{
	return (discovered ? getPotionType():"");
}
