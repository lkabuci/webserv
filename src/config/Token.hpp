#pragma once

#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include "common.hpp"

class Token {
  public:
    Token();
    Token(const TokenType& type, const std::string& lexeme, const int& line);
    Token(const Token& token);
    ~Token();

    Token& operator=(const Token& token);

    const TokenType&   type() const;
    const std::string& lexeme() const;
    const int&         line() const;

  private:
    TokenType   _type;
    std::string _lexeme;
    int         _line;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif
