#include "triple.h"

Triple::Triple()
{
    PlayerId = 0;
    angle = 0;
    power = 100;
}

Triple::Triple(int id_, double angle_, double power_ )
{
    PlayerId = id_;
    angle = angle_;
    power = power_;
}

void Triple::setPlayerID(int PlayerId_)
{
    PlayerId = PlayerId_;
}

void Triple::setAngle(double angle_)
{
    angle = angle_;
}

void Triple::setPower(double power_)
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
