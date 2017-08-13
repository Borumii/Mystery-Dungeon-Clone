#ifndef __TEXTDISPLAY__H
#define __TEXTDISPLAY__H

#include <iostream>
#include <vector>
#include <memory>
#include "floor.h"

#include "character.h"

class TextDisplay {
    std::shared_ptr<Floor> floor;
    std::vector<std::string> grid;
    void setCharacter(std::shared_ptr<Character> character);
    void setSymbol(int x, int y, char symbol);

    public: 
    void setHero();
    void setGold();
    void setPotions();
    void setMonsters();

    void setFloor(std::shared_ptr<Floor> floor);
    //After setting up the floor, then we can generate the grid.
    void setGrid();
    void displayfloor();
  
};
#endif


