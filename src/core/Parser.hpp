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
    size_t                      _current;
    std::list<Token>::iterator  _itCurrent;

    Expr*                   statement();
    Expr*                   expression();
    Expr*                   serverContext();
    Expr*                   block();
    Directive::Parameter    direcitve();
    Expr*                   locationContext();

    bool    check(TokenType type);
    Token&  peek();
    bool    match(int n, ...);
    void    advance();
    Token&  previous();
    bool    isAtEnd();
    bool    isDirectiveKey();
    void    consume(TokenType type, const std::string& message);
    bool    consumeDirective();
    bool    isInvalidToken();
};

#endif
