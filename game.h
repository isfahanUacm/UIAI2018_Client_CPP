#ifndef GAME_H
#define GAME_H
#include <QStringList>
#include "team.h"
#include "ball.h"
#include "strategy.h"
#include <QTcpSocket>
#include <string>
#include <QString>
#include <iostream>
using namespace std;

class Game : public QObject
{

    int cycleNum = 0;
    Team *MyTeam;
    Team *OppTeam;
    Ball *ball;
    QTcpSocket *socket;

    string serverAddress;
    int serverport;
    string teamName;


public:
    Game(string  server_Address, unsigned int  server_port, string name);
    bool connect_server();
    void start();
    void play_round();
    int get_cycleNum();

    void kick (Triple triple);

};

#endif // GAME_H
