#pragma once

#include "Demultiplexer.hpp"
#include "Dispatcher.hpp"
#include "../../include/webserv.h"

class EventLoop {
  public:
    explicit EventLoop(int serverSocket);

    void start();

  private:
    Demultiplexer _demultiplexer;
    Dispatcher    _dispatcher;
};
