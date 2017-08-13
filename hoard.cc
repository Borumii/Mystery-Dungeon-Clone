#include <memory>
#include "hoard.h"

using namespace std;

Hoard::Hoard(): Gold(6){
	pickable = false;
}

bool Hoard::getPickable()
{
	updatePickable();
	return pickable;
}

void Hoard::updatePickable()
{
	pickable = dragon->getHp() == 0;
	if(pickable) setDragon(nullptr);
}

void Hoard::setDragon(shared_ptr<Dragon> new_Dragon)
{
	dragon = new_Dragon;
}

