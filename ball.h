#ifndef BALL_H
#define BALL_H
#include "pos.h"


class Ball
{
    Pos ballPos;
public:
    Ball(); // @TODO set ball in middle of field
    Pos get_Position ();
private:
    void set_Position (Pos pos);
    friend class Game;
};

#endif // BALL_H
