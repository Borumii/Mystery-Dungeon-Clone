#include <cstdlib>
#include <cmath>
#include "halfling.h"

using namespace std;

Halfling::Halfling(): Enemy(100, 15, 20, "Halfling", 'L'){
}

void Halfling::getAttacked(Creature &other){
	
	if(rand() % 2) return;
	
	setHp(getHp() - ceil((100/(100.0 + getCurrentDef())) * other.getCurrentAtk()));
}


