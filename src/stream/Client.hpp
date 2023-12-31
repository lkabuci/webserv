#pragma once

#include "../../include/webserv.h"
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>

class Client {
  public:
    explicit Client(struct sockaddr_storage&, int);
    const char*   getClientAddress() const;
    int           getSockFd() const;
    short         getEvent() const;
    short         getRevent() const;
    void          setRevent(short);
    void          setEvent(short);
    const pollfd& getPfd() const;
    void          setPfd(const pollfd& pfd);

  private:
    struct sockaddr_storage& _sockAddr;
    const int                _sockfd;
    struct pollfd            _pfd;
    char                     _ip[INET6_ADDRSTRLEN];
    char                     _port[PORT_LEN];

    void initClient();
    void fillIpPort();
};
