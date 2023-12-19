#pragma once

#ifndef __ERROR_REPORTER_HPP__
#define __ERROR_REPORTER_HPP__

#include "common.hpp"

class   SyntaxException : public std::exception {
public:
    SyntaxException(int line, const std::string& message, char c);
    SyntaxException(int line, const std::string& message);
    virtual ~SyntaxException() throw();

    virtual const char* what() const throw();

    static std::string  toString(int nbr);

    static bool hadError;

private:
    std::string _errorMsg;
};

#endif
