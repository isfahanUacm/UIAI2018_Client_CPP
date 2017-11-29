#ifndef BALL_H
#define BALL_H
#include "pos.h"


class Ball
{
    Pos ballPos;
public:
    Ball(); // @TODO set ball in middle of field
    Pos get_Ball_Position ();
    void set_Ball_Position (Pos pos);
};

#endif // BALL_H
