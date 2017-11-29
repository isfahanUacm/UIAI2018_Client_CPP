#include "triple.h"

Triple::Triple(int id_, double angle_, double power_ )
{
    PlayerId = id_;
    angle = angle_;
    power = power_;
}

void Triple::set_player_id(int PlayerId_)
{
    PlayerId = PlayerId_;
}

void Triple::set_angle(double angle_)
{
    angle = angle_;
}

void Triple::set_power(double power_)
{
    power = power_;
}

string Triple::toString()
{
    string tmp = std::to_string(PlayerId) + ","
            + std::to_string(angle) + ","
            + std::to_string(power) + "\n";
    return tmp;
}
