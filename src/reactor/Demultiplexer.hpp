#pragma once

#include <poll.h>
#include <vector>

class Demultiplexer {
  public:
    static std::vector<pollfd> waitForEvents(const std::vector<int>& sockets);
//    static void waitForEvents(const std::vector<int>& sockets);
};
