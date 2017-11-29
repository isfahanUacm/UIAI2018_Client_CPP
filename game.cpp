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
    socket = new QTcpSocket(this);
    socket->connectToHost(QString::fromStdString(serverAddress) , serverport);
    return (socket->waitForConnected(20000));
}

void Game::start()
{
    string reg = "register " + teamName + + " \n" ;
    socket->write( reg.c_str()  ) ;
    socket->flush();

    //LOGO
    socket->write("logo null \n");
    socket->flush();
    Player *players = Strategy::Setup_players();
    string formation = "formation ";
    for(int i=0;i<5;i++)
        formation += players[i].get_player_name() + ":"
                + std::to_string(players[i].get_player_First_pos().get_x()) + ":" + std::to_string(players[i].get_player_First_pos().get_y() )
                + (i==4 ? "" : ",");

    formation += "\n";
    cout << formation << endl;
    socket->write(formation.c_str());
    socket->flush();

    while (true)
    {
        play_round();

    }
}


void Game::play_round()
{
    cout << "CYCLE NUMBER : " <<cycleNum << endl;
    socket->waitForReadyRead(10000);
    QString self = socket->readLine(1000);
    cout << self.toStdString() << endl;
    QStringList self_positions = self.split(',');

    QString opp = socket->readLine(1000);
    cout << opp.toStdString() << endl;
    QStringList opp_positions = opp.split(',');
    QString ball_position = socket->readLine(1000);
    cout << ball_position.toStdString() << endl;

    for(int i=0;i<5;i++)
    {
//        MyTeam->get_players()[i].set_player_position(Pos(6,7));

        MyTeam->get_players()[i].set_player_position(Pos(self_positions.at(i).split(':').at(0).toInt(),  self_positions.at(i).split(':').at(1).toInt() ));
        OppTeam->get_players()[i].set_player_position(Pos(opp_positions[i].split(':')[0].toInt() , opp_positions[i].split(':')[1].toInt() ));
    }
    ball->set_Ball_Position(Pos(ball_position.split(':')[0].toInt() , ball_position.split(':')[1].toInt()));
    QString s = socket->readLine(1000);
    cout << s.toStdString() << endl;
    QStringList scores  = s.split(',');

    MyTeam->set_score(scores[0].toInt());
    OppTeam->set_score(scores[1].toInt());
    cycleNum = scores[2].toInt();

    kick(Strategy::do_turn());

}

int Game::get_cycleNum()
{
    return cycleNum;
}

void Game::kick(Triple triple)
{
    cout << "HEEEEEEEEEEEEEEEEEEE" << endl;
    socket->write(triple.toString().c_str());
    cout << triple.toString().c_str() << endl;
    socket->waitForBytesWritten(3000);
    socket->flush();
    cout << "SHEEEEEEEEEEEEEEEEEEEEEEE" << endl;
    return;
}

