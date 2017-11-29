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
    int id;
    int score;

public:
    Player();
    Player(int id, string name_ , Pos firstPos_) ;

    void set_player_position(Pos pos_);

    string get_player_name();
    Pos get_player_pos();
    Pos get_player_First_pos();
    int get_player_score();
    int get_player_id();
};

#endif // PLAYER_H
