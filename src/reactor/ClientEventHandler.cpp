#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
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

ClientEventHandler::ClientEventHandler(Server& sv, sockaddr_storage& addr,
                                       int clientSocket)
    : _socket(clientSocket), _server(sv), _client(addr, clientSocket) {
    _isDoneReading = false;
    _isHeaderEnded = false;
}

ClientEventHandler::~ClientEventHandler() {
    close(_socket);
}

std::string ClientEventHandler::statusText(int code) {
    switch (code) {
    case 200:
        return "OK";
    case 201:
        return "Created";
    case 204:
        return "No Content";
    case 301:
        return "Moved Permanently";
    case 302:
        return "Found";
    case 400:
        return "Bad Request";
    case 403:
        return "Forbidden";
    case 404:
        return "Not Found";
    case 405:
        return "Method Not Allowed";
    case 413:
        return "Request Entity Too Large";
    case 500:
        return "Internal Server Error";
    case 501:
        return "Not Implemented";
    default:
        return "Unknown";
    }
}

void ClientEventHandler::sendResponse(int                statusCode,
                                      const std::string& contentType,
                                      const std::string& body) {
    std::ostringstream response;
    response << "HTTP/1.1 " << statusCode << " " << statusText(statusCode)
             << CRLF;
    response << "Content-Type: " << contentType << CRLF;
    response << "Content-Length: " << body.size() << CRLF;
    response << "Connection: close" << CRLF;
    response << CRLF;
    response << body;

    std::string resp = response.str();
    send(_socket, resp.c_str(), resp.size(), 0);
}

void ClientEventHandler::sendRedirectResponse(int                code,
                                              const std::string& location) {
    std::ostringstream response;
    response << "HTTP/1.1 " << code << " " << statusText(code) << CRLF;
    response << "Location: " << location << CRLF;
    response << "Content-Length: 0" << CRLF;
    response << "Connection: close" << CRLF;
    response << CRLF;

    std::string resp = response.str();
    send(_socket, resp.c_str(), resp.size(), 0);
}

void ClientEventHandler::handleEvent() {
    char    buffer[BUFFER_SIZE];
    ssize_t ret = recv(_socket, buffer, sizeof(buffer), MSG_DONTWAIT);

    if (ret < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        std::cerr << "recv error: " << strerror(errno) << std::endl;
        Reactor::getInstance().unregisterHandler(this);
        return;
    }
    if (ret == 0) {
        std::cout << "Client " << _client.getSockFd()
                  << " closed connection.\n";
        Reactor::getInstance().unregisterHandler(this);
        return;
    }

    _rawData.append(buffer, static_cast<size_t>(ret));

    // Find end of HTTP headers
    size_t headerEnd = _rawData.find(CRLF2);
    if (headerEnd == std::string::npos) {
        if (_rawData.size() > MAXIMUM_HTTP_REQUEST_HEADER_SIZE) {
            sendResponse(413, "text/plain", "Request Entity Too Large");
            Reactor::getInstance().unregisterHandler(this);
        }
        return; // Need more header data
    }

    if (!_isHeaderEnded) {
        _header = _rawData.substr(0, headerEnd);
        _isHeaderEnded = true;
    }

    _body = _rawData.substr(headerEnd + std::strlen(CRLF2));

    // Parse request to determine if we need to wait for body
    Request req = Request::deserialize(_header);

    std::string contentLengthStr =
        req.getHeaderValue(req.getHeaders(), "Content-Length");
    size_t contentLength = 0;
    if (!contentLengthStr.empty()) {
        contentLength =
            static_cast<size_t>(std::atol(contentLengthStr.c_str()));
    }

    if (_body.size() < contentLength) {
        return; // Need more body data
    }

    req.appendBody(_body);

    // Dispatch to the appropriate strategy
    HTTP::METHOD      method = HTTP::toMethod(req.getMethod());
    IRequestStrategy* strategy = NULL;

    switch (method) {
    case HTTP::GET:
        strategy = new GetRequestStrategy(this);
        break;
    case HTTP::POST:
        strategy = new PostRequestStrategy(this);
        break;
    case HTTP::DELETE:
        strategy = new DELETERequestStrategy(this);
        break;
    default:
        sendResponse(501, "text/plain", "Not Implemented");
        Reactor::getInstance().unregisterHandler(this);
        return;
    }

    strategy->handleRequest(req);
    delete strategy;
    Reactor::getInstance().unregisterHandler(this);
}

int ClientEventHandler::getSocketFd() const {
    return _socket;
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
