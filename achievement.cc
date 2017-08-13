#include <string>
#include <vector>
#include <iostream>
#include "achievement.h"

using namespace std;

shared_ptr<GameBoard> Achievement::g;
shared_ptr<Hero> Achievement::h;
vector<bool> Achievement::achiev;
int Achievement::count = 10;
int Achievement::earned = 0; 
int Achievement::goldcountrequied = 10;
int Achievement::potionsused = 0;
int Achievement::potionsusedrequied = 3;
bool Achievement::damagetaken = false;
int Achievement::movesused = 0;
int Achievement::movesallowed = 200;
int Achievement::combatevents = 0;
string Achievement::raceAttacked = "";

bool Achievement::enabled = false;

void Achievement::initializeAchievementClass(shared_ptr<GameBoard> new_g)
{
	g = new_g;
	updateHero();

	achiev.clear();

	for(int i = 0; i < count; i++)
		achiev.emplace_back(!enabled);
}

void Achievement::updateHero()
{
	h = g->getFloor()->getHero();
}


void Achievement::toggle(string name)
{
	string msg = "";
	int index = 0;
	if(name == "Overdose"){ msg = "Consume " + to_string(potionsusedrequied) + " potions."; index = 0;}	
	if(name == "Hoarder"){ msg = "Collect " + to_string(goldcountrequied ) + " pieces of gold."; index = 1;}	
	if(name == "Bully"){ msg = "Kill your first halfling."; index = 2;}	
	if(name == "Reckless"){ msg = "Kill a dwarf as a vampire."; index = 3;}
	if(name == "Dragon Slayer"){ msg = "Slay your first dragon."; index = 4;}	
	if(name == "Racist"){ msg = "You hate the "+ raceAttacked +" race."; index = 5;}	
	if(name == "Clearing House"){ msg = "Kill all enemies in a floor."; index = 6;}	
	if(name == "Pacifist"){ msg = "Do not engage in combat for a floor."; index = 7;}	
	if(name == "Immortal"){ msg = "Do not take any damage in a floor."; index = 8;}
	if(name == "SpeedRun"){ msg = "Win the game in less than " + to_string(movesallowed) + " moves."; index = 9;}	
	
	if(!achiev[index]){
		h->addAction("Achievement unlocked: " + name + " - " + msg);
		achiev[index] = true;
	}

}

void Achievement::checkRacist(string name)
{
	if(raceAttacked == "")
	{
		raceAttacked = name;		
	}
	else if(raceAttacked != name)
	{
		raceAttacked = "x";
	}
}

void Achievement::detectRacist()
{
	if(raceAttacked != "x" && raceAttacked != "")
		toggle("Racist");
	
}

void Achievement::checkPacifist()
{
	if(combatevents == 0)
		toggle("Pacifist");
	combatevents = 0;
	
}

void Achievement::checkImmortal()
{
	if(damagetaken == false)
		toggle("Immortal");
	damagetaken = false;
	
}

void Achievement::checkClearingHouse()
{
	if(g->getFloor()->getMonsters().size() == 0)
		toggle("Clearing House");
}

void Achievement::checkSpeedRun()
{
	if(movesused <= movesallowed)
		toggle("SpeedRun");

}

void Achievement::updateAchievements()
{
	updateHero();
	checkPacifist();
	checkImmortal();
	checkClearingHouse();
	damagetaken = false;
	combatevents = 0;
}

void Achievement::updateEndAchievements()
{
	detectRacist();
	checkSpeedRun();
}

void Achievement::updateMoves()
{
	movesused++;
}



