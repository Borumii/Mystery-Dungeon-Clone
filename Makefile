CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g 
OBJECTS = boardcreator.o floor.o textdisplay.o gameboard.o\
		  drow.o goblin.o shade.o elf.o human.o dragon.o dwarf.o halfling.o\
		  orc.o troll.o merchant.o hero.o monster.o creature.o character.o\
		  enemy.o potion.o ba.o bd.o wa.o wd.o rh.o ph.o item.o hoard.o gold.o\
		  vampire.o command.o achievement.o score.o main.o  
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS} 

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
