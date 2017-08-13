#ifndef __COMMAND__H
#define __COMMAND__H

#include <map>
#include <memory>
#include "gameboard.h"
#include "hero.h"
#include "info.h"
#include "floor.h"

static std::map<std::string, Info> direction = {
   {"no", Info{-1, 0}},
   {"so", Info{1, 0}},
   {"ea", Info{0, 1}},
   {"we", Info{0, -1}},

   {"ne", Info{-1, 1}},
   {"nw", Info{-1, -1}},
   {"se", Info{1, 1}},
   {"sw", Info{1, -1}}
};

class Command {
    std::shared_ptr<Floor> floor;
    std::shared_ptr<Hero> hero;

    bool movement=true;
    
    public:
    void update(const GameBoard &b);

    void toggleMovement();

    void interpret(std::string command);
};

#endif
