#pragma once

#include "../stream/Client.hpp"
#include "IEventHandler.hpp"
#include <vector>

class ClientEventHandler : public IEventHandler {
  public:
    explicit ClientEventHandler(sockaddr_storage&, int clientSocket);
    virtual ~ClientEventHandler();
    virtual void handleEvent();

  private:
    int    _socket;
    Client _client;
};
