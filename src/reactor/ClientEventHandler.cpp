#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "../http/HTTP.hpp"
#include "../http/Request.hpp"
#include "../methods/DELETERequestStrategy.hpp"
#include "../methods/GETRequestStrategy.hpp"
#include "../methods/IRequestStrategy.hpp"
#include "../methods/POSTRequestStrategy.hpp"
#include "../stream/Client.hpp"
#include "ClientEventHandler.hpp"
#include "Reactor.hpp"

#define BUFFER_SIZE 4096
#define MAXIMUM_HTTP_REQUEST_HEADER_SIZE 8192
// 8kb is the default max http request header in both nginx & apache

ClientEventHandler::ClientEventHandler(Server& sv, sockaddr_storage& addr,
                                       int clientSocket)
    : _socket(clientSocket), _server(sv), _client(addr, clientSocket) {
    _isDoneReading = false;
}

ClientEventHandler::~ClientEventHandler() {}

void ClientEventHandler::handleEvent() {
    char        buffer[MAXIMUM_HTTP_REQUEST_HEADER_SIZE];
    std::string s;
    size_t      headerPos = std::string::npos;
    while (headerPos == std::string::npos && !_isDoneReading) {
        std::memset(buffer, 0, sizeof(buffer));
        ssize_t ret = recv(_socket, buffer, sizeof(buffer), MSG_DONTWAIT);

        if (ret == -1) {
            std::cerr << "failed to read data from client" << std::endl;
            Reactor::getInstance().unregisterHandler(this);
            return;
        }

        // Client closed connection
        // or ended sending request
        if (ret == 0) {
            if (!_isDoneReading) {
                std::cout << "Client " << _client.getSockFd()
                          << " closed connection.\n";
                Reactor::getInstance().unregisterHandler(this);
                return;
            }
            // TODO: else client sent all request
        }

        s.append(buffer, ret);
        if ((headerPos = s.find(CRLF2)) != std::string::npos) {
            _header = s.substr(0, headerPos);
            _body = s.substr(headerPos + std::strlen(CRLF2));
            HTTP::METHOD method =
                HTTP::toMethod(Request::deserialize(_header).getMethod());
            switch (method) {
            case HTTP::GET:
                GetRequestStrategy(this);
                break;
            case HTTP::POST:
                PostRequestStrategy(this);
                break;
            case HTTP::DELETE:
                DELETERequestStrategy(this);
                break;
            default:
                Reactor::getInstance().unregisterHandler(this);
            }
        }
        if (!_isDoneReading) {
            return;
        }
    }
    const char response[] = "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 13\r\n"
                            "\r\n"
                            "Hello, World!";
    send(_socket, response, std::strlen(response), 0);
    Reactor::getInstance().unregisterHandler(this);
}

Client& ClientEventHandler::getClient() {
    return _client;
}

const Server& ClientEventHandler::getServer() const {
    return _server;
}

bool ClientEventHandler::isDoneReading() const {
    return _isDoneReading;
}

void ClientEventHandler::setIsDoneReading(bool isDoneReading) {
    _isDoneReading = isDoneReading;
}

const std::string& ClientEventHandler::getHeader() const {
    return _header;
}

const std::string& ClientEventHandler::getBody() const {
    return _body;
}
