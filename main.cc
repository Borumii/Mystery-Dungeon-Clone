#include <iostream>
#include <memory>
#include <ctime>
#include "boardcreator.h"
#include "gameboard.h"
#include "textdisplay.h"
#include "command.h"
#include "score.h"
#include "achievement.h"
#include "monster.h"

using namespace std;

int main(int argc, char *argv[]) {
	
    bool tracking = false;
    bool achievements = false;
    bool hardmode = false;
    bool easymode = false;
    int x, y, z; x = 20, y = z = 10;
    BoardCreator boardcreator{"cc3kfloor.txt"};
    
    int i = 1;
    if (argc > 1 && argv[1][0] != '-') {
        boardcreator.setFilename(argv[1]);
        i++; 
    }
    
    for( ; i < argc; i++)
    {
	string c = argv[i];
	if(c == "-t")
	{	
		if(!tracking)
		{
			Monster::enableTracking();
			tracking = true;
		}	
	}
	else if(c == "-c")
	{
		if(!hardmode && !easymode)
		{
			Monster::enableChallengeMode(1.25);
			hardmode = true;
			x = 30; y = 5; z = 5;
		}
	}
	else if(c == "-e")
	{
		if(!easymode && !hardmode)
		{
			Monster::enableChallengeMode(0.75);
			easymode = true;
			x = 15; y = 10; z = 10;
		}

	}
	else if(c == "-a")
	{
		if(!achievements)
		{
			Achievement::enabled = true;
			achievements = true;
		}
	}
	else
	{
		cout << "Wrong usage!" << endl;
		cout << "use commands: cc3k [FILE] -t, -a, -c, or -e" << endl;
	}
    }
    
	
    if(tracking) cout << "Intelligent tracking enabled!" << endl; 
    if(achievements) cout << "Achievements enabled!" << endl; 
    if(hardmode) cout << "Challenging mode enabled! " << endl;
    if(easymode) cout << "Easy mode enabled!" << endl;

    srand(time(NULL));
    RESTART:

	
    GameBoard b;

    Score score;
    TextDisplay display;
    string command;
	
	RESTART2:
	cout<<"Pick a race:"<<endl;
	
	string racePick;
	cin>>racePick;
    cin.ignore();
	if(racePick=="s" || racePick=="d" || racePick=="v" || racePick=="g" || racePick=="t")
	{
		b = boardcreator.create(racePick, x, y, z);
	}
	else
		goto RESTART2;
    

    Achievement::initializeAchievementClass(make_shared<GameBoard>(b)); 

    Command c;
    c.update(b);
    score.update(&b);

    display.setFloor(b.getFloor());
    while(true) {
        display.setGrid();
    //    display.setHero();
        display.setPotions();
        display.setGold();
	display.setHero();
        display.setMonsters();
        display.displayfloor(); 
        score.update();
        cout << score;
	int finalgold;
        
        getline(cin, command);
        if ((command.size() > 0 && command.at(0) == 'q') || cin.fail()) {
           break;
        }

        c.interpret(command);
	if(b.getFloor()->getHero()->getHp()==0)
	{
		b.setFinalScore();
		finalgold=b.getFinalScore();
	cout << endl;
	cout << "______________________________________" << endl;
	cout << "                                     " << endl;
	cout << " You have died. Game over. Score: "<<finalgold<<endl;
	cout << "______________________________________" << endl;

	LOOP:
	 cout<<"Press q to quit or r to restart."<<endl;
	// LOOP:
	 string sss;
	    while(cin>>sss)
	    {
	 	if(sss=="r")
		{	
			b.getFloor()->getHero()->getAction();
			for(auto floor: b.getFloors())
        		floor->slayMonsters();
			goto RESTART;
		}
	 	else if(sss=="q")
		{
			goto END;
		}
		
	    }	
	}

	

        if (b.needNextFloor()) {
            if (b.lastFloor()) {
		Achievement::updateAchievements();
		Achievement::updateEndAchievements();
		b.setFinalScore();
		int finalgold=b.getFinalScore();

		cout<< b.getFloor()->getHero()->getAction() << endl;
		cout << endl;
		cout << "______________________________________" << endl;
		cout << "                                      " << endl;
		cout << " You won. You are a tryhard. Score: " << finalgold << endl;
		cout << "______________________________________" << endl;

		goto LOOP;

            }
	    else
	    {
		Achievement::updateAchievements();
	    }
	    b.goUp();			
            display.setFloor(b.getFloor());
            c.update(b);
        }
    }

	END:
    score.update();

    for(auto floor: b.getFloors())
        floor->slayMonsters();
}


