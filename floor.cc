#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "floor.h"
#include "dragon.h"

#include "charactermaster.h"

#include "achievement.h"

using namespace std;

void Floor::setRow(std::vector<Tile> row) {
    tiles.push_back(row);
}

void Floor::setRoom() {
    vector<vector<bool>> check;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        vector<bool> boolrow;
        for (unsigned int j = 0; j < tiles[i].size(); j++) {
            boolrow.push_back(false);
        }
        check.push_back(boolrow);
    }

    for (int i = 0; (unsigned)i < tiles.size(); i++) {
        for (int j = 0; (unsigned)j < tiles[i].size(); j++) {
            if (!check[i][j] && tiles[i][j] == Tile::Room) {
                vector<Info> room;
                bfs(Info{i, j}, check, room);
                rooms.push_back(room);
            }
            else { 
                check[i][j] = true;
            }
        }
    }
    vector<Info> globalroom;
    for (auto room: rooms) {
        globalroom.insert(globalroom.end(), room.begin(), room.end());
    }
    rooms.insert(rooms.begin(), globalroom);
}

vector<shared_ptr<Monster>> Floor::getMonsters() {
    return monsterHolder;
}

vector<shared_ptr<Gold>> Floor::getGold() {
    return goldHolder;
}
vector<shared_ptr<Potion>> Floor::getPotions() {
    return potionHolder;
}

shared_ptr<Hero> Floor::getHero() {
    return hero;
}


void Floor::bfs(Info info, vector<vector<bool>> &check, vector<Info> &room) {
    int i = info.x;
    int j = info.y;

    if (check[i][j] || tiles[i][j] != Tile::Room) {
        return;
    }
    else {
        check[i][j] = true;
        room.push_back(info);
    }
    if ((unsigned)i+1 < tiles.size()) {
        bfs(Info{i+1, j}, check, room);
    }
    if (i-1 > 0) {
        bfs(Info{i-1, j}, check, room);
    }
    if ((unsigned)j+1 < tiles[i].size()) {
        bfs(Info{i, j+1}, check, room);
    }
    if (j-1 > 0) {
        bfs(Info{i, j-1}, check, room);
    }
}

vector<std::vector<Tile>> Floor::getTiles() {
    return tiles;
}

Floor::Floor(int mCount, int gCount, int pCount)
{
	goldCount=gCount;
	monsterCount=mCount;
	potionCount=pCount;
	
}


void Floor::shuffleAll()
{
   // auto engine = default_random_engine(random_device{}());
	for(auto &room : rooms)
	{
        	random_shuffle(room.begin(), room.end());
	}
}


void Floor::generatePotions()
{
	int size=rooms.size()-1;

	for(int i=0; i<potionCount; i++)
	{
		int index=(rand()%size)+1;

		int x=rooms[index].back().x;
		int y=rooms[index].back().y;

		rooms[index].pop_back();

		int potionID=rand()%6;

		shared_ptr<Potion> a;

		if(potionID==0)
		{
			a=make_shared<BA>();
		}
		else if(potionID==1)
		{
			a=make_shared<BD>();

		}
		else if(potionID==2)
		{
			a=make_shared<WA>();

		}
		else if(potionID==3)
		{
			a=make_shared<WD>();

		}
		else if(potionID==4)
		{
			a=make_shared<PH>();

		}
		else
		{
			a=make_shared<RH>();

		}
		a->setCoord(x,y);
		removeGlobalTile(x,y,0);
		potionHolder.emplace_back(a);

	}
	
}


void Floor::generateMonsters()
{
	for(int i=0; i<monsterCount; i++)
	{
		int x=rooms[0].back().x;
		int y=rooms[0].back().y;
		rooms[0].pop_back();

		int monsterID=rand()%18;

		shared_ptr<Monster> a;

		if(monsterID<=3)
		{
			a=make_shared<Human>();
			//human
		}
		else if(monsterID<=6)
		{
			a=make_shared<Dwarf>();
		}
		else if(monsterID<=11)
		{
			a=make_shared<Halfling>();
		}
		else if(monsterID<=13)
		{
			a=make_shared<Elf>();
		}
		else if(monsterID<=15)
		{
			a=make_shared<Orc>();
		}
		else
		{
			a=make_shared<Merchant>();
		}
		a->setCoord(x,y);
        monsterHolder.emplace_back(a);
		int length2=rooms.size();
		
		for(int j=1; j<length2; j++)
		{
			for(auto spot : rooms[j])
			{
				if(x==spot.x && y==spot.y)
					a->setRoomID(j);
			}
		}

	}
}

