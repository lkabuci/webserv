#pragma once

#include "../../include/webserv.h"
#include "Demultiplexer.hpp"
#include "Dispatcher.hpp"

class EventLoop {
  public:
    explicit EventLoop(int serverSocket);

    void start();

  private:
    Demultiplexer _demultiplexer;
    Dispatcher    _dispatcher;
};
