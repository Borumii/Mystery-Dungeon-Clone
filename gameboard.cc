#include "gameboard.h"
#include "memory.h"

using namespace std;

GameBoard::GameBoard(int currentFloor):
    currentFloor{currentFloor} {}

void GameBoard::setFloor(shared_ptr<Floor> floor) {
    floors.push_back(floor);
} 

shared_ptr<Floor> GameBoard::getFloor() const {
    return floors[currentFloor];
}

void GameBoard::setCurrentFloor(int currentFloor) {
    this->currentFloor = currentFloor;
}

int GameBoard::getCurrentFloor() const {
	return currentFloor;
}

std::vector<std::shared_ptr<Floor>> GameBoard::getFloors(){
	return floors;
}

bool GameBoard::needNextFloor() {
    int x = floors.at(currentFloor)->getHero()->getX();
    int y = floors.at(currentFloor)->getHero()->getY();
    if (floors.at(currentFloor)->getTiles()[x][y] == Tile::Stair) {
        return true; 
    }
    return false;
}

bool GameBoard::lastFloor() {
    if (floors.size() == (unsigned)currentFloor+1) {
        return true;
    }
    return false;
}

void GameBoard::goUp() {

	shared_ptr<Hero> a = getFloor()->getHero();
	
	int oldMaxHP=a->getMax_hp();
	int oldCurrentHP=a->getHp();
	int oldGold=a->getGold();
	shared_ptr<Potion> p = a->dropPotion();

    currentFloor++;
    	
	shared_ptr<Hero> newHero = getFloor()->getHero();
	newHero->setHp(oldCurrentHP);
	newHero->setMax_hp(oldMaxHP);
	newHero->setGold(oldGold);
	newHero->pickPotion(p);

}

int GameBoard::getFinalScore()
{
	return finalScore;
	
}

void GameBoard::setFinalScore()
{
	string name;
	name=getFloor()->getHero()->getRaceName();
	finalScore=getFloor()->getHero()->getGold();
	if(name == "Shade")
		finalScore=finalScore+(finalScore/2);
	
}

