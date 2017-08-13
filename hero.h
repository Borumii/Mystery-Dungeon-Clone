#ifndef HERO_H
#define HERO_H

#include <string>
#include <memory>
#include "creature.h"
#include "potion.h"

class Potion;

class Hero: public Creature{
		static std::string action;
	public:
		virtual void applyPotion(Potion &potion);
		Hero(int new_hp, int new_atk, int new_def, std::string new_raceName);
		std::string getAction();
		void addAction(std::string new_action);
		void clearAction();

		void getPotionAction(Potion &p);
		std::shared_ptr<Potion> getPotion();
};

#endif


