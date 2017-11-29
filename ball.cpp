#include "ball.h"

Ball::Ball()
{

}

void Ball::set_Ball_Position(Pos pos)
{
    ballPos = pos ;
}

Pos Ball::get_Ball_Position()
{
    return ballPos;
}
