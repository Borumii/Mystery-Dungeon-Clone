#include <string>
#include "elf.h"
#include <cstdlib>

using namespace std;

Elf::Elf(): Enemy(140, 30, 10, "Elf", 'E'){
}


bool Elf::attack(Creature &other){

	Hero d = dynamic_cast<Hero&>(other);
	
	if(rand() % 2)
	{
		other.getAttacked(*this);
		d.addAction("You were attacked by a " + getRaceName() + ".");
	}
	else
	{
		d.addAction("You were missed by a " + getRaceName() + ".");
	}

	if(other.getRaceName().compare("Drow"))	// Elf's special ability
	{
		if(rand() % 2)
		{
			other.getAttacked(*this);
			d.addAction("You were attacked by a " + getRaceName() + ".");
		}

		else
		{
			d.addAction("You were missed by a " + getRaceName() + ".");
			return false;
		}
	}



	if(other.getHp() == 0)
	{
		setGold(getGold() + other.getGold());
		return true;
	}
	
	return false;
}


