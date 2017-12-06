#ifndef STRATEGY_H
#define STRATEGY_H
#include <iostream>
#include <vector>
#include "pos.h"
#include "player.h"
#include "triple.h"

class Game;

using namespace std;

class Strategy
{

public:
    Strategy();
    static Player *Setup_players();
    static Triple do_turn( Game *game);

};

#endif // STRATEGY_H
