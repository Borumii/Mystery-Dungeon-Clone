#include "textdisplay.h"

#include "charactermaster.h"

using namespace std; 

void TextDisplay::setFloor(shared_ptr<Floor> floor) {
    this->floor = floor;
}

void TextDisplay::displayfloor() {
    for (auto row: grid) {
        cout << row; 
        cout << endl;
    }
}

void TextDisplay::setSymbol(int x, int y, char symbol) {
    grid[x][y] = symbol;
}

void TextDisplay::setCharacter(shared_ptr<Character> character) { 
    int x = character->getX();
    int y = character->getY();
    int symbol = character->getSymbol();
    this->setSymbol(x, y, symbol);
}

void TextDisplay::setHero() {
    this->setCharacter(floor->getHero());
}

void TextDisplay::setMonsters() {
    for (auto monster: floor->getMonsters()) {
        this->setCharacter(monster);
    }
}

void TextDisplay::setPotions() {
    for (auto potion: floor->getPotions()) {
        this->setCharacter(potion);
    }
}

void TextDisplay::setGold() {
    for (auto gold: floor->getGold()) {
        this->setCharacter(gold);
    }
}

void TextDisplay::setGrid() {
    grid.clear();
    for (auto row: floor->getTiles()) {
        string line;
        for (auto tile: row) {
            switch(tile) {
                case Tile::HWall:
                    line += '-';
                    break;
                case Tile::VWall:
                    line += '|';
                    break;
                case Tile::Room:
                    line += '.';
                    break;
                case Tile::Passage:
                    line += '#';
                    break;
                case Tile::Empty:
                    line += ' ';
                    break;
                case Tile::Door:
                    line += '+';
                    break;
                case Tile::Stair:
                    line += '\\';
                    break;
                default:
                    break;
            }
        }
        grid.push_back(line); 
    }
}

