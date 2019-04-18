/**
 *
 * File: UdpServerClient.hpp
 * Class name: TCPServer
 * Purpose: This Class is the higher heritaged class of the others udp classes. This Class involves members for proofing errors.
 *
 * @author Johannes Autenrieb
 * @version 1.0 15/06/18
*/

#ifndef _UDP_SEREVER_CLIENT_ERROR_HXX
#define _UDP_SEREVER_CLIENT_ERROR_HXX


#include<stdexcept>

class udp_client_server_runtime_error : public std::runtime_error
{
public:
    udp_client_server_runtime_error(const char *w) : std::runtime_error(w) {}
};
#endif //_UDP_SEREVER_CLIENT_ERROR_HXX
