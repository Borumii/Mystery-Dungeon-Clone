#include "character.h"

Character::Character(char new_Symbol): symbol(new_Symbol){
}

char Character::getSymbol(){
	return symbol;
}

void Character::setSymbol(char new_Symbol){
	symbol = new_Symbol;
}

int Character::getX(){
	return x;
}
void Character::moveX(int offset){
	x += offset;
}	
int Character::getY(){
	return y;
}

void Character::moveY(int offset){
	y += offset;
}

void Character::setCoord(int new_x, int new_y){
	x = new_x;
	y = new_y;
}
