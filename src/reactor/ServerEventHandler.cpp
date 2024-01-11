#include "ServerEventHandler.hpp"
#include "ClientEventHandler.hpp"
#include "Reactor.hpp"
#include <iostream>
#include <sys/socket.h>

ServerEventHandler::ServerEventHandler(const Server& sv) : _server(sv) {}

ServerEventHandler::~ServerEventHandler() {}

void ServerEventHandler::handleEvent() {
    // Implement server-related event handling
    // Accept incoming connections and create client event handlers
    sockaddr_storage clientAddr;
    socklen_t        clientAddrLen = sizeof clientAddr;
    int              clientSocket =
        accept(_server.getSocket(), reinterpret_cast<sockaddr*>(&clientAddr),
               &clientAddrLen);
    if (clientSocket == -1) {
        std::cerr << "failed to connect" << std::endl;
        return;
    }
    ClientEventHandler* clientHandler =
        new ClientEventHandler(_server, clientAddr, clientSocket);
    Reactor::getInstance().registerHandler(clientHandler, clientSocket);
}
