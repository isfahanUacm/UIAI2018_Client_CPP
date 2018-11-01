#include "team.h"
#include <iostream>
using namespace std;

Team::Team()
{
    Player *tmp = Strategy::Setup_players();
    players = new Player[5];

    cout << "----------------------------@@ Start Team " << endl;
    for(int i=0 ; i < 5;i++)
    {
        cout << i << " id:"<<  i <<"  " << tmp[i].get_name().c_str() << "  FirstPos:" << tmp[i].get_First_pos().get_x() << "," << tmp[i].get_First_pos().get_y() <<  "  pos:" << tmp[i].get_pos().get_x() << "," <<tmp[i].get_pos().get_y() << endl;
        players[i] = tmp[i];
    }
    cout << "----------------------------@@ End Team " << endl;
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
