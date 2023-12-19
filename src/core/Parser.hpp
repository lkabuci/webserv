#pragma once

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "ParseException.hpp"
#include "Expr.hpp"
#include <stdarg.h>

class   Parser {
public:
    Parser(const std::list<Token>& tokens);

    Expr*   parse();

private:
    Parser(const Parser&);
    Parser& operator=(const Parser&);

    std::list<Token>            _tokens;
    int                         _current;
    std::list<Token>::iterator  _lookahead;

    //Expr*                       statement();
    Expr*       expression();
    Expr*       serverContext();
    Expr*       locationContext();
    Expr*       serverDirective();
    Expr*       locationDirective();
    Expr*       insideBlock();
    Expr*       parameter();
    Expr*       locationParameter();

    bool    check(TokenType type);
    Token&  peek();
    Token&  peekNext();
    bool    match(int n, ...);
    void    advance();
    Token&  previous();
    bool    isAtEnd();
    bool    isDirectiveKey();
    void    consume(TokenType type, const std::string& message);
    //bool    consumeDirective();
    //bool    isInvalidToken();
    bool    isServerDirective();
    bool    consumeServerDirective();
    bool    consumeLocationDirective();
};

#endif
