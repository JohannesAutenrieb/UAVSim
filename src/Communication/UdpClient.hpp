/**
 *
 * File: UdpClient.hpp
 * Class name: UdpClient
 * Purpose: This Class is creating a sending socket and handeling the message which are need to be send
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/
#ifndef _UDPCLIENT_HXX
#define _UDPCLIENT_HXX


#include<string>
#include <string.h>
#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include"Udp_Server_Client_Error.hpp"


class udp_client
{
public:
                        udp_client(const std::string& addr, int port);
                        ~udp_client();

    int                 get_socket() const;
    int                 get_port() const;
    std::string         get_addr() const;

    int                 send(const char *msg, size_t size);

private:
    int                 f_socket;
    int                 f_port;
    std::string         f_addr;
    struct addrinfo *   f_addrinfo;
};
#endif //_UDPCLIENT_HXX
