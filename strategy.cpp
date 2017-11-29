#include "strategy.h"
Strategy::Strategy()
{

}

Player *Strategy::Setup_players()
{

    /*This is a stupid example code for formation of Players*/

    Player *players = new Player[5];
    players[0] = Player( 1 , "PlayerName1" , Pos(0,0));
    players[1] = Player( 2 , "PlayerName2" , Pos(1,1));
    players[2] = Player( 3 , "PlayerName3" , Pos(2,2));
    players[3] = Player( 4 , "PlayerName4" , Pos(3,3));
    players[4] = Player( 5 , "PlayerName5" , Pos(4,4));

    return players;

}

Triple Strategy::do_turn()
{
    Triple triple (1,1,1);
    return triple;
}

