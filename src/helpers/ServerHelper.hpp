#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

class ServerHelper {
  public:
    static const char* GetIPAddressFromSockAddr(int);
    static const char* GetPortAddressFromSockAddr(int);
};
