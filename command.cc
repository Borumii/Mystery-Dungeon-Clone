#include <iostream>
#include <sstream>
#include "command.h"


using namespace std;


void Command::update(const GameBoard &b) {
    this->floor = b.getFloor();
    this->hero = floor->getHero();
}

void Command::toggleMovement()
{
	if(movement)
		movement=false;
	else
		movement=true;
	
}

void Command::interpret(string command) {
    istringstream iss{command};
    string c;
    string dir;
    
    iss >> c;
    if (c == "a") {
	    iss >> dir;
	    Info target = {direction[dir].x + hero->getX(), 
		    direction[dir].y + hero->getY()};
	    floor->attackMonster(target);
	    if(movement)
 		floor->performActions();
		
		if(hero->getRaceName()=="Troll")
			hero->setHp(hero->getHp()+5);

    }
    else if (c == "u") {
	    iss >> dir;
	    floor->usePotion(direction[dir].x + hero->getX(), 
			    direction[dir].y + hero->getY());
	    if(movement)
		 floor->performActions();
		
		if(hero->getRaceName()=="Troll")
			hero->setHp(hero->getHp()+5);
    }
    else if (c == "e") {
	    floor->usePotion();
	    if(movement)
	 floor->performActions();

		if(hero->getRaceName()=="Troll")
			hero->setHp(hero->getHp()+5);
    }
    else if(c == "f")
    {
	    toggleMovement();
	}
    else if (!direction.count(c)) {
	    return;
    }
    else {
	    Info target = {direction[c].x + hero->getX(), 
		    direction[c].y + hero->getY()};
	    if (floor->validTile(target, hero) && floor->validMove(target, hero)) {
		    hero->moveX(direction[c].x);
		    hero->moveY(direction[c].y);
		    floor->pickupGold(hero->getX(), hero->getY());
		    floor->pickupPotion(hero->getX(), hero->getY(), hero);
	    }
		floor->getNearbyPotions(*hero);
		if(movement)
	   	 floor->performActions();

		if(hero->getRaceName()=="Troll")
			hero->setHp(hero->getHp()+5);
	   // if(floor->getHero()->getHp()==0)
	//	    break;
    }
    
}


