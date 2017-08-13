#include <string>
#include "potion.h"
#include "hero.h"

using namespace std;

Potion::Potion(): Item('P'){
}

string Potion::getType()
{
	return potionType;
}

void Potion::discover(){
}

string Potion::isDiscovered(){
	return "";
}


/*void Potion::setType(string name)
{
	potionType=name;
}*/

string Potion::getPotionType(){
	return potionType;
}


void Potion::applyTo(Hero &h)
{
	h.applyPotion(*this);
	discover();
}

int Potion::getAtkMod()
{
	return AtkMod;
}


int Potion::getDefMod()
{
	return DefMod;
}

int Potion::getHPMod()
{
	return HPMod;
}

void Potion::setAtkMod(int n)
{
	AtkMod=n;
}

void Potion::setDefMod(int n)
{
	DefMod=n;
}

void Potion::setHPMod(int n)
{
	HPMod=n;
}




