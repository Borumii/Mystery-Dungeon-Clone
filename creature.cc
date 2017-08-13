#include <cmath>
#include <string>
#include <iostream>
#include <memory>
#include "creature.h"
#include "hero.h"
#include "achievement.h"
//#include "potion.h"

using namespace std;

Creature::Creature(int new_hp, int new_atk, int new_def, string new_raceName, char new_symbol, int new_gold): Character(new_symbol), hp(new_hp), atk(new_atk), def(new_def), raceName(new_raceName), gold(new_gold) {	
	setCurrentAtk(getAtk());
	setCurrentDef(getDef());
	setMax_hp(getHp());
}


bool Creature::attack(Creature &other){
		
	other.getAttacked(*this);
	
	if(getSymbol() == '@')
	{
		Achievement::combatevents++;

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

		setGold(getGold() + other.getGold());
		return true;
	}
	
	return false;
}

void Creature::getAttacked(Creature &other){
	
	if(getSymbol() == '@')
		Achievement::damagetaken = true;
		
	setHp(getHp() - ceil((100/(100.0 + getCurrentDef())) * other.getCurrentAtk()));
}

int Creature::getHp(){
	return hp;
}

void Creature::setHp(int new_Hp){
	if(new_Hp <= 0) hp = 0;
	else if(new_Hp >= max_hp) hp = max_hp;
	else hp = new_Hp;
}

int Creature::getMax_hp(){
	return max_hp;
}

void Creature::setMax_hp(int new_Max_hp){
	max_hp = (new_Max_hp >= 0) ? new_Max_hp:0;
}

int Creature::getAtk(){
	return atk;
}

int Creature::getCurrentAtk(){
	return currentAtk;
}

void Creature::setCurrentAtk(int new_CurrentAtk){
	currentAtk = (new_CurrentAtk >=0) ? new_CurrentAtk:0;
;
}

int Creature::getDef(){
	return def;
}

int Creature::getCurrentDef(){
	return currentDef;
}

void Creature::setCurrentDef(int new_CurrentDef){
	currentDef = (new_CurrentDef>=0) ? new_CurrentDef:0;
}

int Creature::getSpeed(){
	return speed;
}

void Creature::setSpeed(int new_Speed){
	speed = new_Speed;
}

string Creature::getRaceName(){
	return raceName;
}

bool Creature::isHostile(){
	return true;
}

int Creature::getGold()
{
	return gold;
}

void Creature::setGold(int new_Gold)
{
	gold = new_Gold;
}


shared_ptr<Potion> Creature::dropPotion(){
	if(pickedPotion)
		pickedPotion->setCoord(this->getX(), this->getY());
	return pickedPotion;
}

void Creature::pickPotion(shared_ptr<Potion> new_pickedPotion){
	pickedPotion = new_pickedPotion;
}

void Creature::kill(){
	setHp(0);
}

int Creature::getRoomID(){
	return roomId;
}

void Creature::setRoomID(int new_RoomId){
	roomId = new_RoomId;
}


