#pragma once

#include "../stream/Client.hpp"
#include <cstdio>
#include <poll.h>
#include <sys/poll.h>
#include <vector>

class Webserver {
  public:
    // TODO: change it latter to std::vector<Server>& servers
    explicit Webserver(std::vector<int>& serverSockets);
    void start();
    ~Webserver();

  private:
    void                 removeClient(size_t index);
    std::vector<pollfd>  _pollfds;
    size_t               _nbrOfServers;
    std::vector<Client*> _clients;
};
