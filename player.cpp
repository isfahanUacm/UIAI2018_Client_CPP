#include "player.h"

Player::Player()
{
}

Player::Player(string name_, Pos firstPos_)
{
    this->name = name_;
    this->firstPos = firstPos_;

}

int Player::get_score()
{
    return score;
}

void Player::set_position(Pos pos_)
{
    this->pos = pos_;
}

string Player::get_name()
{
    return name;
}

Pos Player::get_pos()
{
    return pos;
}

Pos Player::get_First_pos()
{
    return firstPos;
}
