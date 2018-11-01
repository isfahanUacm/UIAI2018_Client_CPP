#include "game.h"


Game::Game(string server_Address, unsigned int server_port, string name)
{
    this->serverAddress = server_Address;
    this->serverport = server_port;
    this->teamName = name ;
    MyTeam = new Team;
    OppTeam = new Team ;
    ball = new Ball;
}

bool Game::connect_server( )
{
    socket = new QTcpSocket(nullptr);
    socket->connectToHost(QString::fromStdString(serverAddress) , serverport);
    return (socket->waitForConnected(20000));
}

void Game::start()
{
    string reg = "register " + teamName + + " \n" ;
    socket->write( reg.c_str()  ) ;
    socket->flush();

    //LOGO
//    socket->write("logo null \n");
//    socket->flush();
    Player *players = Strategy::Setup_players();
    string formation = "formation ";
    for(int i=0;i<5;i++)
        formation += players[i].get_name() + ":"
                + std::to_string(players[i].get_First_pos().get_x()) + ":" + std::to_string(players[i].get_First_pos().get_y() )
                + (i==4 ? "" : ",");

    formation += "\n";
    socket->write(formation.c_str());
    socket->flush();
    while (true)
       play_round();
}


void Game::play_round()
{
    cout << "CYCLE NUMBER : " <<cycleNum << endl;
    socket->waitForReadyRead(15000);
    QString self = socket->readLine(1000);
    cout << "SELF DATA : " << self.toStdString().substr(0,3) << endl;
    if(self.trimmed().toStdString()== "END")
    {
        cout << "EXIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIT" << endl;
        socket->close();
        exit(0);
        cout << "________________________________$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    }
//    cout << "Self Position : " << self.toStdString() << endl;
    QStringList self_positions = self.split(',');


    QString opp = socket->readLine(1000);
//    cout << opp.toStdString() << endl;
    QStringList opp_positions = opp.split(',');

    QString ball_position = socket->readLine(1000);
//    cout << ball_position.toStdString() << endl;


    for(int i=0;i<5;i++)
    {
        MyTeam->get_players()[i].set_position(Pos(self_positions.at(i).split(':').at(0).toDouble(),  self_positions.at(i).split(':').at(1).toDouble() ));
        OppTeam->get_players()[i].set_position(Pos(opp_positions[i].split(':')[0].toDouble() , opp_positions[i].split(':')[1].toDouble() ));
    }

    ball->set_Position(Pos(ball_position.split(':')[0].toDouble() , ball_position.split(':')[1].toDouble()));
    QString s = socket->readLine(1000);
    QStringList scores  = s.split(',');

    MyTeam->set_score(scores[0].toInt());
    OppTeam->set_score(scores[1].toInt());
    cycleNum = scores[2].toInt();

    kick(Strategy::do_turn(this));
}

int Game::get_cycleNum()
{
    return cycleNum;
}

void Game::kick(Triple triple)
{
    socket->write(triple.toString().c_str());
    cout << triple.toString().c_str() << endl;
    socket->waitForBytesWritten(5000);
    socket->flush();
    return;
}

Team *Game::get_myTeam()
{
    return MyTeam;
}

Team *Game::get_oppTeam()
{
    return OppTeam;
}

Ball *Game::get_ball()
{
    return ball;
}

