#ifndef CHARACTER_H
#define CHARACTER_H

class Character{
	private:
		char symbol;
		int x;
		int y;
	public:
		Character(char new_Symbol);
		char getSymbol();
		void setSymbol(char new_Symbol);
		int getX();
		void moveX(int offset);	
		int getY();
		void moveY(int offset);
		void setCoord(int new_x, int new_y);

};

#endif

