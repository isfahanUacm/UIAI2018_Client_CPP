#include "player.h"

Player::Player()
{
}

Player::Player(string name_, Pos firstPos_, int id_)
{
    this->name = name_;
    this->firstPos = firstPos_;
    this->id = id_;

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

int Player::get_id()
{
    return id;
}
