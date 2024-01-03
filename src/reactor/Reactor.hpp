#pragma once

#include <poll.h>
#include <vector>

#include "Demultiplexer.hpp"
#include "Dispatcher.hpp"
#include "IEventHandler.hpp"

class Reactor {
  public:
    static Reactor& getInstance();
    ~Reactor();
    void                 registerHandler(IEventHandler* handler, int socket);
    void                 unregisterHandler(IEventHandler* handler);
    void                 run(const std::vector<int>& sockets);
    std::vector<pollfd>& getPollfds();

  private:
    std::vector<IEventHandler*> _eventHandlers;
    std::vector<pollfd>         _pollfds;
    Demultiplexer               _demultiplexer;
    Dispatcher                  _dispatcher;
};
