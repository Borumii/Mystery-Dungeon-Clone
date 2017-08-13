#include <iostream>
#include <string>
#include <memory>
#include "score.h"
#include "gameboard.h" 

using namespace std;

void Score::update(GameBoard *gameboard) {
    this->gameboard = gameboard;
}

string Score::getRace()
{
	return h->getRaceName();
}

int Score::getHP()
{
	return h->getHp();
}

int Score::getGold()
{
	return h->getGold();
}

int Score::getAttack()
{
	return h->getCurrentAtk();
}

int Score::getDefence()
{
	return h->getCurrentDef();
}

int Score::getCurrentFloor()
{
	return gameboard->getCurrentFloor()+1;

}

void Score::endGame()
{
	//gameboard->endGame();
}

void Score::update() {
    h = gameboard->getFloor()->getHero();
}

shared_ptr<Hero> Score::getHero() {
    return h;
}


ostream& operator<<(ostream& out, Score &score)
{
	out<<"Race: "<< score.getRace() <<" ";
	out<<"Gold: "<< score.getGold() <<"                                                 ";
	out<<"Floor: ";
	out<<score.getCurrentFloor();
	//placeholder for floor number
	out<<endl;

	out<<"HP: "<<score.getHP()<<endl;
	out<<"Atk: "<<score.getAttack()<<endl;
	out<<"Def: "<<score.getDefence()<<endl;

	out<<"Action: ";
	out<<score.getHero()->getAction()<<endl;
	score.getHero()->clearAction();

	if(score.getHP()==0)
	{
		//endGame();
	}
	
	return out;
}

