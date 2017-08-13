#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include "boardcreator.h"
#include "charactermaster.h"
#include "tile.h"
using namespace std;

BoardCreator::BoardCreator(string filename):
    filename{filename}, defaultfile{true} {}

void BoardCreator::setFilename(string filename) {
    this->filename = filename;
    defaultfile = false; 
}

void BoardCreator::setRow(std::string line, shared_ptr<Floor> floor) {
    istringstream str{line};
    vector<Tile> row;

    char sym;
    str >> noskipws;
    while (str >> sym) {
        switch (sym) {
            case '|':
                row.push_back(Tile::VWall);
                break;
            case '-':
                row.push_back(Tile::HWall);
                break;
            case '.':
                row.push_back(Tile::Room);
                break;
            case '+':
                row.push_back(Tile::Door);
                break;
            case '#':
                row.push_back(Tile::Passage);
                break;
            case ' ':
                row.push_back(Tile::Empty);
                break;
            case '\\':
                if (!defaultfile) {
                    row.push_back(Tile::Stair);
                }
                else {
                    row.push_back(Tile::Room);
                }
                break;
            default:
                row.push_back(Tile::Room);
                break;
        }
    }
    floor->setRow(row);
}
void BoardCreator::setCharacters(std::string line, shared_ptr<Floor> floor, int x, string s) { 
    istringstream str{line};
    char c;
    int y = 0;
    str >> noskipws;
    while (str >> c) {
        if (c == '0') {
            shared_ptr<RH> potion = make_shared<RH>();
            potion->setCoord(x, y);
            floor->setPotions(potion);
        }
        else if (c == '1') {
            shared_ptr<BA> potion = make_shared<BA>();
            potion->setCoord(x, y);
            floor->setPotions(potion);
        }
        else if (c == '2') {
            shared_ptr<BD> potion = make_shared<BD>();
            potion->setCoord(x, y);
            floor->setPotions(potion);
        }
        else if (c == '3') {
            shared_ptr<PH> potion = make_shared<PH>();
            potion->setCoord(x, y);
            floor->setPotions(potion);
        }
        else if (c == '4') {
            shared_ptr<WA> potion = make_shared<WA>();
            potion->setCoord(x, y);
            floor->setPotions(potion);
        }
        else if (c == '5') {
            shared_ptr<WD> potion = make_shared<WD>();
            potion->setCoord(x, y);
            floor->setPotions(potion);
        }
        else if (c == '6') {
            shared_ptr<Gold> gold = make_shared<Gold>(2);
            gold->setCoord(x, y);
            floor->setGold(gold);
        }
        else if (c == '7') {
            shared_ptr<Gold> gold = make_shared<Gold>(1);
            gold->setCoord(x, y);
            floor->setGold(gold);
        }
        else if (c == '8') {
            shared_ptr<Gold> gold = make_shared<Gold>(4);
            gold->setCoord(x, y);
            floor->setGold(gold);
        }
        else if (c == '@') {
            shared_ptr<Hero> hero;
            if(s=="s")
            {
                hero=make_shared<Shade>();
            }
            else if(s=="d")
            {
                hero=make_shared<Drow>();
            }
            else if(s=="v")
            {
                hero=make_shared<Vampire>();
            }
            else if(s=="g")
            {
                hero=make_shared<Goblin>();
            }
            else if(s=="t")
            {
                hero=make_shared<Troll>();
            }
            hero->setCoord(x, y);
            floor->setHero(hero);
        }
        else if(c == 'H')
		{
			shared_ptr<Monster> a = make_shared<Human>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
		else if(c == 'W')
		{
			shared_ptr<Monster> a = make_shared<Dwarf>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
		else if(c == 'M')
		{
			shared_ptr<Monster> a=make_shared<Merchant>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
		else if(c == 'L')
		{
			shared_ptr<Monster> a = make_shared<Halfling>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
		else if(c == 'E')
		{
			shared_ptr<Monster> a=make_shared<Elf>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
		else if(c == 'O')
		{
			shared_ptr<Monster> a=make_shared<Orc>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
		else if(c == 'D')
		{
			shared_ptr<Monster> a=make_shared<Dragon>();
            a->setCoord(x,y);
            floor->setMonsters(a);
		}
        else if (c == '9') {
            shared_ptr<Hoard> gold = make_shared<Hoard>();
            gold->setCoord(x, y);
            floor->setGold(gold);
        }
        y++;
    }
}

void BoardCreator::findHoard(shared_ptr<Floor> floor) {
    for (auto monster: floor->getMonsters()) {
        if (monster->getSymbol() == 'D') {
            for (auto gold: floor->getGold())  {
                if  (!gold->getPickable() &&
                    abs(monster->getX() - gold->getX()) <= 1 &&
                    abs(monster->getY() - gold->getY()) <= 1) {
                        shared_ptr<Dragon> g = dynamic_pointer_cast<Dragon>(monster);
                        shared_ptr<Hoard> h = dynamic_pointer_cast<Hoard>(gold);
                        g->setHoard(h);
                        h->setDragon(g);
                        break;
                }
            }
        }
    }
}

void BoardCreator::setGenerate(shared_ptr<Floor> floor, string race) {
    floor->setRoom();
    floor->shuffleAll();
    floor->generatePlayer(race);
    floor->generateStair();
    floor->generatePotions();
    floor->generateGold();
    floor->generateMonsters();
}

GameBoard BoardCreator::create(string race, int x, int y, int z) {
    GameBoard b;
    ifstream filein{filename};
    string line;
    shared_ptr<Floor> f;
    bool insidefloor = false;
    int j;
    while(getline(filein, line)) {
        if (!insidefloor && line.substr(0, 2) == "|-") {
            f = make_shared<Floor>(x, y, z);
            insidefloor = true;
            j = 0;
        }
        else if (insidefloor && line.substr(0, 2) == "|-") {
            insidefloor = false;
            this->setRow(line, f);
            if (defaultfile) {
                this->setGenerate(f, race);
            }
            else {
                this->findHoard(f);
            }
            b.setFloor(f);
        }
        if (insidefloor) {
            this->setRow(line, f);
            if (!defaultfile) {
                this->setCharacters(line, f, j, race);
            }
            j++;
        }
    }
    return b;
}


