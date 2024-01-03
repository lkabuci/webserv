#include "StatusLine.hpp"
#include "HTTP.hpp"
#include <sstream>

StatusLine::StatusLine() {}

StatusLine::StatusLine(HTTP::METHOD method, const std::string& uri,
                       HTTP::VERSION version)
    : _method(method), _uri(uri), _version(version) {}

std::string StatusLine::serialize() const {
    std::stringstream status_line;
    status_line << HTTP::toString(_method) << " " << _uri << " "
                << HTTP::toString(_version);
    return status_line.str();
}

StatusLine StatusLine::deserialize(const std::string& statusLine) {
    std::stringstream ss(statusLine);
    std::string       buffer;
    HTTP::METHOD      method;
    HTTP::VERSION     version;
    std::string       reason_phrase;
    std::string       uri;

    int count = 0;
    while (std::getline(ss, buffer, ' ')) {
        switch (count) {
        case 0:
            method = HTTP::toMethod(buffer);
            break;
        case 1:
            uri = buffer;
            break;
        case 2:
            version = HTTP::toVersion(buffer);
            break;
        }
        count++;
    }
    if (count != 3) {
        throw std::runtime_error("Error while parsing the status line");
    }
    return StatusLine(method, uri, version);
}

const HTTP::METHOD& StatusLine::getMethod() const {
    return _method;
}

const std::string& StatusLine::getURI() const {
    return _uri;
}

const HTTP::VERSION& StatusLine::getVersion() const {
    return _version;
}
