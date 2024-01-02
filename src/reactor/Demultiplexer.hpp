#pragma once

#include <poll.h>
#include <vector>

class Demultiplexer {
  public:
    // TODO: here should be a list of server sockets instead of only one
    // explicit Demultiplexer(int[] serverSockets);
    explicit Demultiplexer(int serverSocket);

    int                  pollEvents();
    std::vector<pollfd>& getDescriptors();
    //    std::vector<Client>& getClients();

  private:
    int _serverSocket;
    //    std::vector<Client> _clients;
    std::vector<pollfd> _fds;
};
