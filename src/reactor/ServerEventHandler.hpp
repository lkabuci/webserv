#pragma once

#include "../stream/Server.hpp"
#include "IEventHandler.hpp"

class ServerEventHandler : public IEventHandler {
  public:
    explicit ServerEventHandler(const Server&);
    ~ServerEventHandler();
    void handleEvent();

  private:
    Server _server;
};
