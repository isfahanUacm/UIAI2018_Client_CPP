#ifndef GAME_H
#define GAME_H
#include "team.h"
#include "ball.h"

#include <string>
#include <iostream>
#include <vector>


#ifdef _WIN32
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
  #ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>

#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
#endif

class Game
{

    int cycleNum = 0;
    Team *MyTeam;
    Team *OppTeam;
    Ball *ball;

    string serverAddress;
	int serverPort;
    string teamName;

    void play_round();
	int sockInit();
	int sgetline(int fd, char ** out);
	//
	int sock;
	struct sockaddr_in server;
    vector<string> explode(const string& s , const char& c);

public:
    Game(string  server_Address, unsigned int  server_port);
    bool connect_server();
    void start(string name);
    int get_cycleNum();
    void kick (Triple triple);
    Team *get_myTeam();
    Team *get_oppTeam();
    Ball *get_ball();

};

#endif // GAME_H
