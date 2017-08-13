#include "bd.h"

bool BD::discovered = false;

BD::BD()
{
	setDefMod(5);
	potionType = "BD";
}

void BD::discover()
{
	discovered=true;
}

std::string BD::isDiscovered()
{
	return (discovered ? getPotionType():"");
}

