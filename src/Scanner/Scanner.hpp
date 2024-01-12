#pragma once

#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__

#include "../config/Token.hpp"

class Scanner {
  public:
    Scanner();
    Scanner(const std::string& source);
    Scanner(const Scanner& scanner);

    Scanner& operator=(const Scanner& scanner);

    Token get_next_token();

  private:
    Token       _token;
    std::string _source;
    size_t      _start;
    size_t      _current;
    size_t      _length;

    void set_token(const TokenType& type);
    void comment();
    void quoted_string();
    void token();
    char peek();
    char peek_next();
    char advance();
    bool match(char expected);
    void consume(char c, const char* message);
    bool check(char c);
    bool is_at_end() const;
    bool is_separator(char c);
};

#endif
