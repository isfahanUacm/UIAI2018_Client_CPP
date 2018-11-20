#include "team.h"
#include <iostream>
using namespace std;

Team::Team()
{
    players = new Player[5];
}

Player *Team::get_players()
{
    return players;
}

int Team::get_score()
{
    return score;
}

void Team::set_score(int score_)
{
    score = score_;
}
