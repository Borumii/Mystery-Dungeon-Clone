#include <cmath>
#include "merchant.h"

using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant(): Monster(30, 70, 5, "Merchant", 'M', 4){
}

void Merchant::getAttacked(Creature &other){

	setHp(getHp() - ceil((100/(100.0 + getCurrentDef())) * other.getCurrentAtk()));
	
	setHostile();
}

bool Merchant::isHostile(){
	return hostile;
}

void Merchant::setHostile(){
	hostile = true;
}


