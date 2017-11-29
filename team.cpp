#include "team.h"

Team::Team()
{
    Player *tmp = Strategy::Setup_players();
    players = new Player[5];

    for(int i=0 ; i < 4;i++)
        players[i] = tmp[i];

    // be careful for

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
