#include "dragon.h"
#include <memory>
#include "hoard.h"
#include <cmath>

using namespace std;

Dragon::Dragon(): Enemy(150, 20, 20, "Dragon", 'D', 0){
	setSpeed(0);
}

void Dragon::setHoard(shared_ptr<Hoard> new_hoard){
	hoard = new_hoard;
}

shared_ptr<Hoard> Dragon::getHoard(){
	return hoard;
}

void Dragon::getAttacked(Creature &other){

	setHp(getHp() - ceil((100/(100.0 + getCurrentDef())) * other.getCurrentAtk()));
	
	if(getHp() == 0)
	{
		getHoard()->updatePickable();
	}
}

void Dragon::kill(){
	setHp(0);
	getHoard()->updatePickable();
}


