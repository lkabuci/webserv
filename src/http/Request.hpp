#pragma once

#include "../methods/IRequestStrategy.hpp"
#include "HTTP.hpp"
#include "Header.hpp"
#include "StatusLine.hpp"
#include <map>
#include <vector>

#define CRLF2 "\r\n\r\n"

class Request {

  public:
    Request(StatusLine&, std::vector<Header>&);
    ~Request();
    std::string    serialize() const;
    static Request deserialize(const std::string& request);
    void           handle();

    std::string         getMethod();
    std::string         getUri();
    std::string         getHttpVersion();
    std::vector<Header> getHeaders();
    std::string         getBody();
    std::string         getHeaderValue(const std::vector<Header>& headers,
                                       const std::string&         key);
    void                appendBody(std::string body);

  private:
    StatusLine          _status_line;
    std::vector<Header> _headers;
    std::string         _body;
    IRequestStrategy*   _rqStrategy;
    struct HeaderMatch {
        explicit HeaderMatch(const std::string& key);
        bool        operator()(const Header& header) const;
        std::string _key;
    };
};
