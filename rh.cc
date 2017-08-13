#include "rh.h"

bool RH::discovered = false;

RH::RH()
{
	setHPMod(10);
	potionType = "RH";
}

void RH::discover()
{
	discovered=true;
}

std::string RH::isDiscovered()
{
	return (discovered ? getPotionType():"");
}

