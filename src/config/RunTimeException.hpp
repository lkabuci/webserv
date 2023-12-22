#pragma once

#ifndef __RUN_TIME_EXCEPTION_HPP__
#define __RUN_TIME_EXCEPTION_HPP__

#include "common.hpp"
#include "Token.hpp"

class   RunTimeException : public std::exception {
public:
    RunTimeException(const Token& token, const std::string& message);
    virtual ~RunTimeException() throw();

    virtual const char* what() const throw();

private:
    std::string _errMsg;
};

#endif
