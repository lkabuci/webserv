#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "../stream/Client.hpp"
#include "ClientEventHandler.hpp"
#include "Reactor.hpp"

#define BUFFER_SIZE 4096
#include "../http/Request.hpp"

ClientEventHandler::ClientEventHandler(sockaddr_storage& addr, int clientSocket)
    : _socket(clientSocket), _client(addr, clientSocket) {}

ClientEventHandler::~ClientEventHandler() {}

void ClientEventHandler::handleEvent() {
    // Implement client-related event handling
    char        buffer[BUFFER_SIZE];
    std::string s;
    while (s.find("\r\n\r\n") == std::string::npos) {
        std::memset(buffer, 0, BUFFER_SIZE);
        ssize_t ret = recv(_socket, buffer, BUFFER_SIZE - 1, 0);

        if (ret == -1) {
            std::cerr << "failed to read data from client" << std::endl;
            Reactor::getInstance().unregisterHandler(this);
            return;
        }
        // Client closed connection
        if (ret == 0) {
            std::cout << "Client " << _client.getSockFd()
                      << " closed connection"
                         "."
                      << std::endl;
            Reactor::getInstance().unregisterHandler(this);
            return;
        }
        s += buffer;
        try {
            Request rq(Request::deserialize(s));
            std::cout << rq.serialize() << "\n";
        } catch (...) {
            std::cout << "Error parsing the request\n";
        }
        // we will just send this response for the moment
        const char response[] = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "Content-Length: 13\r\n"
                                "\r\n"
                                "Hello, World!\r\n"
                                "\r\n";
        std::cout << "Client " << _client.getSockFd() << " sent: " << buffer
                  << std::endl;
        send(_socket, response, std::strlen(response), 0);
    }
    // Process incoming data or respond to the client
    // note that if the connection should be kept alive or not
    // Other necessary methods for client events
}
