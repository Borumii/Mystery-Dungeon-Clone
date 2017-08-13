#include <string>
#include "vampire.h"
#include "achievement.h"

using namespace std;

Vampire::Vampire(): Hero(50, 25, 25, "Vampire"){
}

bool Vampire::attack(Creature &other){
	
	int hpbefore = other.getHp();
	other.getAttacked(*this);
	int hpafter = other.getHp();


	Achievement::combatevents++;

	if(getSymbol() == '@')
	{
		Hero d = dynamic_cast<Hero&>(*this);

		if(other.getHp() == 0)
			d.addAction("You killed enemy " + other.getRaceName() + ".");
		else
			d.addAction("You attacked enemy " + other.getRaceName() + " (" + to_string(other.getHp()) +" hp left).");
		Achievement::checkRacist(other.getRaceName());
	}
	
	// Vampire's special ability
	if(!other.getRaceName().compare("Dwarf"))		// Dwarf's special ability
	{
		setMax_hp(getMax_hp() - 5);
		setHp(getHp() - 5);
		if(getHp() == 0)
		{
			//score.print(false);
		}
	}
	else
	{	
		if(hpbefore == hpafter)
		{
			setMax_hp(getMax_hp() + 5);
			setHp(getHp() + 5);
		}
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
		setGold(getGold() + other.getGold());
		return true;
	}
	
	return false;
}

