#pragma once

#include "IEventHandler.hpp"

class ServerEventHandler : public IEventHandler {
  public:
    explicit ServerEventHandler(int serverSocket);
    ~ServerEventHandler();
    void handleEvent();

  private:
    int _socket;
};
