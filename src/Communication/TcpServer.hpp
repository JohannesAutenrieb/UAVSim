/**
 *
 * File: TCPServer.hpp
 * Class name: TCPServer
 * Purpose: This Class is the responsibel instance for creating a recieving tcp socket and recieving the data as a bitset
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _TCPSERVER_HXX
#define _TCPSERVER_HXX

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

using namespace std;

#define MAXPACKETSIZE 4096

class TCPServer
{
        public:
        int sockfd, newsockfd, n, pid;
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        pthread_t serverThread;
        char msg[ MAXPACKETSIZE ];
        static string Message;

        void setup(int port);
        string receive();
        string getMessage();
        void Send(string msg);
        void detach();
        void clean();

        private:
        static void * Task(void * argv);
};

#endif //_TCPSERVER_HXX
