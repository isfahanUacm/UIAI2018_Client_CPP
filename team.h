#ifndef TEAM_H
#define TEAM_H
#include <string>
#include "player.h"
#include "strategy.h"
using namespace std;

class Team
{
    friend class Game;
    string TeamName;
    Player *players;
    int score;
    void set_score(int score_);

public:
    Team();
    Player *get_players();
    int get_score();
};

#endif // TEAM_H
