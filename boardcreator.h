#ifndef __BOARDCREATOR__H
#define __BOARDCREATOR__H

#include <iostream>
#include <string>
#include "gameboard.h"
#include "floor.h"

class BoardCreator {
    std::string filename;
    bool defaultfile;
    void setRow(std::string str, std::shared_ptr<Floor> f);

    void setGenerate(std::shared_ptr<Floor> floor, std::string race);
    void setCharacters(std::string line, std::shared_ptr<Floor> floor, int x, std::string s);
    public:
    BoardCreator(std::string filename);
    // Initilizes the GameBoard
    GameBoard create(std::string s, int x=20, int y=10, int z=10);
    void setFilename(std::string filename);
    void findHoard(std::shared_ptr<Floor> floor);
};

#endif
