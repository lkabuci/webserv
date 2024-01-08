#include "Request.hpp"
#include "../methods/DELETERequestStrategy.hpp"
#include "../methods/GETRequestStrategy.hpp"
#include "../methods/POSTRequestStrategy.hpp"
#include "HTTP.hpp"
#include "Header.hpp"
#include "StatusLine.hpp"
#include <istream>
#include <sstream>
#include <stdexcept>
#include <vector>

static IRequestStrategy* getRequestStrategy(StatusLine&);

/*
    GET / HTTP/1.1\r\n
    Host: www.example.com\r\n
    Connection: close\r\n
    \r\n
    body
*/
Request::Request(StatusLine& status_line, std::vector<Header>& headers,
                 const std::string& body, IRequestStrategy* rq)
    : _status_line(status_line), _headers(headers), _body(body),
      _rqStrategy(rq) {}

std::string Request::serialize() const {
    std::stringstream request;
    request << _status_line.serialize() << CRLF;
    for (size_t i = 0; i < _headers.size(); ++i) {
        request << _headers[i].serialize() << CRLF;
    }
    request << CRLF;
    request << _body;
    return request.str();
}

void Request::handle() {
    if (_rqStrategy) {
        _rqStrategy->handleRequest(*this);
        return;
    }
    // TODO: if no method is set
}

Request Request::deserialize(const std::string& request) {
    StatusLine          status_line;
    std::vector<Header> headers;
    std::string         buffer;
    std::istringstream  ss(request);
    int                 size = 0;
    std::string         body;
    bool                isHeadFinish = false;
    IRequestStrategy*   rqStrategy = NULL;

    while (std::getline(ss, buffer)) {
        size_t pos = buffer.find(CR);
        if (pos != std::string::npos) {
            buffer.erase(pos);
        }
        if (buffer.empty()) {
            isHeadFinish = true;
            continue;
        }
        if (size == 0) {
            status_line = StatusLine::deserialize(buffer);
        } else if (!isHeadFinish) {
            headers.push_back(Header::deserialize(buffer));
        } else {
            body += buffer;
        }
        ++size;
    }
    if (size == 0) {
        throw std::runtime_error("Error while parsing the request");
    }
    rqStrategy = getRequestStrategy(status_line);
    // TODO: check if the HOST key exists
    return Request(status_line, headers, body, rqStrategy);
}

std::string Request::getMethod() {
    return HTTP::toString(_status_line.getMethod());
}

std::string Request::getUri() {
    return _status_line.getURI();
}

std::string Request::getHttpVersion() {
    return HTTP::toString(_status_line.getVersion());
}

std::vector<Header> Request::getHeaders() {
    return _headers;
}
std::string Request::getBody() {
    return _body;
}
Request::~Request() {
    delete _rqStrategy;
}

IRequestStrategy* getRequestStrategy(StatusLine& statusLine) {
    switch (statusLine.getMethod()) {
    case HTTP::GET:
        return new GetRequestStrategy();
    case HTTP::POST:
        return new PostRequestStrategy();
    case HTTP::DELETE:
        return new DELETERequestStrategy();

        //    TODO: PUT and HEAD methods to be added later
        //    case HTTP::PUT: return new PutRequestStrategy();
        //    case HTTP::HEAD: return new HeadRequestStrategy();
    default:
        throw std::runtime_error("Unsupported method");
    }
}
