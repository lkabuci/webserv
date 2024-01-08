#pragma once

#include "../methods/IRequestStrategy.hpp"
#include "HTTP.hpp"
#include "Header.hpp"
#include "StatusLine.hpp"
#include <map>
#include <vector>

class Request {

  public:
    Request(StatusLine&, std::vector<Header>&, const std::string&,
            IRequestStrategy* rq = NULL);
    ~Request();
    std::string    serialize() const;
    static Request deserialize(const std::string& request);
    void           handle();

    std::string         getMethod();
    std::string         getUri();
    std::string         getHttpVersion();
    std::vector<Header> getHeaders();
    std::string         getBody();

  private:
    StatusLine          _status_line;
    std::vector<Header> _headers;
    std::string         _body;
    IRequestStrategy*   _rqStrategy;
};
