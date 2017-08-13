#ifndef _POTIONH_
#define _POTIONH_

#include "hero.h"
#include "item.h"
#include <string>

class Hero;

class Potion: public Item 
{
		int AtkMod=0;
		int DefMod=0;
		int HPMod=0;

	protected:
		std::string potionType;
	
	public:
		Potion();
		void applyTo(Hero &h);
		std::string getType();
//		void setType(std::string name);
		std::string getPotionType();

		virtual void discover();
		virtual	std::string isDiscovered();


		int getAtkMod();
		int getDefMod();
		int getHPMod();

		void setAtkMod(int n);
		void setDefMod(int n);
		void setHPMod(int n);


};

#endif


