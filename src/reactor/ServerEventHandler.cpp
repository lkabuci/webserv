#include "ServerEventHandler.hpp"
#include "ClientEventHandler.hpp"
#include "Reactor.hpp"
#include <iostream>
#include <sys/socket.h>

ServerEventHandler::ServerEventHandler(int serverSocket)
    : _socket(serverSocket) {}

ServerEventHandler::~ServerEventHandler() {}

void ServerEventHandler::handleEvent() {
    // Implement server-related event handling
    // Accept incoming connections and create client event handlers
    sockaddr_storage clientAddr;
    socklen_t        clientAddrLen = sizeof clientAddr;
    int clientSocket = accept(_socket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        std::cerr << "failed to connect" << std::endl;
        return;
    }
    ClientEventHandler* clientHandler = new ClientEventHandler(clientAddr,
                                                               clientSocket);
    Reactor::getInstance().registerHandler(clientHandler);
}
