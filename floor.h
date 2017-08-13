#ifndef __FLOOR__H
#define __FLOOR__H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "tile.h"
#include "info.h"
#include "hero.h"
#include "human.h"
#include "hoard.h"

class Monster;
class Gold;
class Potion;
class Character;
class Creature;

class Floor {
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::vector<Info>> rooms;

    std::vector<std::shared_ptr<Monster>> monsterHolder;
    std::vector<std::shared_ptr<Gold>> goldHolder;
    std::vector<std::shared_ptr<Potion>> potionHolder;

    void bfs(Info info, std::vector<std::vector<bool>> &check,
            std::vector<Info> &room); 

    int monsterCount;
    int goldCount;
    int potionCount;

    std::shared_ptr<Hero> hero;

    public:
    void setRow(std::vector<Tile> row);
    std::vector<std::vector<Tile>> getTiles();
    void setRoom(); 
   
    Floor(int mCount=20, int gCount=10, int pCount=10);
    
    void generatePotions();
    void generateGold();
    void generateMonsters();
    void generatePlayer(std::string s);
    void generateStair();
    
    void pickupGold(int x, int y);
    void pickupPotion(int x, int y, std::shared_ptr<Creature> c);


    Info getDragonTile(Info &i);
    std::shared_ptr<Hero> getHero();
    std::vector<std::shared_ptr<Monster>> getMonsters();
    std::vector<std::shared_ptr<Gold>> getGold();
    std::vector<std::shared_ptr<Potion>> getPotions();
    std::vector<std::shared_ptr<Hoard>> getHoard();

    void removeGlobalTile(int x, int y, int index);
    bool validTile(Info info, std::shared_ptr<Creature> c);
    bool validMove(Info info, std::shared_ptr<Creature> c);
    void getNearbyPotions(Hero &h);
    
    void shuffleInfo(std::vector<Info>& vec);
    void shuffleAll();

    
    void attackMonster(Info info);
    void performActions();
    void slayMonsters();

    void setHeroRoomID();
    void usePotion(int x=-1, int y=-1);

    void setHero(std::shared_ptr<Hero> hero);
    void setPotions(std::shared_ptr<Potion> potion);
    void setMonsters(std::shared_ptr<Monster> monster);
    void setGold(std::shared_ptr<Gold> gold);
    std::shared_ptr<Monster> monsterCheck(int x, int y);
};


#endif


