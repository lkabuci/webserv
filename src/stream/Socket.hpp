#pragma once

#include "AddressResolver.hpp"
#define BACKLOG 10

// TODO: add the correct address ip and port number that we binded
// TODO: add default values of port and ip
class Socket {

  public:
    Socket(const char* ip, const char* port);
    ~Socket();
    int getSocketfd() const;

  private:
    int _sockfd;
    const char* _ip;
    const char* _port;
    const AddressResolver _addresses;

    Socket(const Socket&);
    Socket& operator=(const Socket&);
    void initializeSocket();
    void configureSocket();
    void bindSocket(int index);
};
