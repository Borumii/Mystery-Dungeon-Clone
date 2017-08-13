#include <string>
#include "enemy.h"

using namespace std;

Enemy::Enemy(int new_hp, int new_atk, int new_def, string new_raceName, char new_symbol): Monster(new_hp, new_atk, new_def, new_raceName, new_symbol){
}


Enemy::Enemy(int new_hp, int new_atk, int new_def, string new_raceName, char new_symbol, int new_gold): Monster(new_hp, new_atk, new_def, new_raceName, new_symbol, new_gold){
}


