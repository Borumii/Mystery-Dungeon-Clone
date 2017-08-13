#include "gold.h"

Gold::Gold(int v): Item('G'), value(v) {}

int Gold::getValue(){
	return value;
}

bool Gold::getPickable()
{
	return pickable;
}

