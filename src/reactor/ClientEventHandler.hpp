#pragma once

#include "../stream/Client.hpp"
#include "../stream/Server.hpp"
#include "IEventHandler.hpp"
#include <string>
#include <vector>

class ClientEventHandler : public IEventHandler {
  public:
    explicit ClientEventHandler(Server&, sockaddr_storage&, int clientSocket);
    virtual ~ClientEventHandler();
    virtual void  handleEvent();
    Client&       getClient();
    const Server& getServer() const;

    // Response helpers used by strategy classes
    int  getSocketFd() const;
    void sendResponse(int statusCode, const std::string& contentType,
                      const std::string& body);
    void sendRedirectResponse(int code, const std::string& location);

    // Legacy accessors (kept for compatibility)
    bool               isDoneReading() const;
    void               setIsDoneReading(bool isDoneReading);
    const std::string& getHeader() const;
    const std::string& getBody() const;

  private:
    int           _socket;
    const Server& _server;
    bool          _isDoneReading;
    Client        _client;
    std::string   _header;
    std::string   _body;
    std::string   _rawData;
    bool          _isHeaderEnded;

    static std::string statusText(int code);
};
