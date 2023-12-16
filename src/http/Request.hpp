#ifndef __HTTP_REQUEST_HPP__
#define __HTTP_REQUEST_HPP__

#include "HTTP.hpp"
#include "Header.hpp"
#include "StatusLine.hpp"
#include <vector>

class Request {

  public:
    Request(StatusLine, std::vector<Header>&);
    std::string serialize() const;
    static Request deserialize(const std::string& request);

  private:
    StatusLine _status_line;
    std::vector<Header> _headers;
};

#endif // __HTTP_REQUEST_HPP__
