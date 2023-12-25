#pragma once

#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <vector>

class Dispatcher {
  public:
    explicit Dispatcher(int serverSocket);

    void acceptConnection(std::vector<pollfd>& fds);
    void processData(std::vector<pollfd>& fds);

  private:
    int _serverSocket;
};
