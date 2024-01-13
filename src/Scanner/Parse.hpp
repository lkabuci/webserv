#pragma once

#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include "Scanner.hpp"

class Parse {
  public:
    Parse();
    Parse(const std::string& source);
    Parse(const Parse& parser);
    Parse& operator=(const Parse& parser);

    Token advance();
    Token previous();
    Token peek();
    bool  match(const TokenType& type);
    bool  check(const TokenType& type);
    void  consume(const TokenType& type, const char* message);
    bool  is_at_end() const;

    std::string get_line();

  private:
    Scanner _scanner;
    Token   _token;
    Token   _prev;
};

#endif
