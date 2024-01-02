#pragma once

#include <vector>
#include "IEventHandler.hpp"
#include "../stream/Client.hpp"

class ClientEventHandler : public IEventHandler {
  public:
    explicit ClientEventHandler(sockaddr_storage&, int clientSocket);
    virtual ~ClientEventHandler();
    virtual void handleEvent();

  private:
    int _socket;
    Client _client;
};
