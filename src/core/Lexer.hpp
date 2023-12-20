#pragma once

#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include "common.hpp"
#include "Token.hpp"
#include "SyntaxException.hpp"

class   Lexer {
public:
    Lexer(const std::string& source);

    std::list<Token>    scanTokens();

    static std::map<std::string, TokenType> keys;
    static std::map<std::string, TokenType> creatKeysMap();

//private:
    Lexer(const Lexer&);
    Lexer&    operator=(const Lexer&);

    std::string         _source;
    std::list<Token>    _tokens;
    size_t              _start;
    size_t              _current;
    size_t              _line;
    size_t              _length;

    void    scanToken();
    bool    isAtEnd() const;
    void    skipWhiteSpaces();
    char    peek();
    char    peekNext();
    char    advance();
    void    addToken(TokenType type);
    void    _string();
    void    quotes(char c);
    void    skipComment();
    bool    isStringChar(char c);
    bool    isValidPathChar(char c);
};

#endif
