#include "game.h"
#include <windows.h>
#include<iostream>
#include <stdio.h>
#include<string>

using namespace  std;
#pragma comment(lib, "Ws2_32.lib")

Game::Game(string server_Address, unsigned int server_port, string name)
{
    this->serverAddress = server_Address;
	this->serverPort = server_port;
    this->teamName = name ;
    MyTeam = new Team;
    OppTeam = new Team ;
    ball = new Ball;
}

bool Game::connect_server( )
{
	//
	sockInit();
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		perror("Could not create socket");
	}
	//setup address structure
	if(inet_addr(serverAddress.c_str()) == -1)
	{
		struct hostent *he;
		struct in_addr ** addr_list;

		//resolve the hostname, its not an ip address
		if ( (he = gethostbyname( serverAddress.c_str() ) ) == NULL)
		{
			//gethostbyname failed
			return false;
		}

		//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
		addr_list = (struct in_addr **) he->h_addr_list;

		for(int i = 0; addr_list[i] != NULL; i++)
		{
			//strcpy(ip , inet_ntoa(*addr_list[i]) );
			server.sin_addr = *addr_list[i];
			break;
		}
	}
	//plain ip address
	else
	{
		server.sin_addr.s_addr = inet_addr( serverAddress.c_str() );
	}

	server.sin_family = AF_INET;
	server.sin_port = htons( serverPort );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}


	return true;

}

void Game::start()
{
	string reg = "register " + teamName + '\n' ;
//    socket->write( reg.c_str()  ) ;
//    socket->flush();
	int flag = 0;
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
	int l =send(sock,reg.c_str(),strlen(reg.c_str()),0);
	if (l< 0){
		printf("ERROR!");
	};

	//LOGO
//	socket->write("logo null \n");
//	socket->flush();
	string logo = "logo null \n";
	l = send(sock,logo.c_str(),strlen(logo.c_str()),0);
	flag = 0;
	//setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
	if (l< 0){
		printf("ERROR!");
	};

	Player *players = Strategy::Setup_players();
	string formation = "formation ";
	for(int i=0;i<5;i++)
		formation += players[i].get_name() + ":"
				+ std::to_string(players[i].get_First_pos().get_x()) + ":" + std::to_string(players[i].get_First_pos().get_y() )
				+ (i==4 ? "" : ",");

	formation += "\n";
	cout<<formation;
//    socket->write(formation.c_str());
//    socket->flush();
	//sh_debug
	l = send(sock,formation.c_str(),strlen(formation.c_str()),0);
	flag = 0;
	//setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
	if (l< 0){
		printf("ERROR!");
	};
	while (true)
	   play_round();
}

void Game::play_round()
{
	char * buf;
	int ret ;
	cout << "CYCLE NUMBER : " <<cycleNum << endl;
	//socket->waitForReadyRead(15000);
	//QString self = socket->readLine(1000);

	ret = sgetline(sock, &buf);
	if (ret < 0)
		return; // error/disconnect

	//cout << "Self Position : " << self.toStdString() << endl;
	QString s = QString::fromUtf8(buf);
	QStringList self_positions = s.split(',');

//    QString opp = socket->readLine(1000);
//    cout << opp.toStdString() << endl;

	ret = sgetline(sock, &buf);
	if (ret < 0)
		return; // error/disconnect
	s = QString::fromUtf8(buf);
	QStringList opp_positions = s.split(',');


	ret = sgetline(sock, &buf);
	if (ret < 0)
		return; // error/disconnect
	QString ball_position = QString::fromUtf8(buf);
//    QString ball_position = socket->readLine(1000);
//    cout << ball_position.toStdString() << endl;


	for(int i=0;i<5;i++)
	{
		MyTeam->get_players()[i].set_position(Pos(self_positions.at(i).split(':').at(0).toDouble(),  self_positions.at(i).split(':').at(1).toDouble() ));
		OppTeam->get_players()[i].set_position(Pos(opp_positions[i].split(':')[0].toDouble() , opp_positions[i].split(':')[1].toDouble() ));
	}

	ball->set_Position(Pos(ball_position.split(':')[0].toDouble() , ball_position.split(':')[1].toDouble()));
	ret = sgetline(sock, &buf);
	s = QString::fromUtf8(buf);
	QStringList scores  = s.split(',');

	MyTeam->set_score(scores[0].toInt());
	OppTeam->set_score(scores[1].toInt());
	cycleNum = scores[2].toInt();

	kick(Strategy::do_turn(this));
}

int Game::sockInit()
{
#ifdef _WIN32
	WSADATA wsa_data;
	return WSAStartup(MAKEWORD(1,1), &wsa_data);
#else
	return 0;
#endif
}

int Game::sgetline(int fd, char ** out)
{
	int buf_size = 128;
	int bytesloaded = 0;
	int ret;
	char buf;
	char *buffer = (char*)calloc(buf_size, sizeof(char));
	char * newbuf;

	if (NULL == buffer)
		return -1;

	do
	{
		// read a single byte
		ret = recv(fd, &buf, 1, 0);
		if (ret < 1)
		{
			// error or disconnect
			free(buffer);
			return -1;
		}

		buffer[bytesloaded] = buf;
		bytesloaded++;

		// has end of line been reached?
		if (buf == '\n')
			break; // yes

		// is more memory needed?
		if (bytesloaded >= buf_size)
		{
			buf_size += 128;
			newbuf = (char*)realloc(buffer, buf_size);

			if (NULL == newbuf)
			{
				free(buffer);
				return -1;
			}

			buffer = newbuf;
		}
	}while (true);

	// if the line was terminated by "\r\n", ignore the
	// "\r". the "\n" is not in the buffer
	if ((bytesloaded) && (buffer[bytesloaded-1] == '\r'))
		bytesloaded--;

	*out = buffer; // complete line
	return bytesloaded; // number of bytes in the line, not counting the line break
}

int Game::get_cycleNum()
{
    return cycleNum;
}

void Game::kick(Triple triple)
{
	int flag = 0;
	int l =send(sock,triple.toString().c_str(),strlen(triple.toString().c_str()),0);
	cout<<triple.toString();
//	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
	if (l< 0){
		printf("ERROR!");
	};
//    socket->write(triple.toString().c_str());
//    cout << triple.toString().c_str() << endl;
//    socket->waitForBytesWritten(5000);
//    socket->flush();
//    return;
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

