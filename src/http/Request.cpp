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

/*
    GET / HTTP/1.1\r\n
    Host: www.example.com\r\n
    Connection: close\r\n
    \r\n
    body
*/
Request::Request(StatusLine& status_line, std::vector<Header>& headers)
    : _status_line(status_line), _headers(headers) {}

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

    while (std::getline(ss, buffer)) {
        size_t pos = buffer.find(CR);
        if (pos != std::string::npos) {
            buffer.erase(pos);
        }
        if (buffer.empty()) {
            continue;
        }
        if (size == 0) {
            status_line = StatusLine::deserialize(buffer);
        } else {
            headers.push_back(Header::deserialize(buffer));
        }
        ++size;
    }
    if (size == 0) {
        throw std::runtime_error("Error while parsing the request");
    }
    // TODO: check if the HOST key exists
    return Request(status_line, headers);
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
Request::~Request() {}

std::string Request::getHeaderValue(const std::vector<Header>& headers,
                                    const std::string&         key) {
    std::vector<Header>::const_iterator it =
        std::find_if(headers.begin(), headers.end(), HeaderMatch(key));
    if (it != headers.end())
        return it->getValue();
    return "";
}

void Request::appendBody(const std::string body) {
    _body += body;
}

Request::HeaderMatch::HeaderMatch(const std::string& key) : _key(key) {}

bool Request::HeaderMatch::operator()(const Header& header) const {
    return header.getKey() == _key;
}
