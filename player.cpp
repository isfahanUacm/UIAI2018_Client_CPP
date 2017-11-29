#include "player.h"

Player::Player()
{

}

Player::Player(int id_ , string name_, Pos firstPos_)
{
    this->id = id_;
    this->name = name_;
    this->firstPos = firstPos_;

}

int Player::get_player_score()
{
    return score;
}

void Player::set_player_position(Pos pos_)
{
    this->pos = pos_;
}

string Player::get_player_name()
{
    return name;
}

int Player::get_player_id()
{
    return id;
}

Pos Player::get_player_pos()
{
    return pos;
}

Pos Player::get_player_First_pos()
{
    return firstPos;
}
