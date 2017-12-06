#ifndef GAME_H
#define GAME_H
#include <QStringList>
#include "team.h"
#include "ball.h"

#include <QTcpSocket>
#include <string>
#include <QString>
#include <iostream>

using namespace std;

class Game
{

    int cycleNum = 0;
    Team *MyTeam;
    Team *OppTeam;
    Ball *ball;
    QTcpSocket *socket;

    string serverAddress;
    int serverport;
    string teamName;

    void play_round();

public:
    Game(string  server_Address, unsigned int  server_port, string name);
    bool connect_server();
    void start();
    int get_cycleNum();
    void kick (Triple triple);
    Team *get_myTeam();
    Team *get_oppTeam();
    Ball *get_ball();

};

#endif // GAME_H
