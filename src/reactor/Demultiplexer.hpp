#pragma once

#include <poll.h>
#include <vector>

class Demultiplexer {
  public:
    explicit Demultiplexer(int serverSocket);

    int                  pollEvents();
    std::vector<pollfd>& getDescriptors();

  private:
    int                 _serverSocket;
    std::vector<pollfd> _fds;
};
