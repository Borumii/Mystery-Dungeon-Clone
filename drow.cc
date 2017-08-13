#include "drow.h"
#include "achievement.h"

using namespace std;

Drow::Drow(): Hero(150, 25, 15, "Drow"){
}

void Drow::applyPotion(Potion &potion){

	int hpb = getHp();
	setHp(getHp() + potion.getHPMod() * 1.5);
	int hpa = getHp();

	if(hpb != hpa) Achievement::damagetaken = true;

	setCurrentAtk(getCurrentAtk() + potion.getAtkMod()  * 1.5);
	setCurrentDef(getCurrentDef() + potion.getDefMod()  * 1.5);

	addAction("You used " + potion.getPotionType() + " potion.");

	if(++Achievement::potionsused == Achievement::potionsusedrequied)
	{
		Achievement::toggle("Overdose");
	}
}


