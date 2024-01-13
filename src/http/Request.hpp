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
    static std::set<std::string> general_headers;
    static std::set<std::string> request_headers;
    static std::set<std::string> entity_headers;

    Request(const std::string& request);
    Request(StatusLine&, std::vector<Header>&, const std::string&);
    ~Request();
    std::string    serialize() const;
    static Request deserialize(const std::string& request);
    void           handle();

    void setRequestStr(const std::string& request);

    const std::string&        getRequestStr() const;
    const std::string         getMethod() const;
    const std::string         getUri() const;
    const std::string         getHttpVersion() const;
    const std::vector<Header> getHeaders() const;
    const std::string         getBody() const;
    const std::string         getHeaderValue(const std::vector<Header>& headers,
                                             const std::string&         key) const;
    void                      appendBody(std::string body);

    static std::string str_to_lower(const std::string& str);

  private:
    std::string         _request;
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
