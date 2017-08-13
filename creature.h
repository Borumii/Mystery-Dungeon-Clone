#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <memory>
#include "character.h"
#include "item.h"

class Potion;

class Creature: public Character{
		int hp;
		int max_hp;
		const int atk;
		int currentAtk;
		const int def;
		int currentDef;
		int speed = 1;
		const std::string raceName;
		int gold;
		int roomId;
	protected:
		std::shared_ptr<Potion> pickedPotion;
	public:
		Creature(int new_hp, int new_atk, int new_def, std::string new_raceName, char new_symbolm, int new_gold);
        //True if Creature is killed, otherwise false
		virtual bool attack(Creature &other);
		virtual void getAttacked(Creature &other);

		int getHp();
		void setHp(int new_Hp);
		int getMax_hp();
		void setMax_hp(int new_Max_hp);
		int getAtk();
		int getCurrentAtk();
		void setCurrentAtk(int new_CurrentAtk);
		int getDef();
		int getCurrentDef();
		void setCurrentDef(int new_CurrentDef);
		int getSpeed();
		void setSpeed(int new_Speed);
		std::string getRaceName();
		virtual bool isHostile();
		int getGold();
		void setGold(int new_Gold);
		std::shared_ptr<Potion> dropPotion();
		void pickPotion(std::shared_ptr<Potion> new_pickedPotion);
		virtual void kill();
		int getRoomID();
		void setRoomID(int new_RoomId);
};

#endif


