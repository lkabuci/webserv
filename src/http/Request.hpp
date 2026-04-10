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

    std::string         getMethod() const;
    std::string         getUri() const;
    std::string         getHttpVersion() const;
    std::vector<Header> getHeaders() const;
    std::string         getBody() const;
    std::string         getHeaderValue(const std::vector<Header>& headers,
                                       const std::string&         key) const;
    void                appendBody(const std::string& body);

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