Info Floor::getDragonTile(Info &i)
{
	//returns coordinates to a valid dragon tile if it exists, or -1,-1 otherwise
	int oldX=i.x;
	int oldY=i.y;

	for(Info a:rooms[0])
	{
		if(((a.x<=oldX+1)&&(a.x>=oldX-1)) && ((a.y<=oldY+1)&&(a.y>=oldY-1)))
		{
			return a;
		}
	}

	Info b{-1,-1};
	return b;

	
}


void Floor::generateGold()
{
	for(int i=0; i<goldCount; i++)
	{
		int x=rooms[0].back().x;
		int y=rooms[0].back().y;
		rooms[0].pop_back();

		int goldID=rand()%8;
		shared_ptr<Gold> a;
		if(goldID<=4)
		{
			a=make_shared<Gold>(2);
		}
		else if(goldID<=5)
		{
			shared_ptr<Hoard> b = make_shared<Hoard>();
			a = b;
           		Info c{x,y};
			Info d=getDragonTile(c);

			if(d.x!=-1)
			{
				//create a dragon at coordinates specified by d
				shared_ptr<Dragon> dragon=make_shared<Dragon>();
				dragon->setCoord(d.x, d.y);
				dragon->setHoard(b);
				b->setDragon(dragon);
				monsterHolder.emplace_back(dragon);

			}
			else
			{
				i=i-1;
				continue;
			}
		}
		else
		{
			a=make_shared<Gold>(1);
		}
		
		a->setCoord(x,y);
		goldHolder.emplace_back(a);
		
	}
	
}

/*

void Floor::removeEntity(int x, int y, vector<shared_ptr<Character>>& holder)
{
	int length=holder.size();
	for(int i=0; i<length; i++)
	{
		if(x==holder[i]->getX() && y==holder[i]->getY())
		{
			holder.erase(holder.begin()+i);
			break;
		}
		
	}
	
}
*/


void Floor::removeGlobalTile(int x, int y, int index)
{
	int length=rooms[index].size();

	for(int i=0; i<length; i++)
	{
		if(x==rooms[index][i].x && y==rooms[index][i].y)
		{
			rooms[index].erase(rooms[index].begin()+i);
			break;
		}

	}
	
}

bool Floor::validTile(Info info, shared_ptr<Creature> c)
{
	if(c->getSymbol()=='@')
	{
		switch(tiles[info.x][info.y]) 
		{
			case Tile::Room:
			case Tile::Passage:
			case Tile::Stair:
			case Tile::Door:
				return true;
			default:
				return false;
			
		}
	}
	else
	{
		switch(tiles[info.x][info.y])
		{
			case Tile::Room:
				return true;
			default:
				return false;
			
		}

	}
	
}


bool Floor::validMove(Info info, shared_ptr<Creature> c)
{
	if(validTile(info, c))
	{
		for(auto a : monsterHolder)
		{
			if(a->getX()==info.x && a->getY()==info.y)
				return false;
		}
		return true;
	}
	return false;

}


void Floor::getNearbyPotions(Hero &h)
{

//cout<<"sdfkjgasdguiasdf"<<endl;	
	int x=h.getX();
	int y=h.getY();


	for(auto a : potionHolder)
	{
		if(((a->getX()<=x+1) && (a->getX()>=x-1)) && ((a->getY()<=y+1) && (a->getY()>=y-1)))
		{
			if(!(x==a->getX() && x==a->getY()))
				h.getPotionAction(*a);
		}
	}
}

