#pragma once

#ifndef __PARSE_EXCEPTION_HPP__
#define __PARSE_EXCEPTION_HPP__

#include "Token.hpp"
#include "common.hpp"

class ParseException : public std::exception {
  public:
    ParseException(Token token, const std::string& message);
    virtual ~ParseException() throw() {}

    virtual const char* what() const throw();

  private:
    std::string _errorMsg;
};

#endif
