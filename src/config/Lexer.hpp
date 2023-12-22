#pragma once

#include "TokenType.hpp"
#include <string>
#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include "common.hpp"
#include "Token.hpp"
#include "SyntaxException.hpp"

//class   Lexer {
//public:
//    Lexer(const std::string& source);

//    std::list<Token>    scanTokens();

//    static std::map<std::string, TokenType> keys;
//    static std::map<std::string, TokenType> creatKeysMap();

//private:
//    Lexer(const Lexer&);
//    Lexer&    operator=(const Lexer&);

//    std::string         _source;
//    std::list<Token>    _tokens;
//    size_t              _start;
//    size_t              _current;
//    size_t              _line;
//    size_t              _length;

//    void    scanToken();
//    bool    isAtEnd() const;
//    void    skipWhiteSpaces();
//    char    peek();
//    char    peekNext();
//    char    advance();
//    void    addToken(TokenType type);
//    void    _string();
//    void    quotes(char c);
//    void    skipComment();
//    bool    isStringChar(char c);
//};

class   Lexer {
public:
    Lexer(const std::string& source);
    ~Lexer();

    Token   scan();

    static std::map<std::string, TokenType> keywords;
    static std::map<TokenType, std::string> keywordsValues;

private:
    Lexer(const Lexer& lexer);
    Lexer&  operator=(const Lexer& lexer);

    std::string _source;
    const int   _length;
    int         _start;
    int         _current;
    int         _line;
    Token       _token;

    Token   scanToken();
    void    setToken(TokenType type);
    void    setToken(TokenType type, const std::string& text);
    char    peek();
    char    advance();
    bool    isAtEnd() const;
    void    skipWhiteSpaces();
    void    skipComment();
    void    _string(char c);
    void    _parameter();
    bool    isParameterChar(char c);

    void    reserve();
};

#endif
