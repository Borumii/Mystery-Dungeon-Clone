#ifndef ACHIEV_H
#define ACHIEV_H

#include <vector>
#include "gameboard.h"

class Achievement{	
	static std::shared_ptr<GameBoard> g;
	static std::shared_ptr<Hero> h;
	
	static std::vector<bool> achiev;

	static int count;
	static int earned;

	public:
	// Hoarder
	static int goldcount;
	static bool enabled;
	static int goldcountrequied;

	// Overdose
	static int potionsused;
	static int potionsusedrequied;

	// Bully
	// Reckless
	// Dragon Slayer

	// Racist
	static std::string raceAttacked;

	// Pacifist
	static int combatevents;

	// Immortal
	static bool damagetaken;

	// SpeedRun
	static int movesused;
	static int movesallowed;

	// Clearing House
	
	static void toggle(std::string name);
	static void initializeAchievementClass(std::shared_ptr<GameBoard> new_g);
	static void updateHero();
	static void checkRacist(std::string name);
	static void detectRacist();
	static void checkPacifist();	
	static void checkImmortal();
	static void checkClearingHouse();	
	static void checkSpeedRun();
	static void updateMoves();

	static void updateAchievements();
	static void updateEndAchievements();
	

};




#endif


