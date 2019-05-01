#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "pos.h"
using namespace std;
class Player
{
	friend class Game;
    string name;
    Pos pos;
    Pos firstPos;
    int id;

public:
    Player();
    Player(string name_ , Pos firstPos_ , int id_) ;

    string get_name();
    Pos get_pos();
    Pos get_First_pos();
    int get_id();
private:
	void set_position(Pos pos_);
};

#endif // PLAYER_H
