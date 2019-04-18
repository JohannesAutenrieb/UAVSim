/**
 *
 * File: UDBServer.hpp
 * Class name: UDBServer
 * Purpose: This Class is the responsibel instance for creating a recieving udb socket and recieving the data as a bitset
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _UDPSERVER_HXX
#define _UDPSERVER_HXX


#include<string>
#include <string.h>
#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include<cerrno>
#include"Udp_Server_Client_Error.hpp"

class udp_server
{
public:
                        udp_server(const std::string& addr, int port);
                        ~udp_server();

    int                 get_socket() const;
    int                 get_port() const;
    std::string         get_addr() const;

    int                 recv(char *msg, size_t max_size);
    int                 timed_recv(char *msg, size_t max_size, int max_wait_ms);

private:
    int                 f_socket;
    int                 f_port;
    std::string         f_addr;
    struct addrinfo *   f_addrinfo;
};
#endif //_UDPSERVER_HXX
