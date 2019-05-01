#ifndef GAME_H
#define GAME_H
#include "team.h"
#include "ball.h"

#include <string>
#include <iostream>
#include <vector>



#ifdef WIN32
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
  #ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  #include <windows.h>

#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <netinet/tcp.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
#endif

class Game
{
private:

	friend int main();
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
	bool connect_server();
	void start(string name);
	void kick(Triple triple);


public:
    Game(string  server_Address, unsigned int  server_port);

    int get_cycleNum();

    Team *get_myTeam();
    Team *get_oppTeam();
    Ball *get_ball();

};

#endif // GAME_H
