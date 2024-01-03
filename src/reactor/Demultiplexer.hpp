#pragma once

#include <poll.h>
#include <vector>

class Demultiplexer {
  public:
    static int waitForEvents();
};
