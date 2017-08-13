#ifndef __GAMEBOARD__H
#define __GAMEBOARD__H

#include <iostream>
#include <vector>
#include <memory>
#include "floor.h"

class GameBoard {
  //  int floorCount;
    std::vector<std::shared_ptr<Floor>> floors;
    int currentFloor;
    int finalScore;

    public:
    GameBoard(int currentFloor = 0);
    void setFloor(std::shared_ptr<Floor> floor);
    void setCurrentFloor(int currentFloor);
    std::shared_ptr<Floor> getFloor() const;
    int getCurrentFloor() const;
    std::vector<std::shared_ptr<Floor>> getFloors();
    void loadNext();
    bool needNextFloor();
    bool lastFloor();
    void goUp();
    int getFinalScore();
    void setFinalScore();
};

#endif

