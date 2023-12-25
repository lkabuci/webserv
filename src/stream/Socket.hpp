#pragma once

#include "../helpers/ServerHelper.hpp"
#include "AddressResolver.hpp"
#include <netdb.h>
#define BACKLOG 10

// TODO: add the correct address ip and port number that we binded
// TODO: add default values of port and ip
class Socket {

  public:
    Socket(const char* ip, const char* port);
    ~Socket();
    int         getSocketfd() const;
    const char* getIP() const;
    const char* getPort() const;

  private:
    int                   _sockfd;
    const char*           _ip;
    const char*           _port;
    const AddressResolver _addresses;

    Socket(const Socket&);
    Socket& operator=(const Socket&);
    void    initializeSocket();
    void    configureSocket();
    void    bindSocket(const struct addrinfo);
};
