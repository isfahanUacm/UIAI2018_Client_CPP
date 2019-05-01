#include "game.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include <stdio.h>
#include<string.h>

using namespace  std;

#pragma comment(lib, "Ws2_32.lib")

Game::Game(string server_Address, unsigned int server_port)
{
    this->serverAddress = server_Address;
    this->serverPort = server_port;

    MyTeam = new Team;
    OppTeam = new Team ;
    ball = new Ball;
    MyTeam->players =  Strategy::init_players();

}

bool Game::connect_server( )
{
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

void Game::start(string name)
{
    this->teamName = name ;
    string reg = "register " + teamName + '\n' ;

    int flag = 0;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    int l =send(sock,reg.c_str(),strlen(reg.c_str()),0);
    if (l< 0){
        printf("ERROR!");
    };


    Player *players = Strategy::init_players();
    string formation = "formation ";
    for(int i=0;i<5;i++)
        formation += players[i].get_name() + ":"
                + std::to_string(players[i].get_First_pos().get_x()) + ":" + std::to_string(players[i].get_First_pos().get_y() )
                + (i==4 ? "" : ",");

    formation += "\n";
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

    ret = sgetline(sock, &buf);
    if (ret < 0)
        return; // error/disconnect
	
    string s = buf;
	
	if (s.empty())
	{
		cout << "Error: buf string is Empty." << endl;
		cout << "please contact with Technical support" << endl;
		exit(0);
	}

    if(s.substr(0,3) == "END")
    {
        cout << "Finished." << endl;
        exit(0);
    }
    vector<string> self_positions{explode(s, ',')};

    ret = sgetline(sock, &buf);
    if (ret < 0)
        return; // error/disconnect
    s = buf;
    vector<string> opp_positions { explode(s,',')};

    ret = sgetline(sock, &buf);
    if (ret < 0)
        return; // error/disconnect

    string ball_position = buf;
    for(int i=0;i<5;i++)
    {
        vector<string> self {explode(self_positions[i] , ':')};
        MyTeam->get_players()[i].set_position(Pos(stod(self[0]),  stod(self[1]) ));

        vector<string> opp {explode(opp_positions[i] , ':')};
        OppTeam->get_players()[i].set_position(Pos(stod(opp[0]) , stod(opp[1])));
        OppTeam->get_players()[i].id = i;

   
	}

	vector<string> bal {explode(ball_position, ':') };
    ball->set_Position(Pos(stod(bal[0]) , stod(bal[1])));


    ret = sgetline(sock, &buf);
    if (ret < 0)
        return; // error/disconnect
    s = buf;

    vector<string> scores {explode(s,',')};

    MyTeam->set_score(stoi(scores[0]));
    OppTeam->set_score(stoi(scores[1]));
    cycleNum = stoi(scores[2]);

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

 vector<string> Game::explode(const string &s, const char &c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

int Game::get_cycleNum()
{
    return cycleNum;
}

void Game::kick(Triple triple)
{
    int flag = 0;
    int l =send(sock,triple.toString().c_str(),strlen(triple.toString().c_str()),0);
    //	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    if (l< 0){
        printf("ERROR!");
    };
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

