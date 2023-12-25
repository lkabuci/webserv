#pragma once

#include "Demultiplexer.hpp"
#include "Dispatcher.hpp"

class EventLoop {
  public:
    EventLoop(int serverSocket);

    void start();

  private:
    Demultiplexer _demultiplexer;
    Dispatcher    _dispatcher;
};
