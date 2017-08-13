#include <string>
#include <cstdlib>
#include <iostream>
#include "monster.h"
#include <cmath>
#include "info.h"
#include "dragon.h"
#include "hero.h"

using namespace std;

bool Monster::tracking = false;
double Monster::multiplier = 1;

Monster::Monster(int new_hp, int new_atk, int new_def, string new_raceName, char new_symbol, int new_gold): Creature(new_hp * multiplier , new_atk * multiplier , new_def * multiplier, new_raceName, new_symbol, new_gold){
}

Monster::Monster(int new_hp, int new_atk, int new_def, string new_raceName, char new_symbol): Creature(new_hp * multiplier , new_atk * multiplier , new_def * multiplier, new_raceName, new_symbol, 1 + rand() % 2){
}

bool Monster::attack(Creature &other){
	
	Hero d = dynamic_cast<Hero&>(other);
		
	if((!getRaceName().compare("Merchant") && !isHostile()))
	{
		return false;
	}
	
	if(rand() % 2)
		other.getAttacked(*this);
	else{
		d.addAction("You were missed by a " + getRaceName() + ".");
		return false;	
	}
	
	d.addAction("You were attacked by a " + getRaceName() + ".");

	if(other.getHp() == 0)
	{
		return true;
	}

	return false;
}

Info Monster::action(Hero &h)
{	
	if(abs(getX() - h.getX()) <= 1 && abs(getY() - h.getY()) <= 1)
	{
		attack(h);
		return Info{-1,-1};
	}
	else if(getSymbol() == 'D')
	{	
		Dragon d = dynamic_cast<Dragon&>(*this);

		if(abs(d.getHoard()->getX() - h.getX()) <= 1 && abs(d.getHoard()->getY() - h.getY()) <= 1)
		{
			d.attack(h);
			return Info{-1,-1};
		}
	}

	int offsetX, offsetY;
	offsetX = offsetY = 0;

	if(tracking && isHostile() && (h.getRoomID() == getRoomID()))
	{
		offsetX = (h.getX() > getX()) ? 1:((h.getX() < getX())? -1:0);
		offsetY = (h.getY() > getY()) ? 1:((h.getY() < getY())? -1:0);
	}
	else
	{	
		for(int i = 0; i < getSpeed(); i++)
		{
			int r = rand() % 8;
			switch(r)
			{
				case 0: offsetX++; offsetY++; break;
				case 1: offsetX++; break;
				case 2: offsetX++; offsetY--; break;
				case 3: offsetY++; break;
				case 4: offsetY--; break;
				case 5: offsetX--; offsetY++; break;
				case 6: offsetX--; offsetY--; break;
				case 7: offsetX--; break;
			}
		}
	}
	return Info{getX() + offsetX, getY() + offsetY};
	
}

void Monster::enableTracking(){
	tracking = true;
}
void Monster::disableTracking(){
	tracking = false;
}

void Monster::enableChallengeMode(double new_multiplier){
	multiplier = new_multiplier;
}

void Monster::disableChallengeMode(){
	multiplier = 1;
}

bool Monster::isTracking(){
	return tracking;
}


