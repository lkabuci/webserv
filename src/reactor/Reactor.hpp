#pragma once

#include <poll.h>
#include <vector>

#include "Demultiplexer.hpp"
#include "Dispatcher.hpp"
#include "IEventHandler.hpp"

class Reactor {
  public:
    static Reactor& getInstance();
    void            registerHandler(IEventHandler* handler);
    void            unregisterHandler(IEventHandler* handler);
    void            run(const std::vector<int>& sockets);

  private:
    std::vector<IEventHandler*> _eventHandlers;
    Demultiplexer               _demultiplexer;
    Dispatcher                  _dispatcher;
};
