#include <memory>
#include "hero.h"
#include "ba.h"
#include "wa.h"
#include "bd.h"
#include "wd.h"
#include "ph.h"
#include "rh.h"

#include "achievement.h"

using namespace std;
string Hero::action = "";

Hero::Hero(int new_hp, int new_atk, int new_def, string new_raceName): Creature(new_hp, new_atk, new_def, new_raceName, '@', 0){
	//Score s();
	//score = s;
}

void Hero::applyPotion(Potion &potion){
	int hpb = getHp();
	setHp(getHp() + potion.getHPMod());
	int hpa = getHp();
	
	if(hpb != hpa) Achievement::damagetaken = true;

	setCurrentAtk(getCurrentAtk() + potion.getAtkMod());
	setCurrentDef(getCurrentDef() + potion.getDefMod());

	addAction("You used " + potion.getPotionType() + " potion.");

	if(++Achievement::potionsused == Achievement::potionsusedrequied)
	{
		Achievement::toggle("Overdose");
	}
}

string Hero::getAction(){
	string temp = action;
	clearAction();
	return temp;
}

void Hero::addAction(string new_action){
	if(action == "")
	{
		action = new_action;
	}
	else
	{
		action += " " + new_action;
	}
}

void Hero::clearAction(){
	action = "";
}

void Hero::getPotionAction(Potion &p){
	string type = p.isDiscovered();
	
	if(type == "")
		type = "an unknown";
	else
		type = "a " + type;
	
	addAction("You see " + type + " potion.");
					
}

shared_ptr<Potion> Hero::getPotion(){
	return pickedPotion;
}

