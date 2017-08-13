#ifndef _SCOREH_
#define _SCOREH_

#include <string>
#include "hero.h"
#include "gameboard.h"


class Score
{
	std::shared_ptr<Hero> h;
	GameBoard *gameboard;
	
	public:
    void update(GameBoard *gameboard);
    std::string getRace();
	int getHP();
	int getGold();
	int getAttack();
	int getDefence();
	int getCurrentFloor();
    
    int setHero();
    int setGameBoard();
    
    void update();
    std::shared_ptr<Hero> getHero();

	void endGame();
    friend std::ostream& operator<<(std::ostream& out, Score &score);
};

std::ostream& operator<<(std::ostream& out, Score &score);

#endif


