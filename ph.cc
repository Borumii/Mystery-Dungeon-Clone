#include "ph.h"

using namespace std;

bool PH::discovered = false;

PH::PH()
{
	setHPMod(-10);
	potionType = "PH";
}

void PH::discover()
{
	discovered=true;
}

std::string PH::isDiscovered()
{
	return (discovered ? getPotionType():"");
}


