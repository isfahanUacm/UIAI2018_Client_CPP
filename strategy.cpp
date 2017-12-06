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
    players[0] = Player( 3 , "jafar" , Pos(0,0));
    players[1] = Player( 1 , "majid" , Pos(1,1));
    players[2] = Player( 2 , "abbas" , Pos(2,2));
    players[3] = Player( 5 , "gholam" , Pos(3,3));
    players[4] = Player( 4 , "Kerim" , Pos(4,4));

    return players;

}

Triple Strategy::do_turn(Game *game)
{
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%MY Team" << endl;
    cout << "Ball Pos: " << game->get_ball()->get_Position().get_x() << "  " << game->get_ball()->get_Position().get_y() << endl;
    for(int i=0;i<5;i++)
    {
    cout << "Player " << i  << ": id:"<<game->get_myTeam()->get_players()[i].get_id() << "  name:" << game->get_myTeam()->get_players()[i].get_name()
         << "  pos:" << game->get_myTeam()->get_players()[i].get_pos().get_x() << " , " << game->get_myTeam()->get_players()[i].get_pos().get_y() << endl;

    }
    cout << "SCORE:" << game->get_myTeam()->get_score() << endl;

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl <<endl;

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%OPP Team" << endl;
    for(int i=0;i<5;i++)
    {
    cout << "Player " << i  << ": id:"<<game->get_oppTeam()->get_players()[i].get_id() << "  name:" << game->get_oppTeam()->get_players()[i].get_name()
         << "  pos:" << game->get_oppTeam()->get_players()[i].get_pos().get_x() << " , " << game->get_oppTeam()->get_players()[i].get_pos().get_y() << endl;

    }
    cout << "SCORE:" << game->get_oppTeam()->get_score() << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl;
    Triple triple (1,1,1);
    return triple;


}

