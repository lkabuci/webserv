#include "Request.hpp"
#include "Header.hpp"
#include "StatusLine.hpp"
#include <istream>
#include <sstream>
#include <stdexcept>
#include <vector>

/*
    example of an http request using GET method
    GET / HTTP/1.1\r\n
    Host: www.example.com\r\n
    Connection: close\r\n
    \r\n
*/
Request::Request(StatusLine status_line, std::vector<Header>& headers)
    : _status_line(status_line), _headers(headers) {}

std::string Request::serialize() const {
    std::stringstream request;
    request << _status_line.serialize() << CRLF;
    for (size_t i = 0; i < _headers.size(); ++i) {
        request << _headers[i].serialize() << CRLF;
    }
    request << CRLF;
    return request.str();
}

// NOTE: split by /r/n instead of \n
Request Request::deserialize(const std::string& request) {
    StatusLine          status_line;
    std::vector<Header> headers;
    std::string         buffer;
    std::istringstream  ss(request);
    int                 size = 0;

    while (std::getline(ss, buffer)) {
        if (size == 0) {
            status_line = StatusLine::deserialize(buffer);
            continue;
        }
        headers.push_back(Header::deserialize(buffer));
        ++size;
    }
    if (size == 0) {
        throw std::runtime_error("Error while parsing the request");
    }
    return Request(status_line, headers);
}
