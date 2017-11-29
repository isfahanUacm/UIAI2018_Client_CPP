#ifndef TEAM_H
#define TEAM_H
#include <string>
#include "player.h"
#include "strategy.h"
using namespace std;

class Team
{
    string TeamName;
    Player *players;
    int score;

public:
    Team();
    Player *get_players();
    int get_score();
    void set_score(int score_);
};

#endif // TEAM_H
