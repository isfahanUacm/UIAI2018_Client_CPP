#include "strategy.h"
#include "game.h"
Strategy::Strategy()
{

}

Player *Strategy::Setup_players()
{

    /*This is a stupid example code for formation of Players
    ID , Name , FirstPos */

    Player *players = new Player[5];
    players[0] = Player( "jafar" , Pos(-7,0));
    players[1] = Player( "majid" , Pos(-4,-2));
    players[2] = Player( "abbas" , Pos(-4,2));
    players[3] = Player( "Mamad" , Pos(-1,-1));
    players[4] = Player( "Kerim" , Pos(-1,1));

    return players;

}

Triple Strategy::do_turn(Game *game)
{
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%MY Team" << endl;
    cout << "Ball Pos: " << game->get_ball()->get_Position().get_x() << "  " << game->get_ball()->get_Position().get_y() << endl;
    for(int i=0;i<5;i++)
    {
    cout << "Player " << i  << ": id:"<< i << "  name:" << game->get_myTeam()->get_players()[i].get_name()
         << "  pos:" << game->get_myTeam()->get_players()[i].get_pos().get_x() << " , " << game->get_myTeam()->get_players()[i].get_pos().get_y() << endl;

    }
    cout << "SCORE:" << game->get_myTeam()->get_score() << endl;

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl <<endl;

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%OPP Team" << endl;
    for(int i=0;i<5;i++)
    {
    cout << "Player " << i  << ": id:"<< i << "  name:" << game->get_oppTeam()->get_players()[i].get_name()
         << "  pos:" << game->get_oppTeam()->get_players()[i].get_pos().get_x() << " , " << game->get_oppTeam()->get_players()[i].get_pos().get_y() << endl;

    }
    cout << "SCORE:" << game->get_oppTeam()->get_score() << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl;

    Team *myteam = game->get_myTeam();
    Team *oppteam = game->get_oppTeam();
    Ball *ball = game->get_ball();

    Triple triple(0,0,0);

    return triple;

}

