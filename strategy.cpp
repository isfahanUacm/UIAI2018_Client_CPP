#include "strategy.h"
#include "game.h"
#define PI 3.14159265
Strategy::Strategy()
{

}

Player *Strategy::init_players()
{
    Player *players = new Player[5];
    /*
    Here you can set each of your player's name and your team formation.
    In case of setting wrong position, server will set default formation for your team.
     */

    players[0] = Player("R. Ahmadi", Pos(-6.5,0));
    players[1] = Player("E. Hajisafi", Pos(-2,1));
    players[2] = Player("M. Karimi", Pos(-5,-2));
    players[3] = Player("M. Navidkia", Pos(-5,2));
    players[4] = Player("H. Aghili", Pos(-2,-1));


    return players;

}

Triple Strategy::do_turn(Game *game)
{
    Triple act;
    /*
    Write your code here
    At the end you have to set 3 parameter:
        player id -> act.setPlayerID()
        angle -> act.setAngle()
        power -> act.setPower()
     */

    //Sample code for shooting a random player in the ball direction with the maximum power:
    int your_player_Id = rand() % 5;
    act.setPlayerID(your_player_Id);

    double x1,x2,y1,y2;
    x1 = game->get_myTeam()->get_players()[your_player_Id].get_pos().get_x();
    y1 = game->get_myTeam()->get_players()[your_player_Id].get_pos().get_y();
    x2 = game->get_ball()->get_Position().get_x();
    y2 = game->get_ball()->get_Position().get_y();

    double radian_angle = abs(atan((double)(y2-y1)/(double)(x2-x1)));//Calculate the angle from the chosen player to the ball
    int degree_angle = radian_angle * (180.0/PI) ;

    if(x2>x1)
    {
        if(y2<y1)
            degree_angle =360-degree_angle;
    }
    else
    {
        if(y2<y1)
            degree_angle += 180;
        else
            degree_angle = 180 - degree_angle;
    }
    act.setAngle(degree_angle);

    act.setPower(100);

    return act;


}

