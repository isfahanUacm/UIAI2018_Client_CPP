#include "ball.h"

Ball::Ball()
{

}

void Ball::set_Position(Pos pos)
{
    ballPos = pos ;
}

Pos Ball::get_Position()
{
    return ballPos;
}
