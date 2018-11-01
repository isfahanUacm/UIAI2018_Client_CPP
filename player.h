#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "pos.h"
using namespace std;
class Player
{
    string name;
    Pos pos;
    Pos firstPos;
    int score;

public:
    Player();
    Player(string name_ , Pos firstPos_) ;

    void set_position(Pos pos_);
    string get_name();
    Pos get_pos();
    Pos get_First_pos();
    int get_score();
};

#endif // PLAYER_H
