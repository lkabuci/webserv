#pragma once

#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include "SyntaxException.hpp"
#include "Token.hpp"
#include "common.hpp"

class Lexer {
  public:
    Lexer(const std::string& source);
    ~Lexer();

    Token scan();

    static std::map<std::string, TokenType> keywords;
    static std::map<TokenType, std::string> keywordsValues;

    // private:
    Lexer(const Lexer& lexer);
    Lexer& operator=(const Lexer& lexer);

    std::string _source;
    const int _length;
    int _start;
    int _current;
    int _line;
    Token _token;

    Token scanToken();
    void setToken(TokenType type);
    void setToken(TokenType type, const std::string& text);
    char peek();
    char advance();
    bool isAtEnd() const;
    void skipWhiteSpaces();
    void skipComment();
    void _string(char c);
    void _parameter();
    bool isParameterChar(char c);

    void reserve();
};

#endif