void Floor::generatePlayer(string s)
{
	//assuming s is a valid string corresponding to a hero
		int x=rooms[0].back().x;
		int y=rooms[0].back().y;
		rooms[0].pop_back();


//		shared_ptr<Hero> a;

		if(s=="s")
		{
			hero=make_shared<Shade>();
			//human
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

		hero->setCoord(x,y);
        
		for(int i=1; i<5; i++)
		{
			removeGlobalTile(x,y,i);
		}
	
}



void Floor::pickupGold(int x, int y)
{
	int length=goldHolder.size();
	for(int i=0; i<length; i++)
	{
		if(goldHolder[i]->getX()==x && goldHolder[i]->getY()==y)
		{
			if(goldHolder[i]->getPickable())
			{
				hero->setGold(hero->getGold()+goldHolder[i]->getValue());
				goldHolder.erase(goldHolder.begin()+i);
			}
           	break;
		}
	}
	
}

void Floor::pickupPotion(int x, int y, shared_ptr<Creature> c)
{
	int length=potionHolder.size();
	for(int i=0; i<length; i++)
	{
		if(potionHolder[i]->getX()==x && potionHolder[i]->getY()==y)
		{
			c->pickPotion(potionHolder[i]);
		//	potionHolder.erase(potionHolder.begin()+i);

			string type = potionHolder[i]->isDiscovered();
			potionHolder.erase(potionHolder.begin()+i);
 
			type = (type == "" ? "an unknown":("a " + type));
			if(c->getSymbol()=='@')
			{
			//	string type = potionHolder[i]->getPotionType(); 
				hero->addAction("You have picked up " + type + " potion.");
			}
			else
			{
				hero->addAction(c->getRaceName() + " has picked up " + type + " potion.");
			}
			break;
		}

	}
}

void Floor::generateStair()
{
	int x=rooms[0].back().x;
	int y=rooms[0].back().y;
	rooms[0].pop_back();

	for(int i=1; i<5; i++)
	{
		removeGlobalTile(x,y,i);
	}
	
	tiles[x][y]=Stair;

	
}

void Floor::slayMonsters()
{
	for(auto a: monsterHolder)
		a->kill();
	
}


void Floor::performActions()
{
	Achievement::updateMoves();
	for(auto creature : monsterHolder)
	{
		Info a;
		if(creature->getHp()==0)
		{
			shared_ptr<Potion> p=creature->dropPotion();
			if(p)
			{
				potionHolder.emplace_back(p);
			}

			
			int length=monsterHolder.size();
			for(int i=0; i<length; i++)
			{
				if(monsterHolder[i]->getX()==creature->getX() && monsterHolder[i]->getY()==creature->getY())
				{
					monsterHolder.erase(monsterHolder.begin()+i);
				}
		
			}



			//removeEntity(creature->getX(), creature->getY(), monsterHolder);
			continue;	
		}
		a=creature->action(*hero);
		if(a.x!=-1)
		{
			if(validMove(a, creature))
			{
				creature->setCoord(a.x,a.y);
				pickupPotion(a.x,a.y,creature);
			}

			if(Monster::isTracking())
			{
				if(validMove(Info{a.x, creature->getY()}, creature))
				{
					creature->setCoord(a.x,creature->getY());
					pickupPotion(a.x,creature->getY(), creature);
				}
				else if(validMove(Info{creature->getX(), a.y}, creature))
				{
					creature->setCoord(creature->getX(), a.y);
					pickupPotion(creature->getX(), a.y, creature);
				}
			}

		}
		
	}

	if(hero->getGold() >= Achievement::goldcountrequied){
		Achievement::toggle("Hoarder");
	}
	setHeroRoomID();
}


void Floor::attackMonster(Info info){
	int x = info.x;
	int y = info.y;
	
	int length = monsterHolder.size();
	
	for(int i = 0; i < length; i++)
	{
		if(monsterHolder[i]->getX() == x && monsterHolder[i]->getY() == y)
		{

			bool killed = hero->attack(*monsterHolder[i]);			
			if(killed)
			{
				pickupGold(hero->getX(), hero->getY());
				shared_ptr<Potion> potion = monsterHolder[i]->dropPotion();
				if(potion != nullptr)
					potionHolder.emplace_back(potion);
				monsterHolder.erase(monsterHolder.begin()+i);
			}
			break;
		}
	}
}

bool isInRoom(int x, int y, vector<Info>& room)
{
	for(Info a : room)
	{
		if(a.x==x && a.y==y)
			return true;
		
	}
	return false;
}


void Floor::setHeroRoomID()
{
	int length=rooms.size();	
	
	for(int i=1; i<length; i++)
	{
		if(isInRoom(hero->getX(), hero->getY(), rooms[i]))
		{
			hero->setRoomID(i);
			break;
		}
		
	}
	

}

void Floor::usePotion(int x, int y)
{
//	cout<<"used potion"<<endl;
	if(x==-1 && hero->getPotion())
	{
		hero->getPotion()->applyTo(*hero);
		hero->pickPotion(nullptr);
	}
	else
	{
		int length=potionHolder.size();
		for(int i=0; i<length; i++)
		{
			if(potionHolder[i]->getX()==x && potionHolder[i]->getY()==y)
			{
				potionHolder[i]->applyTo(*hero);
				potionHolder.erase(potionHolder.begin()+i);
				break;
			}
			
		}
	}
}

shared_ptr<Monster> Floor::monsterCheck(int x, int y)
{
	int length=monsterHolder.size();
	for(int i=0; i<length; i++)
	{
		if(monsterHolder[i]->getX()==x && monsterHolder[i]->getY()==y)
		{
			return monsterHolder[i];
		}
		
	}
	return nullptr;
}

void Floor::setPotions(shared_ptr<Potion> potion) {
    potionHolder.push_back(potion);
}

void Floor::setMonsters(shared_ptr<Monster> monster) {
    monsterHolder.push_back(monster);
}

void Floor::setGold(shared_ptr<Gold> gold) {
    goldHolder.push_back(gold);
}

void Floor::setHero(shared_ptr<Hero> hero) {
    this->hero = hero;
}


