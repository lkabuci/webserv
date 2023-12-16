#pragma once

#ifndef __PARSE_EXCEPTION_HPP__
#define __PARSE_EXCEPTION_HPP__

#include "common.hpp"
#include "Token.hpp"

class   ParseException : public std::exception {
public:
    ParseException(Token token, const std::string& message);

    virtual const char* what() const throw();

private:
    std::string _errorMsg;
};

#endif
