#include "StatusLine.hpp"
#include "HTTP.hpp"
#include <sstream>

StatusLine::StatusLine() {}

StatusLine::StatusLine(HTTP::METHOD method, const std::string& uri,
                       HTTP::VERSION version)
    : _method(method), _uri(uri), _version(version) {}

std::string StatusLine::serliaze() const {
    std::stringstream status_line;
    status_line << _method << " " << _uri << " " << _version;
    return status_line.str();
}

StatusLine StatusLine::deserialize(const std::string& status_line) {
    std::stringstream ss(status_line);
    std::string buffer;
    HTTP::METHOD method;
    HTTP::VERSION version;
    HTTP::STATUS_CODE status_code;
    std::string reason_phrase;
    std::string uri;

    int count = 0;
    while (std::getline(ss, buffer, ' ')) {
        switch (count) {
        case 0: method = HTTP::to_method(buffer); break;
        case 1: uri = buffer; break;
        case 2: version = HTTP::to_version(buffer); break;
        }
        count++;
    }
    if (count != 3) {
        throw std::runtime_error("Error while parsing the status line");
    }
    return StatusLine(method, uri, version);
}
