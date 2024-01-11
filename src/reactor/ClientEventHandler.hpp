#pragma once

#include "../stream/Client.hpp"
#include "../stream/Server.hpp"
#include "IEventHandler.hpp"
#include <vector>

class ClientEventHandler : public IEventHandler {
  public:
    explicit ClientEventHandler(Server&, sockaddr_storage&, int clientSocket);
    virtual ~ClientEventHandler();
    virtual void  handleEvent();
    Client&       getClient();
    const Server& getServer() const;
    bool          isDoneReading() const;
    void          setIsDoneReading(bool isDoneReading);

  private:
    int           _socket;
    const Server& _server;
    bool          _isDoneReading;
    Client        _client;
    std::string   _header;

  public:
    const std::string& getHeader() const;

    const std::string& getBody() const;

  private:
    std::string _body;
};
