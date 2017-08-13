#include <cmath>
#include <string>
#include <iostream>
#include "goblin.h"
#include "achievement.h"

using namespace std;

Goblin::Goblin(): Hero(110, 15, 20, "Goblin"){
}

bool Goblin::attack(Creature &other){

	Achievement::combatevents++;
		
	other.getAttacked(*this);

	if(getSymbol() == '@')
	{
		Hero d = dynamic_cast<Hero&>(*this);

		if(other.getHp() == 0)
			d.addAction("You killed enemy " + other.getRaceName() + ".");
		else
			d.addAction("You attacked enemy " + other.getRaceName() + " (" + to_string(other.getHp()) +" hp left).");
		Achievement::checkRacist(other.getRaceName());
	}
	
	if(other.getHp() == 0)
	{
		if(other.getRaceName() == "Halfling")
		{
			Achievement::toggle("Bully");
		}
		if(other.getRaceName() == "Dragon")
		{
			Achievement::toggle("Dragon Slayer");
		}
		if(other.getRaceName() == "Dwarf" && getRaceName() == "Vampire")
		{
			Achievement::toggle("Reckless");
		}
		setGold(getGold() + other.getGold() + 5);	// Goblin's special ability
		return true;
	}
	
	return false;
}

void Goblin::getAttacked(Creature &other){

	if(getSymbol() == '@')
		Achievement::damagetaken = true;

	setHp(getHp() - ceil((100/(100.0 + getCurrentDef())) * other.getCurrentAtk() * ((other.getRaceName().compare("Orc")) ? 1:1.5)));// Orc's special ability
}


