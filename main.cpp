#include <iostream>
#include "game.h"
using namespace std;

int main()
{
  //  Game game("192.168.43.85" , 9595 , "team1" ) ;
    Game game("127.0.0.1" , 9595 , "team2" ) ;
    if(game.connect_server())
    {
        game.start();
    }

}
