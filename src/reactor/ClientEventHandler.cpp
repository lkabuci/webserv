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
    _isHeaderEnded = false;
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
            if (!_isHeaderEnded) {
                _header = s.substr(0, headerPos);
                _body = s.substr(headerPos + std::strlen(CRLF2));
                HTTP::METHOD method =
                    HTTP::toMethod(Request::deserialize(_header).getMethod());
                switch (method) {
                case HTTP::GET:
                    GetRequestStrategy(this);
                    break;
                case HTTP::POST:
                    handle_post_request(s);
                    // PostRequestStrategy(this);
                    //                    goto go;
                    break;
                case HTTP::DELETE:
                    DELETERequestStrategy(this);
                    break;
                default:
                    Reactor::getInstance().unregisterHandler(this);
                }
                _isHeaderEnded = true;
            } else {
                _body.append(s);
            }
        }
        if (!_isDoneReading) {
            return;
        }
    }
    // go:
    const char response[] = "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 13\r\n"
                            "\r\n"
                            "sf ghayerha";
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

void ClientEventHandler::handle_post_request(const std::string& s) {
    (void)s;
    PostRequestStrategy post_request_handler(this);
    try {
        std::string r = "POST /upload HTTP/1.1\r\n"
                        "Host: localhost:3000\r\n"
                        "Content-Type: multipart/form-data;                 "
                        "boundary=----WebKitFormBoundaryABC123\r\n"
                        "\r\n"
                        "john_doe\r\n"
                        "------WebKitFormBoundaryABC123\r\n"
                        "Content-Disposition: form-data; name=\"file\"; "
                        "filename=\"example.txt\"\r\n"
                        "Content-Type: text/plain\r\n"
                        "\r\n"
                        "This is the content of the file.\r\n"
                        "------WebKitFormBoundaryABC123--\r\n";
        // Request request(Request::deserialize(r));
        // std::cout << request.getBody() << '\n';
        Request request(r);
        post_request_handler.handleRequest(request);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
        std::exit(1);
    }
}
